#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define OPTIONS_PROMPT "Choose an option:\n1. Open existing file\n2. Create new file\n3. Quit\n"
#define FILE_ERROR_MSG printf("There was an error opening the file.\n")
#define MEM_CHECK(x) if(x == NULL){printf("There was an error allocating memory. Quitting program...");exit(1);}

typedef struct entry_ {
    unsigned int addr_len;
    char *addr;
    unsigned int pwd_len;
    char *pwd;
} ENTRY;

typedef enum {
    NO_OPTION, OPEN_EXISTING, CREATE_NEW, QUIT
} OPTION;

void new_entry(ENTRY *entry_array);

ENTRY *read_entries(FILE *file);

void write_entries(ENTRY *entry_array, FILE *file);

bool input_integer(int *input);

char *input_string();

int main() {

    ENTRY *entry_array;
    char *file_name;
    FILE *working_file;
    printf("Welcome. %s", OPTIONS_PROMPT);
    int choice_main;
    while (input_integer(&choice_main) == false) printf("Invalid characters.\n");

    OPTION chosen_option = NO_OPTION;
    while (chosen_option != QUIT) {
        switch (choice_main) {
            case 1:
                printf("Enter file to open: ");
                file_name = input_string();
                working_file = fopen(file_name, "rb");
                if (working_file == NULL) {
                    FILE_ERROR_MSG;
                } else {
                    chosen_option = OPEN_EXISTING;
                }
                break;
            case 2:
                printf("Enter file name: ");
                file_name = input_string();
                working_file = fopen(file_name, "wb");
                if (working_file == NULL) {
                    FILE_ERROR_MSG;
                } else {
                    chosen_option = CREATE_NEW;
                }
                break;
            case 3:
                chosen_option = QUIT;
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
                entry_array = malloc(sizeof(ENTRY));
                MEM_CHECK(entry_array)
                entry_array->addr_len = 0;
                entry_array->addr = NULL;
                entry_array->pwd_len = 0;
                entry_array->pwd = NULL;
                new_entry(entry_array);


                printf("\n");
                for (int i = 0; i < entry_array->pwd_len; i++) {
                    printf("%c", entry_array->pwd[i]);
                }
                printf("\n");



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

OPTION option_select(OPTION *option, char *file_name, FILE *file) {

    int choice_main;
    while (input_integer(&choice_main) == false) printf("Invalid characters.\n");

    while (*option != QUIT) {
        switch (choice_main) {
            case 1:
                printf("Enter file to open: ");
                file_name = input_string();
                file = fopen(file_name, "rb");
                if (file == NULL) {
                    FILE_ERROR_MSG;
                } else {
                    *option = OPEN_EXISTING;
                }
                break;
            case 2:
                printf("Enter file name: ");
                file_name = input_string();
                file = fopen(file_name, "wb");
                if (file == NULL) {
                    FILE_ERROR_MSG;
                } else {
                    *option = CREATE_NEW;
                }
                break;
            case 3:
                *option = QUIT;
                printf("Quitting program...");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

bool delete_entry(ENTRY *entry_array) {

}

char *encrypt(char *pwd, unsigned int pwd_len) {
    char *master_buffer;
    int master_index = 0;
    int pwd_index = 0;

    printf("Enter master password: ");
    master_buffer = input_string();

    while (pwd_index < pwd_len) {

        pwd[pwd_index] = (char) (pwd[pwd_index] ^ master_buffer[master_index]);

        pwd_index++;
        master_index++;
        if (master_index > pwd_index) master_index = 0;
    }

    free(master_buffer);
    return pwd;
}

void new_entry(ENTRY *entry_array) {
    char *pwd_buffer;

    int i;
    for (i = 0; (entry_array + i)->addr != NULL; i++);
    entry_array = realloc(entry_array, sizeof(ENTRY) * (i + 2));
    entry_array[i + 1] = entry_array[i];

    printf("Enter website address: ");
    (entry_array + i)->addr = input_string();
    (entry_array + i)->addr_len = (unsigned int) strlen((entry_array + i)->addr) + 1;

    printf("Enter password: ");
    pwd_buffer = input_string();
    (entry_array + i)->pwd_len = (unsigned int) strlen(pwd_buffer);
    (entry_array + i)->pwd = encrypt(pwd_buffer, (unsigned int) (entry_array + i)->pwd_len);

    free(pwd_buffer);
}

ENTRY *read_entries(FILE *file) {
    ENTRY entry_buffer;
    ENTRY *entry_array;
    entry_array = NULL;

    for (int i = 0; fread(&entry_buffer, sizeof(ENTRY), 1, file) != 0; i++) {
        entry_array = (ENTRY *) realloc(entry_array, sizeof(ENTRY) * (i + 1));
        MEM_CHECK(entry_array)

        (entry_array + i)->addr_len = entry_buffer.addr_len;
        (entry_array + i)->pwd_len = entry_buffer.pwd_len;

        (entry_array + i)->addr = malloc(sizeof(char) * (entry_array + i)->addr_len);
        MEM_CHECK((entry_array + i)->addr)
        fread((entry_array + i)->addr, sizeof(char), (entry_array + i)->addr_len, file);

        (entry_array + i)->pwd = malloc(sizeof(char) * (entry_array + i)->pwd_len);
        MEM_CHECK((entry_array + i)->pwd)
        fread((entry_array + i)->pwd, sizeof(char), (entry_array + i)->pwd_len, file);
    }

    return entry_array;
}

void write_entries(ENTRY *entry_array, FILE *file) {
    for (int i = 0; (entry_array + i)->addr != NULL; i++) {
        fwrite((entry_array + i), sizeof(ENTRY), 1, file);
        fwrite((entry_array + i)->addr, sizeof(char), (entry_array + i)->addr_len, file);
        free((entry_array + i)->addr);
        fwrite((entry_array + i)->pwd, sizeof(char), (entry_array + i)->pwd_len, file);
        free((entry_array + i)->pwd);
    }
    free(entry_array);
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
        MEM_CHECK(string)
        string[0] = '\0';

        bool read_string = true;
        while (read_string == true) {
            int character = getchar();
            if (character == '\n' || character == '\r' || character == '\f') {
                read_string = false;
            } else {
                allocated++;
                string = (char *) realloc(string, (allocated + 1) * sizeof(char));
                MEM_CHECK(string)
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