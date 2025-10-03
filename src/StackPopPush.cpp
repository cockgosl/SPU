#include "stack.h"

StackErr_t StackPop (stack_t* stk, type* value) {
    StackVerify(stk);

    if (stk -> size > 0) {
        *value = stk -> array[stk -> size -1  + stk -> canary_indicator];
        stk -> array[stk -> size + -1 + stk -> canary_indicator] = 0;
        (stk -> size)--; 
        }

    StackVerify(stk);
    return stk -> err;
}

StackErr_t StackPush (stack_t* stk, type value) {
    StackVerify(stk);
    
    if (stk -> size >= stk -> capacity) {
        stk -> array = (type*) realloc (stk -> array, ((stk -> size) * 2 + 2 ) * sizeof(int));
        stk -> capacity = (stk -> size) * 2 + 2;
    }
    stk -> array[stk -> size + stk -> canary_indicator] = value;
    (stk -> size)++;
    if (stk -> canary_indicator) {
        (stk -> array) [stk -> capacity + 1] = RIGHT;
    }

    StackVerify(stk);
    return stk -> err;
}