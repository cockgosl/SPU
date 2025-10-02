#ifndef CONST_H
#define CONST_H

#include <stdlib.h>

#define LEFT 0x7BADF00D
#define RIGHT 0x7EADBEEF

    

typedef int type;

enum StackErr_t {
    OKEY = 0,
    ADRESS = 1,
    ADRESS_A = 2,
    CAPACITY = 3,
    CANARY_L = 4,
    CANARY_R = 5,
};

typedef struct { //why isn't it global? is it possible?
    int* array;
    size_t size;
    size_t capacity;
} stack_t; //where is better

#endif  