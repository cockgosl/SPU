#include "SPU.h"

#define JUMP_CHECK(command, CONDITION)\
    case command:\
        spu->InstrPointer++;\
        temp1 = StackPop(&(spu->stack));\
        temp2 = StackPop(&(spu->stack));\
        if (temp1 CONDITION temp2) {\
            spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];\
        }\
        else {\
            spu->InstrPointer++;\
            StackPush (&(spu->stack), temp2);\
            StackPush (&(spu->stack), temp1);\
        }\
        temp1 = 0;\
        temp2 = 0;\
        break;

int main() {
    SPU_t SPU1 = {};
    FILE* bytecode = fopen ("asm+SPU/asambler+bytecode/bytecode.txt", "rb");
    if (bytecode == NULL) {
        printf ("something is wrong with FILE");
        return 0;
    }

    SPUInit (&SPU1, bytecode, sizeof(type));

    SPUDo (&SPU1);
    
    SPUDestroy(&SPU1);
}


void SPUInit (SPU_t* spu, FILE* bytecode, size_t value) {
    if (bytecode && spu) {

        StackInit (&(spu->stack), 5, value);

        StackInit (&(spu->retAddr), 5, value);

        ByteCodeInit(spu, bytecode, value);
        
        RamInit (spu);

    }
    else {
        printf ("It canot be initialized, something is wrong with files");
    }
}

void SPUDestroy (SPU_t* spu) {
    StackDestroy(&(spu->stack));
    StackDestroy(&(spu->retAddr));
    free(spu->Bytecode);
    free(spu->RAM);
    spu->InstrPointer = 0;
    for (int i; i < 17; i++) {
        (spu->Register)[i] = 0;
    }
}

void ByteCodeInit (SPU_t* spu, FILE* bytecode, size_t value) {
    char* buffer = ReadBuffer(bytecode);
    int capacity = atoi(strchr(buffer, '|') + 1);

    spu->Bytecode = (type*) calloc (capacity, value);

    size_t in = 0;

    while (buffer[in] != '\0') { 
        if (buffer[in] == ' ') { 
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
}

void RamInit (SPU_t* spu) {
    spu->RAM = (type*) (calloc(100, sizeof(type)));
}


void SPUDo (SPU_t* spu) {
    //temporary variables that are used in the process of calculating
    type temp1 = 0;
    type temp2 = 0;
    char tempstr[100] = {};
    double tempd = NAN;

    
    size_t indicator = 0;
    size_t crytieria = 0;

    while (1) {
        switch ((spu->Bytecode)[spu->InstrPointer]) {
            case PUSH:
                spu->InstrPointer++;
                StackPush (&(spu->stack), (spu->Bytecode)[spu->InstrPointer]);
                spu->InstrPointer++;
                break;
            case OUT:
                spu->InstrPointer++;
                printf ("OUT: %d\n", StackPop(&(spu->stack)));
                break;
            case ADD:
                spu->InstrPointer++;
                StackPush (&(spu->stack), StackPop(&(spu->stack)) + StackPop(&(spu->stack)) );
                break;
            case SUB:
                spu->InstrPointer++;
                temp1 = StackPop(&(spu->stack));
                temp1 = temp1 - StackPop(&(spu->stack));
                StackPush (&(spu->stack), temp1);
                temp1 = 0;
                break;
            case MUL:
                spu->InstrPointer++;
                StackPush (&(spu->stack), StackPop(&(spu->stack)) * StackPop(&(spu->stack)));
                break;
            case DIV:
                spu->InstrPointer++;
                temp1 = StackPop(&(spu->stack));
                temp2 = StackPop(&(spu->stack));
                if (temp2) {
                    StackPush (&(spu->stack), temp1 / temp2);
                }
                else {
                    printf ("division on zero\n");
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case SQRT:
                spu->InstrPointer++;
                temp1 = int(StackPop(&(spu->stack)));
                temp1 = int(sqrt (double (temp1)));
                StackPush (&(spu->stack), temp1);
                temp1 = 0;
                break;
            case IN:
                spu->InstrPointer++;
                while (temp1 != 1 ) {
                    printf ("write the value you want to PUSH: ");
                    crytieria = scanf ("%d", &temp2);
                    if (crytieria == 1) {
                        StackPush(&(spu->stack), temp2);
                        temp1 = 1;
                    }
                    else {
                        printf("Error in input, try one more time\n");
                        while (getchar() != '\n');
                    }
                }
                printf("\n");
                temp1 = 0;
                crytieria = 0;
                temp2 = 0;
                break;
            case POPR:
                spu->InstrPointer++;
                //We need to know about the condition of the register, the first digit in Register contains information about it
                for (int c = 1; c < 17; c++) {
                    if ((spu->Bytecode)[spu->InstrPointer] == c) {
                        (spu->Register)[c] = StackPop(&(spu->stack));
                        (spu->Register)[0] += int (pow(2, c-1));
                        spu->InstrPointer++;
                    }
                }
                break;
            case PUSHR:
                //We need to know about the condition of the register, the first digit in Register contains information about it
                spu->InstrPointer++;
                crytieria = (size_t)(pow(2,(spu->Bytecode)[spu->InstrPointer]-1));
                if (((spu->Register)[0] & crytieria) >= (spu->Bytecode)[spu->InstrPointer]){
                    StackPush (&(spu->stack), spu->Register[(spu->Bytecode)[spu->InstrPointer]]);
                }
                else {
                    printf("invalid instruction(Register is empty)\n");
                }
                spu->InstrPointer++;
                crytieria = 0;
                break;
            case CALL:
                spu->InstrPointer++;
                StackPush (&(spu->retAddr), (spu->Bytecode)[spu->InstrPointer + 1]);
                spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                break;
            case RET:
                spu->InstrPointer = StackPop (&(spu->retAddr));
                break;
            case JMPD:
                spu->InstrPointer++;
                spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                break;
            JUMP_CHECK(JMPNE, !=)

            JUMP_CHECK(JMPE, ==)

            JUMP_CHECK(JMPAE, >=)

            JUMP_CHECK(JMPBE, <=)

            JUMP_CHECK(JMPA, >)

            JUMP_CHECK(JMPB, <)

            case DRAW:
                for (int i = 0; i < 100; i ++) {
                    printf ("%d", (spu->RAM)[i]);
                    if ((i + 1) % 10 == 0) {
                        printf ("\n");
                    }
                }
                printf ("\n");
                break;

            case HLT:
                printf("the end of process, value: %d\n", (spu->stack).array[0]);
                spu->InstrPointer = 0;
                indicator = 1;
                break;
            default:
                break;
        }
        if (indicator) {
            break;
        }  
    }
}