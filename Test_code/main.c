#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define STRING_SIZE 20

void merge_whitespace(char *string);

int main() {
    char string1[] = "   This  time with   \t\tleading spaces. \tOne\n"
                     "\n"
                     " more for the road ";
    char string2[] = "    we live  in     Helsinki";
    char string3[] = "i      go back to Switzerland    \n\nin   October";

    merge_whitespace(string1);
    merge_whitespace(string2);
    merge_whitespace(string3);

    printf("%s\n%s\n%s", string1, string2, string3);

    return 0;
}

void merge_whitespace(char *string) {
    int i = 0;
    int length = strlen(string);

    bool first_space_found = false;

    while (i < length) {
        if ((string[i] == 9 || string[i] == 10 || string[i] == 11 || string[i] == 12 || string[i] == 13 || string[i] == 32)
            && first_space_found == false) {
            first_space_found = true;
            i++;
        } else if ((string[i] == 9 || string[i] == 10 || string[i] == 11 || string[i] == 12 || string[i] == 13 || string[i] == 32)
                   && first_space_found == true) {
            for (int j = i; j < length; j++) {
                string[j] = string[j + 1];
            }
        } else if ((string[i] != 9 || string[i] != 10 || string[i] != 11 || string[i] != 12 || string[i] != 13 || string[i] != 32)) {
            first_space_found = false;
            i++;
        }
    }
}