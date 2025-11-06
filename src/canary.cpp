#include "stack.h"

StackErr_t canary(stack_t* stk) {
    StackErr_t err = StackVerify(stk);
    if (err != ADRESS) {
        size_t const capacity = stk->capacity;

        stk->array = (type*) realloc (stk->array, (capacity + 2) * sizeof (type));
        if (stk->array) {
            for (int ind = capacity; ind > 0; ind--) {
                stk->array[ind + 1] = stk->array[ind];
            }
            (stk->array) [0] = LEFT;
            (stk->array) [capacity + 1] = RIGHT;
            stk->canary_indicator = 1;
        }
        else {
            printf ("memory cannot be allocated");
        }
    }
    return StackVerify(stk);
}
