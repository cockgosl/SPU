#include "SPU.h"

int main() {
    SPU_t SPU1 = {};
    FILE* bytecode = fopen ("asm+SPU/asambler+bytecode/bytecode.txt", "rb");
    SPUInit (&SPU1, bytecode, sizeof(type));

    SPUDo (&SPU1);
    
    SPUDestroy(&SPU1);
}

SPUErorr_t SPUInit( SPU_t* spu, FILE* bytecode, size_t value) {
    if (bytecode && spu) {

        StackInit (&(spu->stack), 5, value);

        ByteCodeInit(spu, bytecode, value);
        
    }
    return STACK;
}

void SPUDestroy (SPU_t* spu) {
    StackDestroy(&(spu->stack));
    free(spu->Bytecode);
    spu->InstrPointer = 0;
    for (int i; i < 17; i++) {
        (spu->Register)[i] = 0;
    }
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
    //temporary variables that are used in the process of calculating
    type temp1 = 0;
    type temp2 = 0;
    char tempstr[100] = {};
    double tempd = NAN;

    
    size_t indicator = 0;
    size_t crytieria = 0;


    while (1) {
        switch ((spu->Bytecode)[spu->InstrPointer]) {
            case 1:
                spu->InstrPointer++;
                StackPush (&(spu->stack), (spu->Bytecode)[spu->InstrPointer]);
                spu->InstrPointer++;
                break;
            case 2:
                spu->InstrPointer++;
                printf ("OUT: %d\n", StackPop(&(spu->stack)));
                break;
            case 3:
                spu->InstrPointer++;
                StackPush (&(spu->stack), StackPop(&(spu->stack)) + StackPop(&(spu->stack)) );
                break;
            case 4:
                spu->InstrPointer++;
                temp1 = StackPop(&(spu->stack));
                temp1 = temp1 - StackPop(&(spu->stack));
                StackPush (&(spu->stack), temp1);
                temp1 = 0;
                break;
            case 5:
                spu->InstrPointer++;
                StackPush (&(spu->stack), StackPop(&(spu->stack)) * StackPop(&(spu->stack)));
                break;
            case 6:
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
            case 7:
                spu->InstrPointer++;
                temp1 = StackPop(&(spu->stack));
                tempd = sqrt(double (temp1));
                sprintf(tempstr, "%.0f", tempd);
                temp1 = atoi (tempstr);
                StackPush (&(spu->stack), temp1);
                for (int i; i < 100; i++) {
                    tempstr[i] = 0;
                }
                tempd = 0;
                temp1 = 0;
                break;
            case 16:
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
            case 33:
                spu->InstrPointer++;
                switch((spu->Bytecode)[spu->InstrPointer]) {
                    //We need to know about the condition of the register, the first digit in Register contains information about it
                    case 1:
                        (spu->Register)[1] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 1;
                        spu->InstrPointer++; // 2^0
                        break;
                    case 2:
                        (spu->Register)[2] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 2;
                        spu->InstrPointer++; //2^1
                        break;
                    case 3:
                        (spu->Register)[3] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 4;
                        spu->InstrPointer++; //2^2
                        break;
                    case 4:
                        (spu->Register)[4] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 8;
                        spu->InstrPointer++; //2^3
                        break;
                    case 5:
                        (spu->Register)[5] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 16;
                        spu->InstrPointer++; //2^4 and so on
                        break;
                    case 6:
                        (spu->Register)[6] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 32;
                        spu->InstrPointer++;
                        break;
                    case 7:
                        (spu->Register)[7] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 64;
                        spu->InstrPointer++;
                        break;
                    case 8:
                        (spu->Register)[8] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 128;
                        spu->InstrPointer++;
                        break;
                    case 9:
                        (spu->Register)[9] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 256;
                        spu->InstrPointer++;
                        break;
                    case 10:
                        (spu->Register)[10] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 512;
                        spu->InstrPointer++;
                        break;
                    case 11:
                        (spu->Register)[11] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 1024;
                        spu->InstrPointer++;
                        break;
                    case 12:
                        (spu->Register)[12] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 2048;
                        spu->InstrPointer++;
                        break;
                    case 13:
                        (spu->Register)[13] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 4096;
                        spu->InstrPointer++;
                        break;
                    case 14:
                        (spu->Register)[14] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 8192;
                        spu->InstrPointer++;
                        break;
                    case 15:
                        (spu->Register)[15] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 16384;
                        spu->InstrPointer++;
                        break;
                    case 16:
                        (spu->Register)[16] = StackPop(&(spu->stack));
                        (spu->Register)[0] += 32768;
                        spu->InstrPointer++;
                        break;
                    default:
                        break;
                }
                break;
            case 42:
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
            case 50:
                spu->InstrPointer++;
                spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                break;
            case 51:
                spu->InstrPointer++;
                temp1 = StackPop(&(spu->stack));
                temp2 = StackPop(&(spu->stack));
                if (temp1 != temp2) {
                    spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                }
                else {
                    spu->InstrPointer++;
                    StackPush (&(spu->stack), temp2);
                    StackPush (&(spu->stack), temp1);
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case 52:
                spu->InstrPointer++;
                temp1 = StackPop(&(spu->stack));
                temp2 = StackPop(&(spu->stack));
                if (temp1 == temp2) {
                    spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                }
                else {
                    spu->InstrPointer++;
                    StackPush (&(spu->stack), temp2);
                    StackPush (&(spu->stack), temp1);
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case 53:
                spu->InstrPointer++;
                temp1 = StackPop (&(spu->stack));
                temp2 = StackPop (&(spu->stack));
                if (temp1 >= temp2) {
                    spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                }
                else {
                    spu->InstrPointer++;
                    StackPush (&(spu->stack), temp2);
                    StackPush (&(spu->stack), temp1);
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case 54:
                spu->InstrPointer++;
                temp1 = StackPop (&(spu->stack));
                temp2 = StackPop (&(spu->stack));
                if (temp1 <= temp2) {
                    spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                }
                else {
                    spu->InstrPointer++;
                    StackPush (&(spu->stack), temp2);
                    StackPush (&(spu->stack), temp1);
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case 55:
                spu->InstrPointer++;
                temp1 = StackPop (&(spu->stack));
                temp2 = StackPop (&(spu->stack));
                if (temp1 > temp2) {
                    spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                }
                else {
                    spu->InstrPointer++;
                    StackPush (&(spu->stack), temp2);
                    StackPush (&(spu->stack), temp1);
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case 56:
                spu->InstrPointer++;
                temp1 = StackPop (&(spu->stack));
                temp2 = StackPop (&(spu->stack));
                if (temp1 < temp2) {
                    spu->InstrPointer = (spu->Bytecode)[spu->InstrPointer];
                }
                else {
                    spu->InstrPointer++;
                    StackPush (&(spu->stack), temp2);
                    StackPush (&(spu->stack), temp1);
                }
                temp1 = 0;
                temp2 = 0;
                break;
            case 0:
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
    return STACK;
}