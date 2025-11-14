#ifndef CHUNK_H_
#define CHUNK_H_


#include "common.h"


typedef enum {
    OP_RETURN,
} Op_code;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
} Chunk;

void init_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte);


#endif //CHUNK_H_
