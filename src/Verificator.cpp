#include "stack.h"

StackErr_t StackVerify(stack_t* stk) {
    StackErr_t err = OKEY;
    if (stk == NULL) {
        err = ADRESS;
        fprintf (stderr, "errorcode %d : the adress of your stack is wrong\n\n", err);
    }

    if (err == ADRESS) {
        abort();
    }

    if (stk -> array == NULL) {
        fprintf (stderr, "erorrcode %d : the adress of your buffer is wrong\n\n", err);
        err = ADRESS_A;
    }
    if (stk -> size > stk -> capacity && stk -> err == OKEY) {
        stk -> err = CAPACITY;
        fprintf (stderr, "errorcode %d : size > capacity\n\n", stk -> err);
    }
    if (stk -> canary_indicator && err != ADRESS_A) {
        if ((stk -> array)[0] != LEFT) {
            stk -> err = CANARY_L;
            fprintf (stderr, "errorcode %d : left canary is dead, something is changing your buffer\n\n", stk -> err);
        }
        if ((stk -> array)[stk -> capacity + 1] != RIGHT) {
            stk -> err = CANARY_R;
            fprintf (stderr, "errorcode %d : right canary is dead, something is changing your buffer\n\n", stk -> err);
        }
    }
    return stk -> err;
}