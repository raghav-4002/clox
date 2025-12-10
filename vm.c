#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "vm.h"
#include "debug.h"


Vm vm;


static Interpret_result run(void);
static void reset_stack(void);


static Interpret_result
run(void)
{
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define BINARY_OP(op) \
        do { \
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false);

    for (;;) {
        uint8_t instruction;

        switch (instruction = READ_BYTE()) {

            #ifdef DEBUG_TRACE_EXECUTION

                /* Print the stack */
                printf("        ");
                for (Value *slot = vm.stack; slot < vm.stack_top; slot++) {
                    printf("[ ");
                    print_value(*slot);
                    printf("]");
                }
                printf("\n");

                /* Print the instruction details */
                disassemble_instruction(vm.chunk, 
                                        (int) (vm.ip - vm.chunk->code));

            #endif
                    
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }

            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;

            /* Push back the negative value of stack */
            case OP_NEGATE: push(-pop()); break;

            case OP_RETURN: {
                print_value(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}


Interpret_result
interpret(Chunk *chunk)
{
    vm.chunk = chunk;
    vm.ip    = vm.chunk->code;
    return run();
}


static void
reset_stack(void)
{
    vm.stack_top = vm.stack;
}


void
init_vm(void)
{
    reset_stack();
}


void
free_vm(void)
{

}


void
push(Value value)
{
    *(vm.stack_top) = value;
    (vm.stack_top) += 1;
}


Value
pop(void)
{
    (vm.stack_top) -= 1;
    return *(vm.stack_top);
}