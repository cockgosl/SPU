#ifndef VERIF_H
#define VERIF_H

#include <stdio.h>

#include "Consts.h"

StackErr_t StackVerify(stack_t* stk, size_t indicator,  StackErr_t* err);
#endif