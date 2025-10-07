#include "stack.h"

StackErr_t StackInit (stack_t* stk, size_t capacity, size_t value) {
    if (stk) {
        stk->array = (type*) calloc(capacity, value);
        if (stk->array) {
            stk->capacity = capacity;
        }
    }
    return StackVerify (stk);
}