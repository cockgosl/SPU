#include "stack.h"

StackErr_t StackInit (stack_t* stk, size_t capacity, size_t value) {
    if (StackVerify(stk) != ADRESS) {
        stk->array = (type*) calloc(capacity, value);
        if (StackVerify(stk) != ADRESS_A) {
            stk->capacity = capacity;
        }
    }
    return StackVerify (stk);
}