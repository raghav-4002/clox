#ifndef CHUNK_H_
#define CHUNK_H_


#include "common.h"
#include "value.h"


/*
    Instructions for the bytecode VM
*/
typedef enum Op_code
{
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} Op_code;

/*
    Chunk consists of instructions and data
    on which instructions should work on
*/
typedef struct Chunk
{
    int count;
    int capacity;

    uint8_t *code;  /* store bytecode instructions and operands */

    int *lines;   /* to store line number of each instruction
                     for reporting errors */

    Value_array constants; /* structure that keeps record
                              of constants in the bytecode*/
} Chunk;


void init_chunk(Chunk *chunk);
void free_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte, int line);
int add_constant(Chunk *chunk, Value value);


#endif // CHUNK_H_
