#include "stack.h"

void StackDestroy (stack_t* stk) {
    if (stk) {
        free (stk->array);
        stk->size = 0;
        stk->capacity = 0;
        stk->canary_indicator = 0;
        stk->array = NULL;
    }
    else {
        printf("you want to destroy imaganary stk(&stk == NULL)");
    }
}