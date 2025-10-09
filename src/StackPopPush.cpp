#include "stack.h"

type StackPop (stack_t* stk) {
    StackErr_t error = StackVerify(stk);
    type value = 0;
    if (error != ADRESS) {
        if (stk->size > 0) {
            value = stk->array[stk->size - 1  + stk->canary_indicator];
            stk->array[stk->size + -1 + stk->canary_indicator] = 0;
            (stk->size)--; 
        }
        else {
            printf ("there are no elements\n");
            error = NOTENOUGH;
        }
    }    
    StackVerify (stk);

    return value;
}

StackErr_t StackPush (stack_t* stk, type value) {
    StackErr_t error = StackVerify(stk);
    if (error != ADRESS) {
        if (stk->size >= stk->capacity) {
            stk->array = (type*) realloc (stk->array, ((stk->size) * 2 + 2 ) * sizeof(int));
            stk->capacity = 2* ((stk->size) + 1 - stk->canary_indicator);
        }
        if (stk->array) {
            stk->array[stk->size + stk->canary_indicator] = value;
            (stk->size)++;
            if (stk->canary_indicator) {
                (stk->array) [stk->capacity + 1] = RIGHT;
            }
        }
    }
    return StackVerify(stk);
}