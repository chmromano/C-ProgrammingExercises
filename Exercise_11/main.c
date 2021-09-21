#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//To sort more than 3 numbers just change this
#define TO_READ 3
#define STRING_LENGTH 102

#define STRING_INTEGERS "-1234567890"

bool read_int(int *input, FILE *file);

int main() {
    bool successful_execution = true;

    int unsorted_array[TO_READ] = {};
    int sorted_array[TO_READ] = {};

    int unsorted_array_size = TO_READ;

    int smallest = 0;
    int smallest_index = 0;

    FILE *my_file;
    my_file = fopen("numbers.txt", "r");

    if (my_file == NULL) {
        printf("\nThere was an error opening the file.\n");
    } else {
        for (int i = 0; i < TO_READ; i++) {
            if (read_int(&unsorted_array[i], my_file) == false) {
                printf("\nThere was an error while reading the numbers.\n");
                successful_execution = false;
                break;
            }
        }

        if (successful_execution == true) {
            for (int i = 0; i < TO_READ; i++) {

                smallest = unsorted_array[0];
                smallest_index = 0;

                for (int j = 0; j < unsorted_array_size; j++) {
                    if (unsorted_array[j] < smallest) {
                        smallest = unsorted_array[j];
                        smallest_index = j;
                    }
                }

                unsorted_array_size--;
                sorted_array[i] = smallest;

                for (int k = smallest_index; k <= unsorted_array_size; k++) {
                    if (smallest_index != unsorted_array_size) {
                        unsorted_array[k] = unsorted_array[k + 1];
                    }
                }
            }

            my_file = fopen("numbers.txt", "w");

            for (int i = 0; i < TO_READ; i++) {
                fprintf(my_file, "%d\n", sorted_array[i]);
            }
        }
    }

    return 0;
}

bool read_int(int *input, FILE *file) {

    bool read_success = true;

    char temp_string[STRING_LENGTH] = {};

    if (fgets(temp_string, STRING_LENGTH, file) == NULL) {
        read_success = false;
    } else {
        if (temp_string[strlen(temp_string) - 1] == '\n') {
            temp_string[strlen(temp_string) - 1] = '\0';
        }
    }

    for (int i = 0; i < strlen(temp_string); i++) {
        if (strchr(STRING_INTEGERS, temp_string[i]) == NULL) {
            read_success = false;
            break;
        }

        if (temp_string[i] == '-' && i != 0) {
            read_success = false;
            break;
        }
    }

    *input = atoi(temp_string);

    return read_success;
}