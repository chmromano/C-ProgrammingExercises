#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_LENGTH 52
#define ARRAY_SIZE 30

struct item {
    char name[STRING_LENGTH];
    float price;

};

int read_item(struct item array[]);

void validate_string(char string[]);

int main() {
    int item_count = 0;
    struct item items[ARRAY_SIZE] = {};

    FILE *my_file;
    char file_name[STRING_LENGTH] = {};

    printf("Enter the name of the file you want to open: ");
    validate_string(file_name);

    my_file = fopen(file_name, "r");

    return 0;
}

int read_item(struct item array[]) {

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