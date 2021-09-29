#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "file"

int main(void) {
    //Keep program running
    bool run_program = true;

    FILE *my_file;
    my_file = fopen(FILE_NAME, "w");
    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        printf("Enter a string ('.' to stop):\n");
        while (run_program == true) {
            //Keep reading the string
            bool read_string = true;

            //Keep track of allocated memory
            int allocated = 0;

            char *string = NULL;
            //*A*
            //Must allocate memory and initialise string because of what happens at *B*
            string = (char *) malloc(sizeof(char));
            if (string == NULL) {
                printf("Error reallocating memory. Ending program.");
                exit(1);
            }
            string[0] = '\0';

            while (read_string == true) {
                int character = getchar();

                //If character is newline skip, otherwise reallocate memory, add character and move end of string value.
                if (character == '\n' || character == '\r' || character == '\f') {
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

            //*B*
            //If memory is not allocated to string at *A* this step will cause the program to crash.
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
