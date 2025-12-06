#include <stdint.h>

#include "chunk.h"
#include "memory.h"


/* Initialize the chunk with default values */
void
init_chunk(Chunk *chunk)
{
    chunk->count    = 0;
    chunk->capacity = 0;
    chunk->code     = NULL;
}


void
free_chunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    init_chunk(chunk);
}


void
write_chunk(Chunk *chunk, uint8_t byte)
{
    /* If chunk capacity is not sufficient
       then first increase that size */
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity  = GROW_CAPACITY(old_capacity);
        chunk->code      = GROW_ARRAY(uint8_t, chunk->code,
                            old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte; /* Write into the chunk */
    chunk->count++;
}
