#include "SPU.h"

int main() {
    SPU_t SPU1 = {};
    FILE* bytecode = fopen ("asm+SPU/asambler+bytecode/bytecode.txt", "rb");
    SPUInit (&SPU1, bytecode, sizeof(type));
}

SPUErorr_t SPUInit( SPU_t* spu, FILE* bytecode, size_t value) {
    if (bytecode && spu) {

        size_t capacity = Capacity(bytecode);
        

        printf ("capacity: %lu\n", capacity);
        


        //StackInit(&(spu->stack), )
    }
    return STACK;
}

size_t Capacity (FILE* bytecode) {
    char* buffer = ReadBuffer(bytecode);
    int capacity = atoi(strchr(buffer, '|') + 1);
    free (buffer);
    return capacity;
}