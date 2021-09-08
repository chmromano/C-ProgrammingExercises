#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STRING_SIZE 102

void encrypt(char string[], int shift);

int main() {
    bool valid_input = false;
    int ch;

    int shift = 0;
    char my_string[STRING_SIZE] = {};

    printf("Enter the phrase you want to encrypt (maximum 100 characters):\n");

    /*Should work to validate string until max length. To make it work actual array size is 1 more than would actually
    be required to store mac string (101 for 100 characters + null, but 102 array size in my case for validation).*/
    while (valid_input == false) {
        fgets(my_string, STRING_SIZE, stdin);
        if (my_string[strlen(my_string) - 1] == '\n') {
            my_string[strlen(my_string) - 1] = '\0';
            valid_input = true;
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("String too long. Enter a string (maximum 100 characters):\n");
        }
    }

    printf("Enter the amount of shift:\n");

    valid_input = false;

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

    encrypt(my_string, (-1) * shift);

    printf("Decrypted string:\n%s", my_string);

    return 0;
}

void encrypt(char string[], int shift) {
    for (int i = 0; i < strlen(string); i++) {
        //Using temporary variable, otherwise character's ASCII int value can go above 126, causing problems
        int temp = (int) string[i];

        if (temp != 32) {
            /*My function assumes that the shift will be to the right.
            To make it a left shift simply change the line below to perform
            a subtraction, or input a negative shift value.*/
            temp += shift;

            while ((int) temp > 90 || (int) temp < 65) {
                if ((int) temp > 90) {
                    temp -= 26;
                } else if ((int) temp < 65) {
                    temp += 26;
                }
            }

            string[i] = temp;
        }
    }
}