#include <stdlib.h>
#include <stdio.h>

#define LEFT 0x7BADF00D
#define RIGHT 0x7EADBEEF


typedef int type;

enum StackErr_t {
    OKEY = 0,
    ADRESS = 1,
    ADRESS_A = 2,
    NOTENOUGH = 3,
    CAPACITY = 4,
    CANARY_L = 5,
    CANARY_R = 6,
};

typedef struct {
    int* array;
    size_t size;
    size_t capacity;
    size_t canary_indicator;
} stack_t; //where is better

StackErr_t canary(stack_t* stk);
StackErr_t StackInit (stack_t* stk, size_t capacity, size_t value);
type StackPop (stack_t* stk);
StackErr_t StackPush (stack_t* stk, type value);
StackErr_t StackVerify(stack_t* stk);
void StackDump (stack_t* stk, size_t line);
void StackDestroy (stack_t* stk);

  