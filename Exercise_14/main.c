#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool read_file_name(char string[]);

typedef struct chunk {
    uint8_t data[64];
    uint16_t size;
    uint16_t crc;
} CHUNK;

int main() {

    FILE *my_file;

    CHUNK *chunks = NULL;

    char *file_name = NULL;
    file_name = (char *) malloc(sizeof(char));

    if (file_name == NULL) {
        printf("Error allocating memory. Ending program.");
        exit(1);
    }

    printf("Enter file name:\n");
    while (read_file_name(file_name) == false);
    printf("%s", file_name);

    printf("%s:%d", file_name, (int) strlen(file_name));

    my_file = fopen(file_name, "rb");

    if (my_file == NULL) {
        printf("Error opening the file.");
    } else {
        fseek(my_file, 0, SEEK_END);
        long file_size = ftell(my_file);
        rewind(my_file);

        printf("%ld", file_size / 64);

        for (long i = file_size; i > 64; i - 64) {

        }
    }

    free(file_name);
    fclose(my_file);
    return 0;
}

bool read_file_name(char string[]) {

    bool success = true;

    int allocated = 0;

    string[0] = '\0';

    bool read_string = true;

    while (read_string == true) {

        int character;
        character = getchar();

        if (character == '\n' || character == '\r') {
            read_string = false;
        } else {
            allocated++;
            string = (char *) realloc(string, (allocated + 1) * sizeof(char));

            if (string == NULL) {
                printf("Error reallocating memory. Ending program.");
                exit(1);
            }

            string[allocated - 1] = (char) character;
            string[allocated] = '\0';
        }
    }

    if (strlen(string) == 0) {
        printf("Enter valid file name:\n");
        success = false;
        free(string);
    }

    return success;
}