#include <stdlib.h>
#include <stdio.h>

#include "Consts.h"
#include "Verificator.h"

StackErr_t StackPop (stack_t* stk, type* value, size_t indicator ,StackErr_t* err);
StackErr_t StackPush (stack_t* stk, type value, size_t indicator ,StackErr_t* err);