#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define READ_B "rb"
#define N_CHAR_256 256
#define N_CHAR_10 10

char *validate_filename();

typedef struct occurrences_ {
    uint8_t character;
    int occurrences;
} OCCUR;

int main() {
    //Get file name and open file.
    printf("Enter file to read from: ");
    char *file_name = NULL;
    file_name = validate_filename();
    FILE *my_file;
    my_file = fopen(file_name, READ_B);
    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        //Initialise array.
        OCCUR occurrences_array[N_CHAR_256] = {};
        for (int i = 0; i < N_CHAR_256; i++) {
            occurrences_array[i].character = (uint8_t) i;
            occurrences_array[i].occurrences = 0;
        }

        //Count the characters in the file.
        uint8_t character;
        while (fread(&character, 1, 1, my_file) != 0) {
            for (int i = 0; i < N_CHAR_256; i++) {
                if (character == occurrences_array[i].character) occurrences_array[i].occurrences++;
            }
        }

        //Find and print the most frequent characters.
        printf("10 most frequent characters:\n");
        for (int i = 0; i < N_CHAR_10; i++) {

            //Find the most frequent characters.
            int most_frequent = 0;
            int index = 0;
            for (int j = 0; j < N_CHAR_256; j++) {
                if (occurrences_array[j].occurrences > most_frequent) {
                    most_frequent = occurrences_array[j].occurrences;
                    index = j;
                }
            }

            //Print the most frequent characters.
            printf("\tChar n. %3u [%c]: appears %d times\n", occurrences_array[index].character,
                   occurrences_array[index].character, occurrences_array[index].occurrences);

            //Indicates that characters has been found and printed.
            occurrences_array[index].occurrences = 0;
        }
    }

    free(file_name);
    fclose(my_file);
    return 0;
}

//Function to validate the filename (improved).
char *validate_filename() {
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