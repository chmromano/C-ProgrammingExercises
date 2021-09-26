#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 64

bool read_file_name(char string[]);

struct chunk {
    uint8_t data[CHUNK_SIZE];
    uint16_t size;
    uint16_t crc;
};

int main() {

    FILE *my_file;

    struct chunk *chunks = NULL;

    char *file_name = NULL;
    file_name = (char *) malloc(sizeof(char));

    if (file_name == NULL) {
        printf("Error allocating memory. Ending program.");
        exit(1);
    }

    file_name[0] = '\0';

    printf("Enter file name:\n");
    while (read_file_name(file_name) == false);

    printf("%s:%d\n", file_name, (int) strlen(file_name));

    my_file = fopen(file_name, "rb");

    if (my_file == NULL) {
        printf("Error opening the file.");
    } else {
        fseek(my_file, 0, SEEK_END);
        long file_size = ftell(my_file);
        rewind(my_file);

        int allocate = ((int) file_size / CHUNK_SIZE) + 1;

        chunks = (struct chunk *) malloc(sizeof(struct chunk) * allocate);

        if (chunks == NULL) {
            printf("Error allocating memory. Ending program.");
            exit(1);
        }

        for (int i = 0; i < allocate; i++) {
            fread((chunks + i)->data, 1, CHUNK_SIZE, my_file);
        }

        for (int i = 0; i < allocate; i++) {
            for(int j = 0; j < CHUNK_SIZE; j++) {
                printf("%hhu", (chunks + i)->data[j]);
            }
            printf("\n");
        }

        printf("%d", allocate);
    }

    free(file_name);
    free(chunks);
    fclose(my_file);
    return 0;
}

bool read_file_name(char string[]) {

    bool success = true;

    int allocated = 0;

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
    }

    return success;
}