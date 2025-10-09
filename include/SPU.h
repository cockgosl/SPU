#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"

typedef int type;

enum SPUErorr_t {
    STACK = 0,
    
};

typedef struct {
    stack_t stack = {};
    type* Bytecode;
    int InstrPointer = 0;
    type Register[17] = {};
}   SPU_t;

SPUErorr_t SPUInit( SPU_t* spu, FILE* bytecode, size_t value);
void SPUDestroy (SPU_t* spu);
SPUErorr_t ByteCodeInit (SPU_t* spu, FILE* bytecode, size_t value);
SPUErorr_t SPUDo (SPU_t* spu);
char* ReadBuffer(FILE* text);