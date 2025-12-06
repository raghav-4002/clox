#ifndef VALUE_H_
#define VALUE_H_


#include "common.h"


typedef double Value;


/* An array to store the literal values of constants.
   `Chunk` array accesses this to find literal values. */
typedef struct Value_array
{
    int capacity;
    int count;
    Value *values;
} Value_array;


void init_value_array(Value_array *array);
void write_value_array(Value_array *array, Value value);
void free_value_array(Value_array *array);
void print_value(Value value);


#endif // VALUE_H_