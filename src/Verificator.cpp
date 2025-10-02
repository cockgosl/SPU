#include "Verificator.h"

StackErr_t StackVerify(stack_t* stk, size_t indicator, StackErr_t* err){
    if (stk == NULL) {
        *err = ADRESS;
        printf ("errorcode %d : the adress of your stack is wrong\n\n", *err);
    }
    if (stk -> array == NULL) {
        *err = ADRESS_A;
        printf ("erorrcode %d : the adress of your buffer is wrong\n\n", *err);
    }
    if (stk -> size > stk -> capacity && *err == OKEY) {
        *err = CAPACITY;
        printf ("errorcode %d : size > capacity\n\n", *err);
    }
    if (indicator) {
        if ((stk -> array)[0] != LEFT) {
            *err = CANARY_L;
            printf ("errorcode %d : left canary is dead, something is changing your buffer\n\n", *err);
        }
        if ((stk -> array)[stk -> capacity + 1] != RIGHT) {
            *err = CANARY_R;
            printf ("errorcode %d : right canary is dead, something is changing your buffer\n\n", *err);
        }
    }
    return *err;
}