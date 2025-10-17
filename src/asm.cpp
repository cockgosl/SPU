#include "SPU.h"

int main (int argc, char* argv[]) {

    size_t counter = 0;

    size_t PassageNumber = 1;

    int labels[10] = {};

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
                if (buffer[in] == '\n' || buffer[in] == ' ' || buffer[in] == '\r') { 
                buffer[in] = '\0';
                }
            }

            char* pointer = buffer;

            while ( pointer < buffer + size ) {
                if (strcmp (pointer, "PUSH") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 1);
                    }
                    pointer += strlen ("PUSH");
                    while(!isalpha(*pointer)) {
                        if ((isdigit(*pointer) || (*pointer) == '-') && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        pointer++;
                        if (*pointer == ':') {
                            break;
                        }
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
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
                        labels[atoi(pointer)] = counter - 1; //index in bytecode must lack one in comparesent with counter
                    }
                    else {
                        printf ("label is incorrect\n");
                    }
                    while (!isalpha(*pointer)) {
                        pointer++;
                        if (*pointer == ':') {
                            break;
                        }
                    }
                    
                }
                else if (strcmp (pointer, "PUSHR") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 42);
                    }
                    pointer += strlen ("PUSHR");
                    while(!isalpha(*pointer)) {
                        pointer++;
                    }

                    if (strcmp (pointer, "RAX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 1);
                        }
                        pointer += strlen ("RAX");
                    }
                    else if (strcmp (pointer, "RBX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 2);
                        }
                        pointer += strlen ("RBX");
                    }
                    else if (strcmp (pointer, "RCX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 3);
                        }
                        pointer += strlen ("RCX");
                    }
                    else if (strcmp (pointer, "RDX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 4);
                        }
                        pointer += strlen ("RDX");
                    }
                    else if (strcmp (pointer, "REX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 5);
                        }
                        pointer += strlen ("REX");
                    }
                    else if (strcmp (pointer, "RFX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 6);
                        }
                        pointer += strlen ("RFX");
                    }
                    else if (strcmp (pointer, "RGX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 7);
                        }
                        pointer += strlen ("RGX");
                    }
                    else if (strcmp (pointer, "RHX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 8);
                        }
                        pointer += strlen ("RHX");
                    }
                    else if (strcmp (pointer, "RIX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 9);
                        }
                        pointer += strlen ("RIX");
                    }
                    else if (strcmp (pointer, "RJX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 10);
                        }
                        pointer += strlen ("RJX");
                    }
                    else if (strcmp (pointer, "RKX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 11);
                        }
                        pointer += strlen ("RKX");
                    }
                    else if (strcmp (pointer, "RLX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 12);
                        }
                        pointer += strlen ("RLX");
                    }
                    else if (strcmp (pointer, "RMX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 13);
                        }
                        pointer += strlen ("RMX");
                    }
                    else if (strcmp (pointer, "RNX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 14);
                        }
                        pointer += strlen ("RNX");
                    }
                    else if (strcmp (pointer, "ROX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 15);
                        }
                        pointer += strlen ("ROX");
                    }
                    else if (strcmp (pointer, "RPX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 16);
                        }
                        pointer += strlen ("RPX");
                    }
                    else {
                        ;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }  

                else if (strcmp (pointer, "OUT") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 2);
                    }
                    pointer += strlen ("OUT");
                }
                else if (strcmp (pointer, "POPR") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 33);
                    }
                    pointer += strlen ("POPR");
                    
                    while(!isalpha(*pointer)) {
                        pointer++;
                    }

                    if (strcmp (pointer, "RAX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 1);
                        }
                        pointer += strlen ("RAX");
                    }
                    else if (strcmp (pointer, "RBX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 2);
                        }
                        pointer += strlen ("RBX");
                    }
                    else if (strcmp (pointer, "RCX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 3);
                        }
                        pointer += strlen ("RCX");
                    }
                    else if (strcmp (pointer, "RDX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 4);
                        }
                        pointer += strlen ("RDX");
                    }
                    else if (strcmp (pointer, "REX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 5);
                        }
                        pointer += strlen ("REX");
                    }
                    else if (strcmp (pointer, "RFX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 6);
                        }
                        pointer += strlen ("RFX");
                    }
                    else if (strcmp (pointer, "RGX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 7);
                        }
                        pointer += strlen ("RGX");
                    }
                    else if (strcmp (pointer, "RHX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 8);
                        }
                        pointer += strlen ("RHX");
                    }
                    else if (strcmp (pointer, "RIX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 9);
                        }
                        pointer += strlen ("RIX");
                    }
                    else if (strcmp (pointer, "RJX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 10);
                        }
                        pointer += strlen ("RJX");
                    }
                    else if (strcmp (pointer, "RKX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 11);
                        }
                        pointer += strlen ("RKX");
                    }
                    else if (strcmp (pointer, "RLX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 12);
                        }
                        pointer += strlen ("RLX");
                    }
                    else if (strcmp (pointer, "RMX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 13);
                        }
                        pointer += strlen ("RMX");
                    }
                    else if (strcmp (pointer, "RNX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 14);
                        }
                        pointer += strlen ("RNX");
                    }
                    else if (strcmp (pointer, "ROX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 15);
                        }
                        pointer += strlen ("ROX");
                    }
                    else if (strcmp (pointer, "RPX") == 0) {
                        if (PassageNumber == 2) {
                            fprintf (output, "%d", 16);
                        }
                        pointer += strlen ("RPX");
                    }
                    else {
                        ;
                    }
                    if (PassageNumber == 2) {
                            fprintf (output, ",");
                        }
                    counter++;
                }
                else if (strcmp (pointer, "ADD") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 3);
                    }
                    pointer += strlen ("ADD");
                }
                else if (strcmp (pointer, "SUB") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 4);
                    }
                    pointer += strlen ("SUB");
                }
                else if (strcmp (pointer, "MUL") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 5);
                    }
                    pointer += strlen ("MUL");
                }
                else if (strcmp (pointer, "DIV") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 6);
                    }
                    pointer += strlen ("DIV");
                }
                else if (strcmp (pointer, "SQRT") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 7);
                    }
                    pointer += strlen ("SQRT");
                }
                else if (strcmp (pointer , "IN") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 16);
                    }
                    pointer += strlen ("IN");
                }
                else if (strcmp (pointer , "CALL") == 0 ) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 48);
                    }
                    pointer += strlen ("CALL");
                    pointer += 1; //skiping backspace
                    if (*pointer == ':') {
                        pointer++;
                        if (isdigit(*pointer)) {
                            if (PassageNumber == 2) {
                                counter++;
                                fprintf (output, "%d,", labels[*pointer - '0']);
                                counter++;
                                fprintf (output, "%lu,", counter);
                            }
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
                else if (strcmp (pointer , "JMP") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 50);
                    }
                    pointer += strlen ("JMP");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (strcmp (pointer , "JNE") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 51);
                    }
                    pointer += strlen ("JNE");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (strcmp (pointer , "JE") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 52);
                    }
                    pointer += strlen ("JE");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (strcmp (pointer , "JAE") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 53);
                    }
                    pointer += strlen ("JAE");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (strcmp (pointer , "JBE") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 54);
                    }
                    pointer += strlen ("JBE");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (strcmp (pointer , "JA") == 0){
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 55);
                    }
                    pointer += strlen ("JA");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (strcmp (pointer , "JB") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d,", 56);
                    }
                    pointer += strlen ("JB");
                    while(!isalpha(*pointer)) {
                        if (isdigit(*pointer) && PassageNumber == 2) {
                            fprintf (output, "%c", *pointer );
                        }
                        if (*pointer == ':') {
                            pointer++;
                            if (isdigit (*pointer)) {
                                if (PassageNumber == 2) {
                                    fprintf (output, "%d", labels[*pointer - '0']);
                                }
                            }
                            else {
                                printf ("syntax error\n");
                            }
                        }
                        pointer++;
                    }
                    if (PassageNumber == 2) {
                        fprintf (output, ",");
                    }
                    counter++;
                }
                else if (*pointer == '\0') {
                    pointer++;
                }
                else if (strcmp (pointer, "HLT") == 0) {
                    counter++;
                    if (PassageNumber == 2) {
                        fprintf (output, "%d", 0);
                        fprintf (output, "|%lu", counter);
                        break;
                    }
                    else {
                        PassageNumber = 2;
                        pointer = buffer;
                        counter = 0;
                    }
                }
                else {
                    fprintf (stderr, "syntax error\n");
                    pointer++;
                }
            }
        free(buffer);
        }
        else {
            printf ("can't read the given files\n");
        }
    }
    else {
            printf("the amount of arguments in terminal is wrong\n");
    }
}



