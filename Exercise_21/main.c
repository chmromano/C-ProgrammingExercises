#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define READ_B "rb"
#define N_CHAR_256 256
#define N_CHAR_10 10

char *input_string();

int main() {
    //Get file name and open file.
    printf("Enter file to read from: ");
    char *file_name = NULL;
    file_name = input_string();
    FILE *my_file;
    my_file = fopen(file_name, READ_B);
    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        int occurrences_array[N_CHAR_256] = {};
        //Count the characters in the file.
        uint8_t character;
        while (fread(&character, 1, 1, my_file) != 0) {
            for (int i = 0; i < N_CHAR_256; i++) {
                if ((int) character == i) occurrences_array[i]++;
            }
        }

        //Find and print the most frequent characters.
        printf("10 most frequent characters:\n");
        for (int i = 0; i < N_CHAR_10; i++) {

            //Find the most frequent characters.
            int most_frequent = 0;
            int index = 0;
            for (int j = 0; j < N_CHAR_256; j++) {
                if (occurrences_array[j] > most_frequent) {
                    most_frequent = occurrences_array[j];
                    index = j;
                }
            }

            // If there are less than 10 different characters in the file this prevents entries with no occurrences from
            // being printed.
            if (occurrences_array[index] != 0) {
                //Ensure that only printable characters are printed. Otherwise, only the character number is printed.
                if (index >= 32 && index <= 126) {
                    printf("\tChar n. %3u ['%c']: appears %d times\n", (uint8_t) index,
                           index, occurrences_array[index]);
                } else {
                    printf("\tChar n. %3u: appears %d times\n", (uint8_t) index, occurrences_array[index]);
                }
                //Ensures that already printed characters won't get printed again.
                occurrences_array[index] = 0;
            }
        }
    }

    free(file_name);
    fclose(my_file);
    return 0;
}

//Function to validate the filename (improved, more self-contained).
char *input_string() {
    char *string;
    bool success = false;
    while (success == false) {
        int allocated = 0;

        string = (char *) malloc(sizeof(char));
        if (string == NULL) {
            printf("Error allocating memory. Ending program.");
            exit(1);
        }
        string[0] = '\0';

        bool read_string = true;
        while (read_string == true) {
            int character = getchar();
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

        if (strlen(string) == 0) {
            free(string);
            printf("Enter valid file name: ");
        } else {
            success = true;
        }
    }

    return string;
}