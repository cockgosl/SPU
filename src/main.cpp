#include "stack.h"

int main() {
    stack_t stk1 = {OKEY};
    int top_element = 0;

    StackInit (&stk1 , 3, sizeof (type));
    for (size_t r = 0; r < 6; r++) {
        StackPush(&stk1, r);
    }

    for (size_t i = 0; i < stk1.capacity; i++) {
        printf ("%d\n", (stk1.array)[i]);
    }

    canary (&stk1);

    while (stk1.size > 0) {
        StackPop(&stk1, &top_element);
        printf ("top_element: %d\n\n", top_element);
    }

    for (size_t r = 0; r < 6; r++) {
        StackPush(&stk1, r);
    }
    free (stk1.array);
    stk1.canary_indicator = 0;
}