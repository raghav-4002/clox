#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "vm.h"
#include "debug.h"


Vm vm;


static Interpret_result run(void);


void
init_vm(void)
{

}


void
free_vm(void)
{

}


static Interpret_result
run(void)
{
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {
        uint8_t instruction;

        switch (instruction = READ_BYTE()) {
            #ifdef DEBUG_TRACE_EXECUTION
                disassemble_instruction(vm.chunk, 
                                        (int) (vm.ip - vm.chunk->code));
            #endif
                    
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                print_value(constant);
                printf("\n");
                break;
            }

            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_CONSTANT
    #undef READ_BYTE
}


Interpret_result
interpret(Chunk *chunk)
{
    vm.chunk = chunk;
    vm.ip    = vm.chunk->code;
    return run();
}