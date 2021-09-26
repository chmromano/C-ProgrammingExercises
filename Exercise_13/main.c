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
        printf("Enter a string ('.' to stop):\n");

        while (run_program == true) {

            bool read_string = true;

            char *string = NULL;
            int allocated = 0;
            string = (char *) malloc(sizeof(char));

            if (string == NULL) {
                printf("Error allocating memory. Ending program.");
                exit(1);
            }

            string[0] = '\0';

            while (read_string == true) {

                int character;
                character = getchar();

                if (character == '\n' || character == '\r') {
                    read_string = false;
                } else {
                    allocated++;
                    string = (char *) realloc(string, (allocated + 1) * sizeof(char));

                    if (string == NULL) {
                        printf("Error reallocating memory. Ending program.");
                        exit(1);
                    }

                    string[allocated - 1] = (char) character;
                    string[allocated] = '\0';
                }
            }

            if (strlen(string) == 1 && string[0] == '.') {
                run_program = false;
            } else if (strlen(string) == 0) {
                printf("Error: empty string. Enter a string ('.' to stop):\n");
            } else {
                fprintf(my_file, "%d:%s\n", (int) strlen(string), string);
                printf("Enter another string ('.' to stop):\n");
            }

            free(string);
        }
    }

    fclose(my_file);
    return 0;
}
