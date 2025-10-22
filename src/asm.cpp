#include "SPU.h"

#define ONE_REG_CHECK(Register)\
    if (strcmp (pointer, "R" #Register "X") == 0) {\
        sprintf (Bytecode, "%d", #Register[0] - 'A' + 1);\
        capacity++;\
        if ((#Register[0] - 'A' + 1) >= 10 && (#Register[0] - 'A' + 1 <= 16)) {\
            Bytecode += 3;\
        }\
        else {\
            Bytecode += 2;\
        }\
        pointer += strlen ("R" #Register "X");\
    }\

#define All_Reg_Check\
    ONE_REG_CHECK(A)\
    ONE_REG_CHECK(B)\
    ONE_REG_CHECK(C)\
    ONE_REG_CHECK(D)\
    ONE_REG_CHECK(E)\
    ONE_REG_CHECK(F)\
    ONE_REG_CHECK(G)\
    ONE_REG_CHECK(H)\
    ONE_REG_CHECK(I)\
    ONE_REG_CHECK(J)\
    ONE_REG_CHECK(K)\
    ONE_REG_CHECK(L)\
    ONE_REG_CHECK(M)\
    ONE_REG_CHECK(N)\
    ONE_REG_CHECK(O)\
    ONE_REG_CHECK(P)\


#define ONE_JUMP_CHECK(JUMP)\
    else if (strcmp (pointer , "JMP" #JUMP "") == 0) {\
        counter++;\
        if (strlen (#JUMP) == 2) {\
            sprintf (Bytecode, "%d", #JUMP[0] + #JUMP[1]);\
        }\
        if (strlen (#JUMP) == 1) {\
            sprintf (Bytecode, "%d", #JUMP[0]);\
        }\
        capacity++;\
        Bytecode += strlen (Bytecode) + 1;\
        pointer += strlen ("JMP" #JUMP "") + 1;\
        while(isdigit(*pointer) || *pointer == ':') {\
            if (isdigit(*pointer)) {\
                sscanf (pointer, "%s", Bytecode );\
                capacity++;\
                Bytecode += strlen (pointer) + 1;\
                pointer += strlen (pointer);\
            }\
            else if (*pointer == ':') {\
                pointer++;\
                if (isdigit (*pointer)) {\
                    sprintf (Bytecode, "%d", labels[*pointer - '0']);\
                    capacity++;\
                    Bytecode += strlen (Bytecode) + 1;\
                }\
                else {\
                    printf ("syntax error\n");\
                }\
            }\
            else {\
                printf ("syntax error\n");\
            }\
            pointer++;\
        }\
        counter++;\
    }\

#define ALL_JUMPS_CHECK\
    ONE_JUMP_CHECK(D)\
    ONE_JUMP_CHECK(A)\
    ONE_JUMP_CHECK(B)\
    ONE_JUMP_CHECK(E)\
    ONE_JUMP_CHECK(NE)\
    ONE_JUMP_CHECK(AE)\
    ONE_JUMP_CHECK(BE)\

#define CHECK(COMMAND)\
    else if (strcmp (pointer, #COMMAND) == 0) {\
        counter++;\
        temp1 = #COMMAND[0] * 10 + #COMMAND[1];\
        sprintf(Bytecode, "%d", temp1);\
        capacity++;\
        Bytecode += strlen (Bytecode) + 1;\
        pointer += strlen (#COMMAND);\
        temp1 = 0;\
    }\

int main (int argc, char* argv[]) {

    size_t counter = 0;

    size_t PassageNumber = 1;

    int labels[10] = {};

    size_t capacity = 0;
    char* temp = NULL;

    int temp1 = 0;

    for (size_t in = 0; in < 10; in ++) {
        labels[in] = -1;
    }

    if (argc == 3) {
        FILE* source = fopen (argv[1], "rb" );
        FILE* output = fopen (argv[2], "wb");

        if (source && output) {
            char* buffer = ReadBuffer (source);
            assert (buffer);
            size_t size = strlen(buffer);

            for (size_t in = 0; in < size; in++) { 
                if (buffer[in] == '\n' || buffer[in] == ' ' || buffer[in] == '\r' ) { 
                buffer[in] = '\0';
                }
            }

            char* Bytecode = (char*)(calloc(size, sizeof(char)));
            temp = Bytecode;
            assert(Bytecode);

            char* pointer = buffer;

            while ( pointer < buffer + size ) {
                if (strcmp (pointer, "PUSH") == 0) {
                    counter++;
                    sprintf (Bytecode, "%d", PUSH);
                    Bytecode += strlen(Bytecode) + 1;
                    capacity++;
                    pointer += strlen ("PUSH") + 1; //skipping backspace
                    if (isdigit(*pointer) || (*pointer) == '-') {
                        sscanf (pointer, "%s", Bytecode);
                        Bytecode += strlen(pointer) + 1;
                        pointer += strlen(pointer);
                        capacity++;
                    }
                    else {
                        printf ("syntax error\n");
                    }
                    counter++;
                }
                else if (*pointer == ';') {
                    pointer++;
                    while (*pointer != ';') {
                        pointer++;
                    }
                    pointer++;
                }
                else if (*pointer == ':') {
                    pointer++;
                    if (atoi (pointer) > 0 ) {
                        if ((labels[atoi(pointer)] == -1 && PassageNumber == 2)) {
                            printf ("syntax error\n");
                        }
                        else if (labels[atoi(pointer)] != -1 && PassageNumber == 1) {
                            printf ("syntax error\n");
                        }
                        labels[atoi(pointer)] = counter ;
                    }
                    else {
                        printf ("label is incorrect\n");
                    }
                    while (!isalpha(*pointer) && *pointer != ';') {
                        pointer++;
                        if (*pointer == ':') {
                            break;
                        }
                    }
                    
                }
                else if (strcmp (pointer, "PUSHR") == 0) {
                    counter++;
                    sprintf(Bytecode, "%d", PUSHR);
                    capacity++;
                    Bytecode += strlen (Bytecode) + 1;
                    pointer += strlen ("PUSHR") + 1; //skipping backspace

                    All_Reg_Check

                    counter++;
                }  

                else if (strcmp (pointer, "POPR") == 0) {
                    counter++;
                    sprintf(Bytecode, "%d", POPR);
                    capacity++;
                    Bytecode += strlen ("33") + 1;
                    pointer += strlen ("POPR");
                    
                    while(!isalpha(*pointer) && *pointer != ';') {
                        pointer++;
                    }

                    All_Reg_Check

                    counter++;
                }

                else if (strcmp (pointer, "PUSHM") == 0) {
                    counter++;
                }

                CHECK(OUT)

                CHECK(ADD)

                CHECK(SUB)

                CHECK(MUL)

                CHECK(DIV)
                
                CHECK(SQRT)

                CHECK(IN)

                CHECK(RET)

                CHECK(DRAW)

                else if (strcmp (pointer , "CALL") == 0 ) {
                    counter++;
                    sscanf("48", "%s", Bytecode);
                    capacity++;
                    Bytecode += strlen ("48") + 1;
                    pointer += strlen ("CALL");
                    pointer += 1; //skiping backspace
                    if (*pointer == ':') {
                        pointer++;
                        if (isdigit(*pointer)) {
                            counter++;
                            counter++;
                            capacity++;
                            capacity++;
                            sprintf (Bytecode, "%d", labels[*pointer - '0']);
                            Bytecode += strlen (Bytecode) + 1;
                            sprintf (Bytecode, "%lu", counter);
                            Bytecode += strlen (Bytecode) + 1;
                            pointer += strlen (pointer);
                        }
                        else {
                            printf ("syntax error\n");
                        }
                    }
                    else {
                        printf ("syntax error\n");
                    }
                    pointer++;
                }

                ALL_JUMPS_CHECK //it is a macro that finds all jumps

                else if (*pointer == '\0') {
                    pointer++;
                }
                else if (strcmp (pointer, "HLT") == 0) {
                    counter++;
                    sscanf ("0", "%s", Bytecode);
                    capacity++;
                    Bytecode += strlen ("0") + 1;
                    strcat (Bytecode, "|");
                    sprintf (Bytecode + strlen("|"), "%lu", counter);
                    capacity++;
                    if (PassageNumber == 2) {
                        break;
                    }
                    else {
                        PassageNumber = 2;
                        Bytecode = temp;
                        pointer = buffer;
                        counter = 0;
                    }
                }
                else {
                    fprintf (stderr, "syntax error\n");
                    pointer++;
                }
            }
        Bytecode = temp;
        printf ("capacity %lu\n", capacity);
        for (size_t i; i < capacity / 2; i++) {
            fprintf (output, "%s ", temp);
            temp += strlen (temp) + 1;
        }

        free(buffer);
        free(Bytecode);
        }
        else {
            printf ("can't read the given files\n");
        }
    }
    else {
            printf("the amount of arguments in terminal is wrong\n");
    }
}

