#include "stack.h"

int main() {
    stack_t stk1 = {};
    int top_element = 0;

    printf ("stackinit:%d\n" , StackInit (&stk1, 3, sizeof (type)));

    canary (&stk1);

    StackDump (&stk1, __LINE__);

    for (size_t r = 0; r < 6; r++) {
        StackPush(&stk1, r);
    }

    for (size_t i = 1; i < stk1.capacity + 1; i++) {
        printf ("%d\n", (stk1.array)[i]);
    }


    for (int i = 0; i < 10; i++) {
        StackPop(&stk1, &top_element);
        printf ("top_element: %d\n\n", top_element);
    }

    for (size_t r = 0; r < 6; r++) {
        StackPush(&stk1, r);
    }
    
    StackDestroy (&stk1);

    StackDump(&stk1, __LINE__);
}