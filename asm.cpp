#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

char* ReadBuffer (FILE* text);


int main (int argc, char* argv[]) {
    FILE* source = fopen (argv[1], "r" );
    FILE* output = fopen (argv[2], "w");

    assert(source);
    assert(output);

    char* buffer = ReadBuffer (source);

    size_t in = 0;

    fprintf(stderr, "buffer: %s\n", buffer);
    fprintf(stderr, "size: %lu\n", strlen(buffer));

    while (buffer[in] != '\0') { 
        if (buffer[in] == '\n' || buffer[in] == ' ') { 
            buffer[in] = '\0';
        }
        in++;
    }
    fprintf(stderr, "buffer: %s\n", (char*)((size_t)buffer + 9));
    in = 0;

    char* pointer = buffer;
    fprintf(stderr, "pointer before: %p\n", pointer);
    fprintf(stderr, "size: %lu\n", strlen(buffer));
    while (1) {
        if (strcmp (pointer, "PUSH") == 0) {
            fprintf (output, "%d ", 1);
            pointer = (char*) (size_t (pointer) + strlen ("PUSH"));
            while(!isalpha(*pointer)) {
                if (*pointer != '\0') {
                    fprintf (output, "%c", *pointer );
                }
                pointer++;
                fprintf(stderr, "%p\n", pointer);
            }
            fprintf(stderr, "pointer:%s\n", pointer);
        } 
        else if (strcmp (pointer, "POP") == 0) {
            fprintf (output, "%d ", 2);
            pointer = (char*) (size_t (pointer) + strlen ("POP") + 1);
        }
        else if (strcmp (pointer, "ADD") == 0) {
            fprintf (output, "%d\n", 3);
            pointer = (char*) (size_t (pointer) + strlen ("ADD"));
        }
        else if (strcmp (pointer, "SUB") == 0) {
            fprintf (output, "%d\n", 4);
            pointer = (char*) (size_t (pointer) + strlen ("SUB"));
        }
        else if (strcmp (pointer, "MUL") == 0) {
            fprintf (output, "%d\n", 5);
            pointer = (char*) (size_t (pointer) + strlen ("MUL"));
        }
        else if (strcmp (pointer, "DIV") == 0) {
            fprintf (output, "%d\n", 6);
            pointer = (char*) (size_t (pointer) + strlen ("DIV"));
        }
        else if (strcmp (pointer, "SQRT") == 0) {
            fprintf (output, "%d\n", 7);
            pointer = (char*) (size_t (pointer) + strlen ("SQRT"));
        }
        else if (strcmp (pointer, "HLT") == 0) {
            fprintf (output, "%d\n", 0);
            break;
        }
        else {
            fprintf (stderr, "syntax error\n");
            pointer++;
        }
    }
    free(buffer);
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

