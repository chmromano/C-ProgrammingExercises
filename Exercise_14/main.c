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
    file_name[0] = '\0';

    printf("Enter file name: ");
    //Keep prompting user until a valid filename is entered.
    while (read_file_name(file_name) == false);

    FILE *my_file;
    my_file = fopen(file_name, "rb");

    if (my_file == NULL) {
        printf("Error opening the file.");
    } else {
        //Buffer using predefined maximum chunk size.
        uint8_t buffer[CHUNK_SIZE] = {};

        //Storing actual chunk size of chunk.
        uint16_t actual_chunk_size;
        //For-loop runs as long as fread() doesn't return 0, which would mean there is nothing more to read.
        for (int i = 0; (actual_chunk_size = (uint16_t) fread(buffer, 1, CHUNK_SIZE, my_file)) != 0; i++) {

            allocated++;

            //Since a chunk was found, reallocate as much memory as is needed for the array (+1).
            chunks = (struct chunk *) realloc(chunks, sizeof(struct chunk) * allocated);
            if (chunks == NULL) {
                printf("Error allocating memory. Ending program.");
                exit(1);
            }

            //Copy data from the buffer to data of the chunk struct. "Zero" the buffer.
            for (int j = 0; j < (int) actual_chunk_size; j++) {
                (chunks + i)->data[j] = buffer[j];
                buffer[j] = '\0';
            }

            //Copy the actual size and the CRC to the chunk struct.
            (chunks + i)->size = actual_chunk_size;
            (chunks + i)->crc = crc16((chunks + i)->data, (chunks + i)->size);
        }

        printf("\n");

        //Print and format output.
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

    //Free everything and close file.
    free(file_name);
    free(chunks);
    fclose(my_file);
    return 0;
}

//Copied CRC function.
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

//Function to read the file name (basically reused from EX13).
bool read_file_name(char string[]) {
    bool success = true;
    bool read_string = true;
    int allocated = 0;

    while (read_string == true) {
        int character = getchar();

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