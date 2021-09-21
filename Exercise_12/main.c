#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 52
#define ARRAY_SIZE 30
#define STRING_DOUBLES "1234567890."

struct item {
    char name[STRING_LENGTH];
    double price;

};

bool read_item(char string[], double *number, FILE *file);

bool read_double(double *input, char string[]);

void validate_string(char string[]);

int main() {
    int item_count = 0;
    struct item items[ARRAY_SIZE] = {};
    char item_name[STRING_LENGTH] = {};
    double item_price = 0;
    int longest_string = 0;
    int longest_price = 0;

    FILE *my_file;
    char file_name[STRING_LENGTH] = {};

    printf("Enter the name of the file you want to open: ");
    validate_string(file_name);

    my_file = fopen(file_name, "r");

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        while (!feof(my_file)) {
            if (read_item(item_name, &item_price, my_file) == true) {
                strcpy(items[item_count].name, item_name);
                if (strlen(items[item_count].name) > longest_string) {
                    longest_string = (int) strlen(items[item_count].name);
                }

                items[item_count].price = item_price;
                int digits = 0;
                while (item_price >= 1) {
                    item_price = item_price / 10;
                    digits++;
                }
                digits += 3;
                if (digits > longest_price) {
                    longest_price = digits;
                }

                item_count++;
            }
        }

        if (item_count == 0) {
            printf("\nNo items found.\n");
        } else {
            printf("\nFound %d items.\n\n", item_count);
            printf("%-*s\t%*s\n", longest_string, "Name", longest_price, "Price");
            for (int i = 0; i < item_count; i++) {
                printf("%-*s\t%*.2f\n", longest_string, items[i].name, longest_price, items[i].price);
            }
        }
    }

    return 0;
}

bool read_item(char string[], double *number, FILE *file) {

    bool read_success = true;

    int index = 0;

    char temp_string[STRING_LENGTH] = {};
    char double_string[STRING_LENGTH] = {};

    if (fgets(temp_string, STRING_LENGTH, file) == NULL) {
        read_success = false;
    } else {
        if (temp_string[strlen(temp_string) - 1] == '\n') {
            temp_string[strlen(temp_string) - 1] = '\0';
        }
    }

    if (strchr(temp_string, ';') == NULL) {
        read_success = false;
    } else {
        for (int i = 0; i < strlen(temp_string); i++) {
            if (temp_string[i] == ';') {
                index = i;
                break;
            } else {
                double_string[i] = temp_string[i];
                double_string[i + 1] = '\0';
            }
        }

        for (int i = 0; i < strlen(temp_string) - index; i++) {
            string[i] = temp_string[index + i + 1];
            string[i + 1] = '\0';
        }
    }

    if(read_double(number, double_string) == false) {
        read_success = false;
    }

    return read_success;
}

bool read_double(double *number, char string[]) {

    bool read_success = true;

    bool first_dot = false;

    for (int i = 0; i < strlen(string); i++) {
        if (strchr(STRING_DOUBLES, string[i]) == NULL) {
            read_success = false;
            break;
        }

        if (string[i] == '.') {
            if (first_dot == false) {
                first_dot = true;
            } else {
                read_success = false;
                break;
            }
        }
    }

    *number = atof(string);

    return read_success;
}

void validate_string(char string[]) {
    bool valid_input = false;
    int ch;

    while (valid_input == false) {
        fgets(string, STRING_LENGTH, stdin);
        if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
            valid_input = true;
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("File name too long. Enter a file name (maximum 50 characters):\n");
        }
    }
}