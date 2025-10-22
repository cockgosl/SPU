#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"

typedef int type;


enum cases {
    HLT = 0,
    PUSH = 1,
    OUT = 'O' * 10 + 'U',
    ADD = 'A' * 10 + 'D',
    SUB = 'S' * 10 + 'U',
    MUL = 'M' * 10 + 'U',
    DIV = 'D' * 10 + 'I',
    SQRT = 'S' * 10 + 'Q',
    IN = 'I' * 10 + 'N',
    RET = 'R' * 10 + 'E',
    POPR = 33,
    PUSHR = 42,
    CALL = 48,
    JMPD = 'D',
    JMPNE = 'N' + 'E',
    JMPE = 'E',
    JMPAE = 'A' + 'E',
    JMPBE = 'B' + 'E',
    JMPA = 'A',
    JMPB = 'B',
    DRAW = 'D' * 10 + 'R',
};

typedef struct {
    stack_t stack = {};
    stack_t retAddr = {};
    type* Bytecode;
    type* RAM = NULL;
    int InstrPointer = 0;
    type Register[17] = {};
}   SPU_t;

void SPUInit( SPU_t* spu, FILE* bytecode, size_t value);
void SPUDestroy (SPU_t* spu);
void ByteCodeInit (SPU_t* spu, FILE* bytecode, size_t value);
void RamInit (SPU_t* spu);
void SPUDo (SPU_t* spu);
char* ReadBuffer(FILE* text);