#include <stdlib.h>
#include <stdio.h>

#define LEFT 0x7BADF00D
#define RIGHT 0x7EADBEEF

#define DEBUG 1
#ifndef DEBUG
#define StackPop (stack_t* stk, type* value ,StackErr_t* err) StackPop (stack_t* stk, type* value , size_t line, StackErr_t* err) 
#define  StackErr_t* err __LINE__, StackErr_t*
#define DEBUG 1
#endif  

typedef int type;

enum StackErr_t {
    OKEY = 0,
    ADRESS = 1,
    ADRESS_A = 2,
    CAPACITY = 3,
    CANARY_L = 4,
    CANARY_R = 5,
};

typedef struct {
    int* array;
    size_t size;
    size_t capacity;
    size_t canary_indicator;
} stack_t; //where is better

StackErr_t canary(stack_t* stk, StackErr_t* err);
StackErr_t StackInit (stack_t* stk, size_t capacity, size_t value, StackErr_t* err);
StackErr_t StackPop (stack_t* stk, type* value ,StackErr_t* err);
StackErr_t StackPush (stack_t* stk, type value, StackErr_t* err);
StackErr_t StackVerify(stack_t* stk,  StackErr_t* err);

  