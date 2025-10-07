#include "stack.h"

void StackDump (stack_t* stk, size_t line) {
    printf("StackCondition on line: %lu\n", line);
    printf ("Stack[%p]: \n{\n", stk);
    if (stk) {
        printf ("array: %p\n", stk->array);
        printf ("size: %lu\n", stk->size);
        printf ("capacity: %lu\n", stk->capacity);
        printf ("canary_indicator: %lu\n}\n", stk->canary_indicator );

        printf ("the inside of the stack: \n{\n");
        for (int i = stk->canary_indicator, ind = 0; i < stk->capacity + stk->canary_indicator; ind++, i++) {
            printf ("array[%d]: %d\n", ind, stk->array[i]);
        }
        printf("}\n");
        printf ("\n");
    }

}