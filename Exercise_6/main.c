#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STRING_SIZE 101

void encrypt(char string[], int shift);

int main() {
    bool valid_input = false;
    int ch;

    int shift = 0;
    char my_string[STRING_SIZE];

    printf("Enter the phrase you want to encrypt (maximum 100 characters):\n");

    fgets(my_string, STRING_SIZE, stdin);
    if (my_string[strlen(my_string) - 1] == '\n') {
        my_string[strlen(my_string) - 1] = '\0';
    }

    printf("Enter the amount of shift:\n");

    while (valid_input == false) {
        if (scanf("%d", &shift) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Incorrect characters. Please enter a valid number:\n");
        } else {
            valid_input = true;
        }
    }

    for (int i = 0; i < strlen(my_string); i++) {
        my_string[i] = toupper(my_string[i]);
    }

    printf("Original string:\n%s\n", my_string);

    encrypt(my_string, shift);

    printf("Encrypted string:\n%s\n", my_string);

    encrypt(my_string, -shift);

    printf("Decrypted string:\n%s", my_string);

    return 0;
}

void encrypt(char string[], int shift) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] != (char) 32) {
            string[i] += shift;

            if ((int) string[i] > 90) {
                string[i] -= 26;
            } else if ((int) string[i] < 65) {
                string[i] += 26;
            }
        }
    }
}