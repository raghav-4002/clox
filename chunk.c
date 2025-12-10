#include <stdint.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"


/* Initialize the chunk with default values */
void
init_chunk(Chunk *chunk)
{
    chunk->count    = 0;
    chunk->capacity = 0;
    chunk->code     = NULL;
    chunk->lines    = NULL;
    init_value_array(&chunk->constants);
}


void
free_chunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}


void
write_chunk(Chunk *chunk, uint8_t byte, int line)
{
    /* If chunk capacity is not sufficient
       then first increase that size */
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity  = GROW_CAPACITY(old_capacity);
        chunk->code      = GROW_ARRAY(uint8_t, chunk->code,
                            old_capacity, chunk->capacity);

        /* Size of `lines` array is equal to that of `code` */
        chunk->lines     = GROW_ARRAY(int, chunk->lines,
                                       old_capacity, chunk->capacity);
    }

    /* Store the byte into the code array
        and line number into the line array */
    chunk->code[chunk->count]  = byte;
    chunk->lines[chunk->count] = line;

    chunk->count++;
}


/*
    Adds a new constant value in the chunk.
    Is a wrapper over the actual function 
    `write_value_array()`
*/
int
add_constant(Chunk *chunk, Value value)
{
    write_value_array(&chunk->constants, value);
    return chunk->constants.count - 1; /* index of value just added,
                                          will act as operand in bytecode */
}