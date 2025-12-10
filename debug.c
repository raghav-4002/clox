#include <stdio.h>

#include "debug.h"
#include "chunk.h"
#include "value.h"


static int simple_instruction(const char *name, int offset);
static int constant_instruction(const char *name, Chunk *chunk, int offset);


/*
    Print the particular byte instruction of
    `chunk` array
*/
int
disassemble_instruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset);
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("   | ");
    }
    else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);

        case OP_ADD:
            return simple_instruction("OPP_ADD", offset);

        case OP_SUBTRACT:
            return simple_instruction("OP_SUBTRACT", offset);

        case OP_MULTIPLY:
            return simple_instruction("OP_MULTIPLY", offset);

        case OP_DIVIDE:
            return simple_instruction("OP_DIVIDE", offset);

        case OP_NEGATE:
            return simple_instruction("OP_NEGATE", offset);

        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);

        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}


/*
    Disassemble the `chunk` array, printing all the
    instructions
*/
void
disassemble_chunk(Chunk *chunk, const char *name)
{
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset);
    }
}


/* For `OP_RETURN` */
static int
simple_instruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}


/* For `OP_CONSTANT` */
static int
constant_instruction(const char *name, Chunk *chunk, int offset)
{
    /* Trying to access the index of literal
        value which resides in the `values` array.
        The index is just next to the `OP_CONSTANT`
        instruction. */
    uint8_t constant = chunk->code[offset + 1];

    printf("%-16s %4d ", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("\n");    

    /* Move past the operand of instruction */
    return offset + 2;
}