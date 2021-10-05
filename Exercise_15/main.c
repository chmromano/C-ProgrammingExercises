#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint16_t crc16(const uint8_t *data_p, unsigned int length);

bool validate_filename(char string[]);

bool validate_character();

int validate_size();

struct chunk {
    uint8_t *data;
    uint16_t size;
    uint16_t capacity;
    uint16_t crc;
};

int main() {
    do {
        //Create pointer to array and variable to keep track of the amount of allocated memory.
        struct chunk *chunks = NULL;
        int allocated = 0;

        //Getting the name of the file.
        char *file_name = NULL;
        file_name = (char *) malloc(sizeof(char));
        if (file_name == NULL) {
            printf("Error allocating memory. Ending program.");
            exit(1);
        }
        file_name[0] = '\0';
        printf("Enter file name: ");
        while (validate_filename(file_name) == false);

        FILE *my_file;
        my_file = fopen(file_name, "rb");

        //Get chunk size and create buffer of that size to temporarily store input from file.
        int max_chunk_size = validate_size();
        uint8_t buffer[max_chunk_size];

        if (my_file == NULL) {
            printf("Error opening the file. ");
        } else {
            size_t cur_chunk_size;
            for (int i = 0; (cur_chunk_size = fread(buffer, (size_t) 1, (size_t) max_chunk_size, my_file)) != 0; i++) {

                allocated++;

                chunks = (struct chunk *) realloc(chunks, sizeof(struct chunk) * allocated);
                if (chunks == NULL) {
                    printf("Error allocating memory. Ending program.");
                    exit(1);
                }

                (chunks + i)->data = (uint8_t *) malloc(sizeof(uint8_t) * cur_chunk_size);
                if ((chunks + i)->data == NULL) {
                    printf("Error allocating memory. Ending program.");
                    exit(1);
                }

                for (int j = 0; j < max_chunk_size; j++) {
                    (chunks + i)->data[j] = buffer[j];
                    buffer[j] = '\0';
                }

                (chunks + i)->size = (uint16_t) cur_chunk_size;
                (chunks + i)->capacity = (uint16_t) max_chunk_size;
                (chunks + i)->crc = crc16((chunks + i)->data, (unsigned int) (chunks + i)->size);
            }

            printf("\n");

            for (int i = 0; i < allocated; i++) {
                printf("Chunk %d:\n", i + 1);
                if ((int) (chunks + i)->size == 1) {
                    printf("\tSize:     %hu byte\n", (chunks + i)->size);
                } else {
                    printf("\tSize:     %hu bytes\n", (chunks + i)->size);
                }
                if ((int) (chunks + i)->capacity == 1) {
                    printf("\tCapacity: %hu byte\n", (chunks + i)->capacity);
                } else {
                    printf("\tCapacity: %hu bytes\n", (chunks + i)->capacity);
                }
                printf("\tCRC:      0x%04X\n", (chunks + i)->crc);
                free((chunks + i)->data);
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
    } while (validate_character());

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

bool validate_filename(char string[]) {
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

bool validate_character() {
    int ch;
    char character = 0;

    bool run_again = true;

    printf("\nDo you want to read another file (y/n)? ");

    bool valid_input = false;
    while (valid_input == false) {
        if (scanf("%c", &character) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Invalid input. Try again (y/n): ");
        } else if (toupper(character) == 'Y') {
            valid_input = true;
        } else if (toupper(character) == 'N') {
            run_again = false;
            valid_input = true;
        } else {
            printf("Invalid character. Try again (y/n): ");
        }
    }

    return run_again;
}

int validate_size() {
    int ch;
    int input = 0;
    bool valid_input = false;

    printf("Enter chunk size: ");

    while (valid_input == false) {
        if (scanf("%d", &input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Invalid characters. Enter chunk size: ");
        } else if (input <= 0) {
            printf("Invalid chunk size. Enter chunk size: ");
        } else {
            valid_input = true;
        }
    }

    return input;
}