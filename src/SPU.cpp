#include "SPU.h"

int main() {
    SPU_t SPU1 = {};
    FILE* bytecode = fopen ("asm+SPU/asambler+bytecode/bytecode.txt", "rb");
    SPUInit (&SPU1, bytecode, sizeof(type));

    SPUDo (&SPU1);

}

SPUErorr_t SPUInit( SPU_t* spu, FILE* bytecode, size_t value) {
    if (bytecode && spu) {

        StackInit (&(spu->stack), 5, value);

        ByteCodeInit(spu, bytecode, value);
        
    }
    return STACK;
}

SPUErorr_t SPUDestroy (SPU_t* spu) {
    return STACK;
}

SPUErorr_t ByteCodeInit (SPU_t* spu, FILE* bytecode, size_t value) {
    char* buffer = ReadBuffer(bytecode);
    int capacity = atoi(strchr(buffer, '|') + 1);

    spu->Bytecode = (type*) calloc (capacity, value);

    size_t in = 0;

    while (buffer[in] != '\0' || buffer[in] == '|') { 
        if (buffer[in] == ',') { 
            buffer[in] = '\0';
        }
        in++;
    }

    char* pointer = buffer;

    for (size_t counter = 0; counter < capacity; counter++) {
        (spu->Bytecode)[counter] = atoi (pointer);
        pointer += strlen(pointer) + 1;
    }

    free (buffer);
    return STACK;
}

SPUErorr_t SPUDo (SPU_t* spu) {
    type temp = 0;
    char tempstr[100] = {};
    double tempd = NAN;

    type value = 0;
    size_t capacity = 1;
    size_t indicator = 0;

    for (size_t in = 0; spu->Bytecode[in] != 0; in++) {
        capacity++;
    }

    for (size_t in = 0; in < capacity; in++) {
        switch ((spu->Bytecode)[spu->InstrPointer]) {
            case 1:
                spu->InstrPointer++;
                StackPush (&(spu->stack), (spu->Bytecode)[spu->InstrPointer]);
                spu->InstrPointer++;
                break;
            case 2:
                spu->InstrPointer++;
                StackPop (&(spu->stack), &value);
                break;
            case 3:
                spu->InstrPointer++;
                StackPop (&(spu->stack), &value);
                temp += value;
                value = 0;
                StackPop (&(spu->stack), &value);
                temp += value;
                StackPush (&(spu->stack), temp);
                value = 0;
                temp = 0;
                break;
            case 4:
                spu->InstrPointer++;
                StackPop (&(spu->stack), &value);
                temp = value;
                StackPop (&(spu->stack), &value);
                value = temp - value;
                StackPush (&(spu->stack), value);
                break;
                temp = 0;
            case 5:
                spu->InstrPointer++;
                StackPop (&(spu->stack), &value);
                temp = value;
                StackPop (&(spu->stack), &value);
                value = value* temp;
                StackPush (&(spu->stack), value);
                break;
                temp = 0;
            case 6:
                spu->InstrPointer++;
                StackDump(&(spu->stack), 1);
                StackPop (&(spu->stack), &value);
                temp = value;
                StackPop (&(spu->stack), &value);
                if (value) {
                    value = temp / value;
                    StackPush (&(spu->stack), value);
                }
                else {
                    printf ("division on zero\n");
                }
                temp = 0;
                break;
            case 7:
                spu->InstrPointer++;
                StackPop (&(spu->stack), &value);
                tempd = sqrt(double (value));
                sprintf(tempstr, "%.0f", tempd);
                value = atoi (tempstr);
                StackPush (&(spu->stack), value);
                for (int i; i < 100; i++) {
                    tempstr[i] = 0;
                }
                tempd = 0;
                break;
            case 42:
                ;
            case 0:
                printf("the end of process, value: %d\n", (spu->stack).array[0]);
                spu->InstrPointer = 0;
                indicator = 1;
                break;
        }
        if (indicator) {
            break;
        }  
    }
    return STACK;
}