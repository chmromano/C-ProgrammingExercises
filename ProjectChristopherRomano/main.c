#include "main.h"
#include "strings.h"
#include "helper_functions.h"
#include "password_functions.h"

int main() {
    OPTION chosen_option = NO_OPTION;
    while (chosen_option != QUIT) {
        ENTRY *entry_array;
        entry_array = NULL;
        int array_len;

        char *file_name;
        file_name = NULL;
        FILE *working_file = NULL;

        OPTIONS_PROMPT;

        while (chosen_option == NO_OPTION) {

            char character = 0;

            int choice_main;
            while (input_integer(&choice_main) == false) INVALID_INT_MAIN_MSG;

            switch (choice_main) {
                case 1:
                    FILE_OPEN_MSG;
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
                    FILE_CREATE_MSG;
                    file_name = input_string();
                    working_file = fopen(file_name, READ_BIN);
                    if(working_file != NULL) {
                        FILE_EXISTS_MSG;
                        while (input_y_n(&character) == false) INVALID_CHAR_MSG;
                    }
                    fclose(working_file);
                    if (character != NO_CHAR) {
                        working_file = fopen(file_name, WRITE_BIN);
                        if (working_file == NULL) {
                            FILE_ERROR_MSG;
                        } else {
                            chosen_option = CREATE_NEW;
                        }
                        array_len = 0;
                        entry_array = malloc(sizeof(ENTRY));
                        mem_check(entry_array);
                    } else {
                        chosen_option = NO_OPTION;
                        OPTIONS_PROMPT;
                    }
                    break;
                case 3:
                    chosen_option = QUIT;
                    QUIT_MSG;
                    break;
                default:
                    INVALID_CHOICE_MAIN_MSG;
                    break;
            }
        }

        if (chosen_option == CREATE_NEW || chosen_option == OPEN_EXISTING) ENTRY_OPERATIONS_PROMPT;

        while (chosen_option == CREATE_NEW || chosen_option == OPEN_EXISTING) {

            char *addr_search;

            int chosen_operation;
            while (input_integer(&chosen_operation) == false) INVALID_INT_COMMAND_MSG;
            switch (chosen_operation) {
                case 1:
                    entry_array = new_entry(entry_array, &array_len);
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 2:
                    WEBSITE_SEARCH_MSG;
                    addr_search = input_string();
                    print_entries(addr_search, entry_array, array_len);
                    free(addr_search);
                    PRESS_ENTER;
                    getchar();
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 3:
                    print_entries(PRINT_ALL, entry_array, array_len);
                    PRESS_ENTER;
                    getchar();
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 4:
                    ENTRY_OPERATIONS_PROMPT;
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
                    INVALID_CHOICE_COMMAND_MSG;
                    break;
            }
        }
    }

    return 0;
}

