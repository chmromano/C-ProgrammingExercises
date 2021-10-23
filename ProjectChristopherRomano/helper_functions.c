#include "main.h"
#include "strings.h"

//Used in strchr().
#define YES_OR_NO "YN"

//Function to verify memory allocation success.
void mem_check(void *memory) {
    if (memory == NULL) {
        MEM_ERROR_MSG;
        exit(1);
    }
}

//Function to validate a 'Y', 'y', 'N', or 'n' character.
bool input_y_n(char *character) {
    bool success = true;
    int ch;
    if (scanf("%c", character) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        success = false;
    } else if (strchr(YES_OR_NO, (char) toupper(*character)) == NULL) {
        success = false;
    } else {
        *character = (char) toupper(*character);
    }
    return success;
}

//Function to validate an integer input.
bool input_integer(int *input) {
    bool success = true;
    int ch;
    if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        success = false;
    }
    return success;
}

//Function to validate a string.
char *input_string() {
    char *string;
    string = NULL;

    bool success = false;
    while (success == false) {
        int allocated = 0;

        string = realloc(string, sizeof(char));
        mem_check(string);
        string[0] = '\0';

        bool read_string = true;
        while (read_string == true) {
            int character = getchar();
            if (character == '\n' || character == '\r' || character == '\f') {
                read_string = false;
            } else {
                allocated++;
                string = realloc(string, (allocated + 1) * sizeof(char));
                mem_check(string);
                string[allocated - 1] = (char) character;
                string[allocated] = '\0';
            }
        }

        if (strlen(string) == 0) {
            EMPTY_STRING_MSG;
        } else {
            success = true;
        }
    }

    return string;
}