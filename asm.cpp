#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>


char* ReadBuffer (FILE* text);

int main (int argc, char* argv[]) {
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
                    fprintf (output, "%d", 1);
                    pointer += strlen ("PUSH");
                    while(!isalpha(*pointer)) {
                        if (*pointer != '\0') {
                            fprintf (output, "%c", *pointer );
                        }
                        pointer++;
                    }
                } 
                else if (strcmp (pointer, "POP") == 0) {
                    fprintf (output, "%d", 2);
                    pointer += strlen ("POP");
                }
                else if (strcmp (pointer, "ADD") == 0) {
                    fprintf (output, "%d", 3);
                    pointer += strlen ("ADD");
                }
                else if (strcmp (pointer, "SUB") == 0) {
                    fprintf (output, "%d", 4);
                    pointer += strlen ("SUB");
                }
                else if (strcmp (pointer, "MUL") == 0) {
                    fprintf (output, "%d", 5);
                    pointer += strlen ("MUL");
                }
                else if (strcmp (pointer, "DIV") == 0) {
                    fprintf (output, "%d", 6);
                    pointer += strlen ("DIV");
                }
                else if (strcmp (pointer, "SQRT") == 0) {
                    fprintf (output, "%d", 7);
                    pointer += strlen ("SQRT");
                }
                else if (strcmp (pointer, "HLT") == 0) {
                    fprintf (output, "%d", 0);
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


char* ReadBuffer(FILE* text) {

    assert (text);

    struct stat statistic = {};

    char* buffer = NULL;
    int descriptor = fileno(text); 
    fstat (descriptor, &statistic);    

    size_t size = statistic.st_size;

    buffer = (char*) calloc(sizeof (char), size + 1);
    buffer[size] = '\0';
    fread (buffer, sizeof(char), size, text);
    
    return buffer;   
}

