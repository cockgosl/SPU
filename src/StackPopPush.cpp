#include "StackPopPush.h"

StackErr_t StackPop (stack_t* stk, type* value, size_t indicator, StackErr_t* err) {
    StackVerify(stk, indicator, err);

    if (stk -> size > 0) {
        *value = stk -> array[stk -> size -1  + indicator];
        stk -> array[stk -> size + -1 + indicator] = 0;
        (stk -> size)--; 
        }

    StackVerify(stk, indicator, err);
    return *err;
}

StackErr_t StackPush (stack_t* stk, type value, size_t indicator,  StackErr_t* err) {
    StackVerify(stk, indicator, err);
    
    if (stk -> size >= stk -> capacity) {
        stk -> array = (type*) realloc (stk -> array, ((stk -> size) + 1 ) * sizeof(int));
        stk -> capacity = stk -> size + 1;
    }
    stk -> array[stk -> size + indicator] = value;
    if (indicator) {
        (stk -> array) [stk -> size + 2] = RIGHT;
    }
    (stk -> size)++;

    StackVerify(stk, indicator, err);
    return *err;
}