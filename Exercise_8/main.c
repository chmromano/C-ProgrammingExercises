#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define STRING_SIZE 102

void string_validation(char string[]);

void convert_upper_string(char string[]);

int main() {
    bool loop = true;

    char my_string[STRING_SIZE] = {};

    while (loop == true) {
        printf("Enter a string (maximum 100 characters):\n");

        string_validation(my_string);

        if ((strncmp(my_string, "STOP", 4)) == 0 || (strncmp(my_string, "stop", 4)) == 0) {
            loop = false;
        } else {
            convert_upper_string(my_string);
            printf("%s\n", my_string);
        }
    }

    printf("Program stopped.");

    return 0;
}

void string_validation(char string[]) {
    bool valid_input = false;
    int ch;

    while (valid_input == false) {
        fgets(string, STRING_SIZE, stdin);
        if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
            valid_input = true;
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("String too long. Enter a string (maximum 100 characters):\n");
        }
    }
}

void convert_upper_string(char string[]) {

    bool is_first_cap = false;

    for (int i = 0; i < strlen(string); i++) {
        if (is_first_cap == false && isalpha(string[i]) == true) {
            string[i] = toupper(string[i]);
            is_first_cap = true;
        } else if (is_first_cap == true && isblank(string[i]) == true) {
            is_first_cap = false;
        }
    }
}