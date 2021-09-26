#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "test_file"

int main() {

    bool run_program = true;

    long size;

    size_t result;

    char *buffer;

    int char_count = 0;

    int character;

    FILE *my_file;
    my_file = fopen(FILE_NAME, "rb");

    // obtain file size:
    fseek(my_file, 0, SEEK_END);
    size = ftell(my_file);
    rewind(my_file);

    // allocate memory to contain the whole file:
    buffer = (char *) malloc(sizeof(char) * size);
    if (buffer == NULL) {
        exit(1);
    }

    // copy the file into the buffer:
    result = fread(buffer, 1, size, my_file);
    if (result != size) {
        fputs("Reading error", stderr);
        exit(3);
    }

    printf("%ld", size);

    // terminate
    fclose(my_file);
    free(buffer);
    return 0;
}
