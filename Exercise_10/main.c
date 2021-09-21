#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 102

#define STRING_INTEGERS "1234567890"
#define STRING_DOUBLES "-1234567890."

bool read_int(int *input, FILE *file);

bool read_double(double *input, FILE *file);

int main() {
    bool successful_execution = true;
    int n_expected = 0;
    int n_actual = 0;
    double sum = 0;
    double temp_double = 0;

    FILE *my_file;
    my_file = fopen("numbers.txt", "r");

    if (my_file == NULL) {
        printf("\nThere was an error opening the file.\n");
    } else {
        if (read_int(&n_expected, my_file) == true) {

            for (int i = 0; i < n_expected; i++) {
                if (read_double(&temp_double, my_file) == true) {
                    sum += temp_double;
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
                printf("Average of %d number is: %.2f", n_actual, sum / (double) n_actual);
            } else {
                printf("Average of %d numbers is: %.2f", n_actual, sum / (double) n_actual);
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
    }

    *input = atoi(temp_string);

    return read_success;
}

bool read_double(double *input, FILE *file) {

    bool read_success = true;

    bool first_dot = false;

    char temp_string[STRING_LENGTH] = {};

    if (fgets(temp_string, STRING_LENGTH, file) == NULL) {
        read_success = false;
    } else {
        if (temp_string[strlen(temp_string) - 1] == '\n') {
            temp_string[strlen(temp_string) - 1] = '\0';
        }
    }

    for (int i = 0; i < strlen(temp_string); i++) {
        if (strchr(STRING_DOUBLES, temp_string[i]) == NULL) {
            read_success = false;
            break;
        }

        if (temp_string[i] == '.') {
            if (first_dot == false) {
                first_dot = true;
            } else {
                read_success = false;
                break;
            }
        }

        if (temp_string[i] == '-' && i != 0) {
            read_success = false;
            break;
        }
    }

    *input = atof(temp_string);

    return read_success;
}