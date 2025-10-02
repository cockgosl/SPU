#include "stack.h"

int main() {
    StackErr_t err = OKEY;
    stack_t stk1 = {};
    int top_element = 0;

    StackInit (&stk1, 3, sizeof (type), &err);
    for (size_t r = 0; r < 6; r++) {
        StackPush(&stk1, r, &err);
    }

    for (size_t i = 0; i < stk1.capacity; i++) {
        printf ("%d\n", (stk1.array)[i]);
    }

    canary (&stk1, &err);

    while (stk1.size > 0) {
        StackPop(&stk1, &top_element, &err);
        printf ("top_element: %d\n\n", top_element);
    }

    for (size_t r = 0; r < 6; r++) {
        StackPush(&stk1, r, &err);
    }
    free (stk1.array);
    stk1.canary_indicator = 0;
}