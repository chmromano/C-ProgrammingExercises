#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* One problem with the program is that if a line in the file is longer than 51 characters, the next line the program
 * reads will be the rest on the SAME line. It doesn't cause problems. What happens is the string after the 51st
 * character is read, and goes through the item validation process. If it's just extra characters from the previous
 * string they will be discarded, but if it is a properly formatted item it will be read and added to the array. */
#define STRING_LENGTH 52
#define ARRAY_SIZE 30
#define STRING_DOUBLES "1234567890."
#define EXTRA_DIGITS 3

struct item {
    char name[STRING_LENGTH];
    double price;

};

bool read_item(char string[], double *number, FILE *file);

bool read_double(double *input, char string[]);

void validate_string(char string[]);

int main() {

    struct item items[ARRAY_SIZE] = {};

    int item_count = 0;
    int discarded_items = 0;

    char item_name[STRING_LENGTH] = {};
    double item_price = 0;

    int longest_name = 0;
    int longest_price = 0;

    char file_name[STRING_LENGTH] = {};

    printf("Enter the name of the file you want to open: ");
    validate_string(file_name);

    FILE *my_file;
    my_file = fopen(file_name, "r");

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        while (!feof(my_file)) {
            if (read_item(item_name, &item_price, my_file) == true) {
                strcpy(items[item_count].name, item_name);

                //Keep track of the longest string.
                if (strlen(items[item_count].name) > longest_name) {
                    longest_name = (int) strlen(items[item_count].name);
                }

                items[item_count].price = item_price;

                //Keep track of the "longest" price. digits variable accounts for 3 extra characters ".00".
                int digits = EXTRA_DIGITS;
                while (item_price >= 1) {
                    item_price = item_price / 10;
                    digits++;
                }
                if (digits > longest_price) {
                    longest_price = digits;
                }

                item_count++;

                if (item_count == ARRAY_SIZE) {
                    printf("\nArray limit reached. Reading stopped.\n");
                    break;
                }
            } else {
                //Keep track of any items not read due to errors in formatting.
                discarded_items++;
            }
        }

        if (item_count == 0) {
            printf("\nNo items found.\n");
        } else {
            if (item_count == 1) {
                printf("\nFound %d item. ", item_count);
            } else {
                printf("\nFound %d items. ", item_count);
            }

            if (discarded_items == 1) {
                printf("Discarded %d item.\n\n", discarded_items);
            } else {
                printf("Discarded %d items.\n\n", discarded_items);
            }

            printf("%-*s    %*s\n", longest_name, "Name", longest_price, "Price");
            for (int i = 0; i < item_count; i++) {
                printf("%-*s    %*.*f\n", longest_name, items[i].name, longest_price, (EXTRA_DIGITS - 1), items[i].price);
            }
        }
    }

    return 0;
}

//Reads item. Returns true or false depending on read success.
bool read_item(char string[], double *number, FILE *file) {

    bool read_success = true;

    int item_name_index_start = 0;

    char temp_string[STRING_LENGTH] = {};
    char double_string[STRING_LENGTH] = {};

    if (fgets(temp_string, STRING_LENGTH, file) == NULL) {
        read_success = false;
    } else if (temp_string[strlen(temp_string) - 1] == '\n') {
        temp_string[strlen(temp_string) - 1] = '\0';
    }

    //Parsing temp_string until delimiter ';'. Saving before and after ';' in two separate strings.
    if (strchr(temp_string, ';') == NULL) {
        read_success = false;
    } else {
        for (int i = 0; i < strlen(temp_string); i++) {
            if (temp_string[i] == ';') {
                item_name_index_start = i + 1;
                break;
            } else {
                double_string[i] = temp_string[i];
                double_string[i + 1] = '\0';
            }
        }

        for (int i = 0; i < strlen(temp_string) - item_name_index_start; i++) {
            string[i] = temp_string[item_name_index_start + i];
            string[i + 1] = '\0';
        }
    }

    if (read_double(number, double_string) == false) {
        read_success = false;
    }

    return read_success;
}

//Validate double. Return true or false depending on validation success.
bool read_double(double *number, char string[]) {

    bool read_success = true;

    bool first_dot = false;

    for (int i = 0; i < strlen(string); i++) {
        //Check for forbidden characters.
        if (strchr(STRING_DOUBLES, string[i]) == NULL) {
            read_success = false;
            break;
        }

        //Keep track of multiple dots in the string. Only 1 dot allowed.
        if (string[i] == '.') {
            if (first_dot == false) {
                first_dot = true;
            } else {
                read_success = false;
                break;
            }
        }
    }

    //Use atof() to convert string to double after validation.
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