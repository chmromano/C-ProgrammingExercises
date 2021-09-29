#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 64

uint16_t crc16(const uint8_t *data_p, unsigned int length);

bool read_file_name(char string[]);

struct chunk {
    uint8_t data[CHUNK_SIZE];
    uint16_t size;
    uint16_t crc;
};

int main() {

    int allocated = 0;

    struct chunk *chunks = NULL;

    char *file_name = NULL;
    file_name = (char *) malloc(sizeof(char));
    if (file_name == NULL) {
        printf("Error allocating memory. Ending program.");
        exit(1);
    }

    printf("Enter file name: ");
    while (read_file_name(file_name) == false);

    FILE *my_file;
    my_file = fopen(file_name, "rb");

    if (my_file == NULL) {
        printf("Error opening the file.");
    } else {
        uint8_t buffer[CHUNK_SIZE] = {};

        uint16_t chunk_size;
        for (int i = 0; (chunk_size = (uint16_t) fread(buffer, 1, CHUNK_SIZE, my_file)) != 0; i++) {
            allocated++;

            chunks = (struct chunk *) realloc(chunks, sizeof(struct chunk) * allocated);
            if (chunks == NULL) {
                printf("Error allocating memory. Ending program.");
                exit(1);
            }

            for (int j = 0; j < (int) chunk_size; j++) {
                (chunks + i)->data[j] = buffer[j];
                buffer[j] = '\0';
            }

            (chunks + i)->size = chunk_size;
            (chunks + i)->crc = crc16((chunks + i)->data, (chunks + i)->size);
        }

        printf("\n");

        for (int i = 0; i < allocated; i++) {
            printf("Chunk %d:\n", i + 1);
            if ((chunks + i)->size == 1) {
                printf("\tSize: %hu byte\n", (chunks + i)->size);
            } else {
                printf("\tSize: %hu bytes\n", (chunks + i)->size);
            }
            printf("\tCRC: %04X\n", (chunks + i)->crc);
        }

        if (allocated == 1) {
            printf("\nAllocated %d chunk.\n", allocated);
        } else {
            printf("\nAllocated %d chunks.\n", allocated);
        }
    }

    free(file_name);
    free(chunks);
    fclose(my_file);
    return 0;
}

uint16_t crc16(const uint8_t *data_p, unsigned int length) {
    uint8_t x;
    uint16_t crc = 0xFFFF;
    while (length--) {
        x = crc >> 8 ^ *data_p++;
        x ^= x >> 4;
        crc = (crc << 8) ^ ((uint16_t) (x << 12)) ^ ((uint16_t) (x << 5)) ^ ((uint16_t) x);
    }
    return crc;
}

bool read_file_name(char string[]) {
    bool success = true;
    bool read_string = true;
    int allocated = 0;

    while (read_string == true) {
        int character;
        character = getchar();

        if (character == '\n' || character == '\r' || character == '\f') {
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
        printf("Enter valid file name: ");
        success = false;
    }

    return success;
}