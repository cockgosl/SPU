#include "canary.h"

StackErr_t canary(stack_t* stk, size_t* indicator, StackErr_t* err) {
    size_t const size = stk -> size;
    
    type temp[100] = {};
    for (int ind = 0; ind < size; ind++) {
        temp[ind] = stk -> array [ind];
    }
    stk -> array = (type*) realloc (stk -> array, (size + 2) * sizeof (type));
    for (int ind = 0; ind < size; ind++) {
        stk -> array [ind + 1] = temp [ind];
    }
    (stk -> array) [0] = LEFT;
    (stk -> array) [size + 1] = RIGHT;
    *indicator = 1;
    return *err;
}