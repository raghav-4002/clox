#ifndef VM_H_
#define VM_H_


#include "chunk.h"


typedef struct Vm
{
    Chunk *chunk;  /* Chunk to interpret */
    
    /* 
       Instruction pointer; points to the
       instruction to be executed. Is a pointer 
       as dereferencing a ptr is faster
       than array index access
    */
    uint8_t *ip;   
} Vm;


typedef enum Interpret_result
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} Interpret_result;


void init_vm();
void free_vm();
Interpret_result interpret(Chunk *chunk);


#endif // VN_H_