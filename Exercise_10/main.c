#include <stdio.h>
#include <stdbool.h>

#define STRING_LENGTH 102

bool read_int(int *input, FILE *file);

bool read_float(float *input, FILE *file);

int main() {
    bool successful_execution = true;
    int n_expected = 0;
    int n_actual = 0;
    float sum = 0;
    float temp_float = 0;

    FILE *my_file;
    my_file = fopen("numbers.txt", "r");

    if (my_file == NULL) {
        printf("\nThere was an error opening the file.\n");
    } else {
        if (read_int(&n_expected, my_file) == true) {

            for (int i = 0; i < n_expected; i++) {
                if (read_float(&temp_float, my_file) == true) {
                    sum += temp_float;
                    n_actual++;
                } else {
                    successful_execution = false;
                    break;
                }
            }

            if (successful_execution == false) {
                if (n_actual == 1) {
                    printf("Error! Tried to read %d numbers, %d number was read.\n", n_expected, n_actual);
                } else if (n_expected == 1) {
                    printf("Error! Tried to read %d number, %d numbers were read.\n", n_expected, n_actual);
                } else {
                    printf("Error! Tried to read %d numbers, %d numbers were read.\n", n_expected, n_actual);
                }
            }

            if (n_actual == 1) {
                printf("Average of %d number is: %.2f", n_actual, sum / (float) n_actual);
            } else {
                printf("Average of %d numbers is: %.2f", n_actual, sum / (float) n_actual);
            }

        } else {
            printf("Error! No numbers could be read!");
        }
    }

    fclose(my_file);
    return 0;
}


bool read_int(int *input, FILE *file) {

    bool read_success = true;

    char temp_string[STRING_LENGTH] = {};

    if (fgets(temp_string, STRING_LENGTH, file) == NULL) {
        read_success = false;
    }

    if (sscanf(temp_string, "%d", input) != 1) {
        read_success = false;
    }

    return read_success;
}

bool read_float(float *input, FILE *file) {

    bool read_success = true;

    char temp_string[STRING_LENGTH] = {};

    if (fgets(temp_string, STRING_LENGTH, file) == NULL) {
        read_success = false;
    }

    if (sscanf(temp_string, "%f", input) != 1) {
        read_success = false;
    }

    return read_success;
}