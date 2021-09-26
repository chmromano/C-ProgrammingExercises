#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "strings.txt"

int main() {

    bool run_program = true;

    FILE *my_file;
    my_file = fopen(FILE_NAME, "w");

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        while (run_program == true) {

            bool read_string = true;

            char string[] = {};
            int string_length = 0;

            while (read_string == true) {
                int character;
                character = getchar();

                if (character == '\n') {
                    read_string = false;
                } else {
                    string_length++;
                }
            }

            if (strlen(string) == 1 && string[0] == '.') {
                run_program = false;
            } else {
                fprintf(my_file, "%d:%s", string_length, string);
            }
        }
    }

    fclose(my_file);
    return 0;
}
