#include "stack.h"

StackErr_t canary(stack_t* stk) {
    if (StackVerify(stk) != ADRESS) {
        size_t const capacity = stk->capacity;

        type temp[stk->capacity] = {};
        for (int ind = 0; ind < capacity; ind++) {
            temp[ind] = stk->array [ind];
        }
        stk->array = (type*) realloc (stk->array, (capacity + 2) * sizeof (type));
        if (StackVerify(stk) != ADRESS_A) {
            for (int ind = 0; ind < capacity; ind++) {
                stk->array [ind + 1] = temp [ind];
            }
            (stk->array) [0] = LEFT;
            (stk->array) [capacity + 1] = RIGHT;
            stk->canary_indicator = 1;
        }
    }
    return StackVerify(stk);
}