#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define OPTIONS_PROMPT "Choose an option:\n1. Open existing file\n2. Create new file\n3. Quit\n"
#define FILE_ERROR_MSG printf("There was an error opening the file.\n")
#define MEM_ERROR_MSG printf("There was an error allocating memory. Quitting program...")

typedef struct entry_ {
    unsigned int addr_len;
    char *addr;
    unsigned int pwd_len;
    char *pwd;
} ENTRY;

typedef enum {
    NO_OPTION, OPEN_EXISTING, CREATE_NEW
} OPTION;

ENTRY *read_entries(FILE *file);

bool write_entries(ENTRY *entry_array, FILE *file);

bool input_integer(int *input);

char *input_string();

int main() {

    bool run_main = true;
    while (run_main == true) {
        char *file_name;
        FILE *working_file;

        OPTION chosen_option = NO_OPTION;


        printf("Welcome. %s", OPTIONS_PROMPT);

        int choice_main;
        while (input_integer(&choice_main) == false) printf("Invalid characters.\n");
        switch (choice_main) {
            case 1:
                printf("Enter file to open: ");
                file_name = input_string();
                working_file = fopen(file_name, "ab");
                if (working_file == NULL) {
                    FILE_ERROR_MSG;
                } else {
                    chosen_option = OPEN_EXISTING;
                }
                break;
            case 2:
                printf("Enter file name: ");
                file_name = input_string();
                working_file = fopen(file_name, "ab");
                if (working_file == NULL) {
                    FILE_ERROR_MSG;
                } else {
                    chosen_option = CREATE_NEW;
                }
                break;
            case 3:
                run_main = false;
                printf("Quitting program...");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        switch (chosen_option) {
            case OPEN_EXISTING:
                break;
            case CREATE_NEW:
                break;
            default:
                break;
        }
    }

    /*
    FILE *my_file;
    my_file = fopen("image.jpg", "rb");

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {

        unsigned char *array;
        array = NULL;

        unsigned char buffer;

        int i;
        for (i = 1; fread(&buffer, 1, 1, my_file) != 0; i++) {
            array = (unsigned char *) realloc(array, sizeof(unsigned char) * i);
            if (array == NULL) {
                printf("There was an error allocating memory. Ending program.");
                exit(1);
            }
            array[i - 1] = buffer;
        }

        for (int j = 0; j < i; j++) {
            printf("%c", array[j]);
        }

        free(array);
        fclose(my_file);
    }*/

    return 0;
}

ENTRY *read_entries(FILE *file) {
    ENTRY entry_buffer;
    ENTRY *entry_array;
    entry_array = NULL;

    for (int i = 0; fread(&entry_buffer, sizeof(ENTRY), 1, file) != 0; i++) {
        entry_array = (ENTRY *) realloc(entry_array, sizeof(ENTRY) * (i + 1));
        if (entry_array == NULL) {
            MEM_ERROR_MSG;
            exit(1);
        }

        (entry_array + i)->addr_len = entry_buffer.addr_len;
        (entry_array + i)->pwd_len = entry_buffer.pwd_len;

        (entry_array + i)->addr = malloc(sizeof(char) * (entry_array + i)->addr_len);
        if ((entry_array + i)->addr == NULL) {
            MEM_ERROR_MSG;
            exit(1);
        }
        fread((entry_array + i)->addr, sizeof(char), (entry_array + i)->addr_len, file);

        (entry_array + i)->pwd = malloc(sizeof(char) * (entry_array + i)->pwd_len);
        if ((entry_array + i)->pwd == NULL) {
            MEM_ERROR_MSG;
            exit(1);
        }
        fread((entry_array + i)->pwd, sizeof(char), (entry_array + i)->pwd_len, file);
    }

    return entry_array;
}

bool write_entries(ENTRY *entry_array, FILE *file) {
    bool success = true;


    return success;
}


bool input_integer(int *input) {
    bool success = true;
    int ch;
    if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        success = false;
    }
    return success;
}

char *input_string() {
    char *string;
    bool success = false;
    while (success == false) {
        int allocated = 0;

        string = (char *) malloc(sizeof(char));
        if (string == NULL) {
            MEM_ERROR_MSG;
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
                    MEM_ERROR_MSG;
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