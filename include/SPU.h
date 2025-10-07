#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "stack.h"

typedef int type;

enum SPUErorr_t {
    STACK = 0,
    
};

typedef struct {
    stack_t stack = {};
    type* Bytecode;
    int InstrPointer;
    type* Register;
}   SPU_t;

SPUErorr_t SPUInit( SPU_t* spu, FILE* bytecode, size_t value);
size_t Capacity (FILE* bytecode);
char* ReadBuffer(FILE* text);