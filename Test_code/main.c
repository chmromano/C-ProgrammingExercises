#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FILE_NAME "test_file"

int main() {

    bool run_program = true;

    int char_count = 0;

    int character;

    FILE *my_file;
    my_file = fopen(FILE_NAME, "w");

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        while (run_program == true) {

            character = getchar();

            if (character != '.' && character != '\n') {
                char_count++;
                fprintf(my_file, "%d:%c\n", char_count, character);
            } else if (character == '.') {
                run_program = false;
            }
        }
    }

    fclose(my_file);
    return 0;
}
