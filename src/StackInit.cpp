#include "stack.h"

StackErr_t StackInit (stack_t* stk, size_t capacity, size_t value, StackErr_t* err) {
    stk -> array = (type*) calloc(capacity, value);
    stk -> capacity = capacity;
    return *err;
}