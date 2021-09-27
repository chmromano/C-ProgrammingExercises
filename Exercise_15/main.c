#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint16_t crc16(const uint8_t *data_p, unsigned int length);

bool validate_filename(char string[]);

uint16_t validate_size();

bool validate_character();

struct chunk {
    uint8_t *data;
    uint16_t size;
    uint16_t capacity;
    uint16_t crc;
};

int main() {

    do {

        int allocated = 0;

        struct chunk *chunks = NULL;

        chunks = (struct chunk *) malloc(sizeof(struct chunk));

        char *file_name = NULL;
        file_name = (char *) malloc(sizeof(char));

        if (file_name == NULL) {
            printf("Error allocating memory. Ending program.");
            exit(1);
        }

        printf("Enter file name: ");
        while (validate_filename(file_name) == false);

        FILE *my_file;
        my_file = fopen(file_name, "rb");

        if (my_file == NULL) {
            printf("Error opening the file. ");
        } else {

            uint16_t max_chunk_size = validate_size();
            uint8_t buffer[max_chunk_size];

            size_t cur_chunk_size;

            for (int i = 0; (cur_chunk_size = fread(buffer, 1, max_chunk_size, my_file)) != 0; i++) {

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
                (chunks + i)->capacity = max_chunk_size;
                (chunks + i)->crc = crc16((chunks + i)->data, (chunks + i)->size);
            }


            if (allocated == 1) {
                printf("\nAllocated %d chunk.\n\n", allocated);
            } else {
                printf("\nAllocated %d chunks.\n\n", allocated);
            }

            for (int i = 0; i < allocated; i++) {
                printf("Chunk %d:\n", i + 1);
                if ((chunks + i)->size == 1) {
                    printf("\tSize:     %hu byte\n", (chunks + i)->size);
                } else {
                    printf("\tSize:     %hu bytes\n", (chunks + i)->size);
                }
                if ((chunks + i)->capacity == 1) {
                    printf("\tCapacity: %hu byte\n", (chunks + i)->capacity);
                } else {
                    printf("\tCapacity: %hu bytes\n", (chunks + i)->capacity);
                }
                printf("\tCRC:      %04X\n", (chunks + i)->crc);
                free((chunks + i)->data);
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
        printf("Enter valid file name: ");
        success = false;
    }

    return success;
}

uint16_t validate_size() {
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

    return(uint16_t) input;
}

bool validate_character() {
    int ch;
    char character = 0;

    bool run_again = true;

    printf("Do you want to read another file (y/n)? ");

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