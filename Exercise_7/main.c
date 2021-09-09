#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define STRING_SIZE 102

void string_validation(char string[]);

void convert_underscore_string(char string[]);

int main() {
    bool loop = true;

    char my_string[STRING_SIZE] = {};

    while (loop == true) {
        printf("Enter a string (maximum 100 characters):\n");

        string_validation(my_string);

        if ((strncmp(my_string, "STOP", 4)) == 0 || (strncmp(my_string, "stop", 4)) == 0) {
            loop = false;
        } else {
            convert_underscore_string(my_string);
            printf("%s\n", my_string);
        }
    }

    printf("Program stopped.");
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

void convert_underscore_string(char string[]) {
    bool capitalised_first = false;

    for (int i = 1; i <= strlen(string); i++) {
        if (string[i - 1] == 32 && string[i] != 32) {
            string[i] = toupper(string[i]);
        }
    }
}