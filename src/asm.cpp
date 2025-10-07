#include "SPU.h"

int main (int argc, char* argv[]) {

    size_t counter = 0;

    if (argc == 3) {
        FILE* source = fopen (argv[1], "rb" );
        FILE* output = fopen (argv[2], "wb");

        if (source && output) {
            char* buffer = ReadBuffer (source);

            size_t in = 0;
            size_t size = strlen(buffer);

            while (buffer[in] != '\0') { 
                if (buffer[in] == '\n' || buffer[in] == ' ' || buffer[in] == '\r') { 
                buffer[in] = '\0';
                }
                in++;
            }

            char* pointer = buffer;

            while ( pointer < buffer + size) {

                if (strcmp (pointer, "PUSH") == 0) {
                    counter++;
                    fprintf (output, "%d", 1);
                    pointer += strlen ("PUSH");
                    while(!isalpha(*pointer)) {
                        if (*pointer != '\0') {
                            fprintf (output, "%c", *pointer );
                        }
                        pointer++;
                    }
                    counter++;
                } 
                else if (strcmp (pointer, "POP") == 0) {
                    counter++;
                    fprintf (output, "%d", 2);
                    pointer += strlen ("POP");
                }
                else if (strcmp (pointer, "ADD") == 0) {
                    counter++;
                    fprintf (output, "%d", 3);
                    pointer += strlen ("ADD");
                }
                else if (strcmp (pointer, "SUB") == 0) {
                    counter++;
                    fprintf (output, "%d", 4);
                    pointer += strlen ("SUB");
                }
                else if (strcmp (pointer, "MUL") == 0) {
                    counter++;
                    fprintf (output, "%d", 5);
                    pointer += strlen ("MUL");
                }
                else if (strcmp (pointer, "DIV") == 0) {
                    counter++;
                    fprintf (output, "%d", 6);
                    pointer += strlen ("DIV");
                }
                else if (strcmp (pointer, "SQRT") == 0) {
                    counter++;
                    fprintf (output, "%d", 7);
                    pointer += strlen ("SQRT");
                }
                else if (strcmp (pointer, "HLT") == 0) {
                    counter++;
                    fprintf (output, "%d", 0);
                    fprintf (output, "|%lu", counter);
                    break;
                }
                else if(*pointer == '\0') {
                    pointer++;
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



