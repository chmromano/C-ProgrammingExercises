#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMR "N."
#define ADDR "Address"
#define PWD "Password"

#define PRINT_ALL (char *) "*\0"
#define READ_BIN "rb"
#define WRITE_BIN "wb"

#define OPTIONS_PROMPT "\nWelcome. Available options:\n\n1. Open existing file\n2. Create new file\n3. "\
"Quit\n\nChoose an option: "
#define INVALID_INT_MAIN_MSG "Invalid input. Enter a valid choice (1-3): "
#define INVALID_CHOICE_MAIN_MSG "Invalid choice. Enter a valid choice (1-3): "
#define FILE_OPEN_MSG "\nEnter file to open: "
#define FILE_CREATE_MSG "\nCreating file. Enter file name: "
#define EMPTY_STRING_MSG "\nString cannot be empty. Enter a valid string: "
#define QUIT_MSG "\nQuitting program...\n"

#define ENTRY_OPERATIONS_PROMPT "\nAvailable operations:\n\n1. New entry\n2. Search entry by address\n3. Print entries "\
"report\n4. Delete entry by address\n5. Save and exit\n6. Exit without saving\n\nChoose an operation: "
#define INVALID_INT_COMMAND_MSG "Invalid input. Enter a valid choice (1-6): "
#define INVALID_CHOICE_COMMAND_MSG "Invalid choice. Enter a valid choice (1-6): "

#define NO_PWD_MSG "\nNo passwords stored.\n"

#define FILE_ERROR_MSG printf("There was an error opening the file.\n")
#define MEM_CHECK(x) if(x == NULL){printf("There was an error allocating memory. Quitting program...");exit(1);}

typedef struct entry_ {
    int addr_len;
    char *addr;
    int pwd_len;
    char *pwd;
} ENTRY;

typedef enum {
    NO_OPTION, OPEN_EXISTING, CREATE_NEW, QUIT
} OPTION;

ENTRY *new_entry(ENTRY *entry_array, int *array_len);

char *decrypt(char *pwd, int pwd_len, char *master);

void print_entries(char *addr, ENTRY *entry_array, int array_len);

ENTRY *read_entries(int *array_len, FILE *file);

void write_entries(ENTRY *entry_array, int array_len, FILE *file);

bool input_integer(int *input);

char *input_string();

int main() {
    OPTION chosen_option = NO_OPTION;
    while (chosen_option != QUIT) {
        ENTRY *entry_array;
        entry_array = NULL;
        int array_len = 0;

        char *file_name;
        FILE *working_file = NULL;

        printf(OPTIONS_PROMPT);

        while (chosen_option == NO_OPTION) {

            int choice_main;
            while (input_integer(&choice_main) == false) printf(INVALID_INT_MAIN_MSG);

            switch (choice_main) {
                case 1:
                    printf(FILE_OPEN_MSG);
                    file_name = input_string();
                    working_file = fopen(file_name, READ_BIN);
                    if (working_file == NULL) {
                        FILE_ERROR_MSG;
                    } else {
                        chosen_option = OPEN_EXISTING;
                        entry_array = read_entries(&array_len, working_file);
                        fclose(working_file);
                    }
                    break;
                case 2:
                    printf(FILE_CREATE_MSG);
                    file_name = input_string();
                    working_file = fopen(file_name, WRITE_BIN);
                    if (working_file == NULL) {
                        FILE_ERROR_MSG;
                    } else {
                        chosen_option = CREATE_NEW;
                    }
                    array_len = 0;
                    entry_array = malloc(sizeof(ENTRY));
                    MEM_CHECK(entry_array)
                    break;
                case 3:
                    chosen_option = QUIT;
                    printf(QUIT_MSG);
                    break;
                default:
                    printf(INVALID_CHOICE_MAIN_MSG);
                    break;
            }
        }

        if (chosen_option == CREATE_NEW || chosen_option == OPEN_EXISTING) printf(ENTRY_OPERATIONS_PROMPT);

        while (chosen_option == CREATE_NEW || chosen_option == OPEN_EXISTING) {

            char *addr_search;

            int chosen_operation;
            while (input_integer(&chosen_operation) == false) printf(INVALID_INT_COMMAND_MSG);
            switch (chosen_operation) {
                case 1:
                    entry_array = new_entry(entry_array, &array_len);
                    break;
                case 2:
                    printf("\nEnter website to search: ");
                    addr_search = input_string();
                    print_entries(addr_search, entry_array, array_len);
                    free(addr_search);
                    break;
                case 3:
                    print_entries(PRINT_ALL, entry_array, array_len);
                    break;
                case 4:
                    break;
                case 5:
                    chosen_option = NO_OPTION;
                    working_file = fopen(file_name, WRITE_BIN);
                    if (working_file == NULL) {
                        FILE_ERROR_MSG;
                    }
                    write_entries(entry_array, array_len, working_file);
                    fclose(working_file);
                    free(file_name);
                    break;
                case 6:
                    chosen_option = NO_OPTION;
                    free(entry_array);
                    free(file_name);
                    break;
                default:
                    printf(INVALID_CHOICE_COMMAND_MSG);
                    break;
            }
        }
    }

    return 0;
}

bool delete_entry(char *addr, ENTRY *entry_array) {

}

char *encrypt(char *pwd, int pwd_len) {
    int master_index = 0;
    int pwd_index = 0;

    printf("Enter master password: ");
    char *master_buffer;
    master_buffer = input_string();

    pwd_len--;

    pwd[pwd_len] = '\0';

    printf("%s\n", pwd);

    while (pwd_index < pwd_len) {

        pwd[pwd_index] = (char) (pwd[pwd_index] ^ master_buffer[master_index]);

        pwd_index++;
        master_index++;
        if (master_index == (int) strlen(master_buffer)) master_index = 0;
    }

    printf("%s\n", pwd);

    free(master_buffer);

    return pwd;
}

ENTRY *new_entry(ENTRY *entry_array, int *array_len) {
    entry_array = realloc(entry_array, sizeof(ENTRY) * (*array_len + 1));
    MEM_CHECK(entry_array)

    printf("Enter website address: ");
    (entry_array + *array_len)->addr = input_string();
    (entry_array + *array_len)->addr_len = (int) strlen((entry_array + *array_len)->addr) + 1;

    printf("Enter password: ");
    char *pwd_buffer;
    pwd_buffer = input_string();

    printf("%s\n", pwd_buffer);

    (entry_array + *array_len)->pwd_len = (int) strlen(pwd_buffer) + 1;
    (entry_array + *array_len)->pwd = encrypt(pwd_buffer, (entry_array + *array_len)->pwd_len);

    free(pwd_buffer);

    *array_len = *array_len + 1;

    return entry_array;
}

ENTRY *read_entries(int *array_len, FILE *file) {
    ENTRY entry_buffer;
    ENTRY *entry_array;
    entry_array = NULL;

    fread(array_len, sizeof(int), 1, file);

    printf("%d\n", *array_len);

    int i;
    for (i = 0; i < *array_len; i++) {
        fread(&entry_buffer, sizeof(ENTRY), 1, file);
        entry_array = realloc(entry_array, sizeof(ENTRY) * (i + 1));
        MEM_CHECK(entry_array)

        (entry_array + i)->addr_len = entry_buffer.addr_len;
        (entry_array + i)->pwd_len = entry_buffer.pwd_len;

        (entry_array + i)->addr = malloc(sizeof(char) * (entry_array + i)->addr_len);
        MEM_CHECK((entry_array + i)->addr)
        fread((entry_array + i)->addr, sizeof(char), (entry_array + i)->addr_len, file);

        (entry_array + i)->pwd = malloc(sizeof(char) * (entry_array + i)->pwd_len);
        MEM_CHECK((entry_array + i)->pwd)
        fread((entry_array + i)->pwd, sizeof(char), (entry_array + i)->pwd_len, file);
        printf("%s\n", (entry_array + i)->pwd);
    }

    return entry_array;
}

char *decrypt(char *pwd, int pwd_len, char *master) {
    int master_index = 0;
    int pwd_index = 0;

    char *decrypted_pwd;
    decrypted_pwd = malloc(sizeof(char) * pwd_len);
    MEM_CHECK(decrypted_pwd)

    pwd_len--;

    decrypted_pwd[pwd_len] = '\0';

    while (pwd_index < pwd_len) {

        decrypted_pwd[pwd_index] = (char) (pwd[pwd_index] ^ master[master_index]);

        pwd_index++;
        master_index++;
        if (master_index == (int) strlen(master)) master_index = 0;
    }

    return decrypted_pwd;
}

void print_entries(char *addr, ENTRY *entry_array, int array_len) {

    if (array_len == 0) {
        printf(NO_PWD_MSG);
    } else {
        int longest_index = strlen(NMR);
        int longest_addr = strlen(ADDR);
        int longest_pwd = strlen(PWD);

        int index = 0;

        for (int i = 0; i < array_len; i++) {
            if (strcmp(PRINT_ALL, addr) == 0 || strcmp((entry_array + i)->addr, addr) == 0) index++;
            if ((entry_array + i)->addr_len > longest_addr) longest_addr = (entry_array + i)->addr_len;
            if ((entry_array + i)->pwd_len > longest_pwd) longest_pwd = (entry_array + i)->pwd_len;
        }

        /*int digits = 0;
        int temp_index = index;
        while (temp_index != 0) {
            temp_index = temp_index / 10;
            digits++;
        }
        if (digits > longest_index) longest_index = digits;
        digits = 0;*/

        printf("Enter master password: ");
        char *master_buffer;
        master_buffer = input_string();

        printf("%-*s | %-*s | %-*s\n", longest_index, NMR, longest_addr, ADDR, longest_pwd, PWD);

        index = 0;
        for (int i = 0; i < array_len; i++) {
            if (strcmp(PRINT_ALL, addr) == 0 || strcmp((entry_array + i)->addr, addr) == 0) {
                index++;

                char *decrypted_pwd;
                decrypted_pwd = decrypt((entry_array + i)->pwd, (entry_array + i)->pwd_len, master_buffer);

                printf("%*d | %*s | %*s\n", longest_index, index, longest_addr, (entry_array + i)->addr, longest_pwd, decrypted_pwd);

                free(decrypted_pwd);
            }
        }

        free(master_buffer);
    }
}

void write_entries(ENTRY *entry_array, int array_len, FILE *file) {

    printf("%d\n", array_len);

    fwrite(&array_len, sizeof(int), 1, file);

    for (int i = 0; i < array_len; i++) {
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

        string = malloc(sizeof(char));
        MEM_CHECK(string)
        string[0] = '\0';

        bool read_string = true;
        while (read_string == true) {
            int character = getchar();
            if (character == '\n' || character == '\r' || character == '\f') {
                read_string = false;
            } else {
                allocated++;
                string = realloc(string, (allocated + 1) * sizeof(char));
                MEM_CHECK(string)
                string[allocated - 1] = (char) character;
                string[allocated] = '\0';
            }
        }

        if (strlen(string) == 0) {
            free(string);
            printf(EMPTY_STRING_MSG);
        } else {
            success = true;
        }
    }

    return string;
}