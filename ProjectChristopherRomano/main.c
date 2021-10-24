#include "main.h"
#include "strings.h"
#include "helper_functions.h"
#include "password_functions.h"

int main() {
    //Enter main program loop.
    OPTION chosen_option = NO_OPTION;
    while (chosen_option != QUIT) {
        int array_len;
        ENTRY *entry_array;

        char *file_name;
        FILE *working_file;

        OPTIONS_PROMPT;

        //Enter option selection loop.
        while (chosen_option == NO_OPTION) {

            int choice_main;
            while (input_integer(&choice_main) == false) INVALID_INT_MAIN_MSG;
            switch (choice_main) {
                case 1:
                    //Open an existing file.
                    FILE_OPEN_MSG;
                    file_name = input_string();
                    working_file = fopen(file_name, READ_BIN);
                    if (working_file == NULL) {
                        FILE_ERROR_MSG;
                    } else {
                        chosen_option = OPERATE;
                        //Read entries in the chosen file.
                        entry_array = read_entries(&array_len, working_file);
                    }
                    fclose(working_file);
                    break;
                case 2:
                    //Create a new file.
                    FILE_CREATE_MSG;
                    file_name = input_string();
                    //Check if the file exists. If it does ask user if the file should be overwritten.
                    char character = 0;
                    working_file = fopen(file_name, READ_BIN);
                    if (working_file != NULL) {
                        FILE_EXISTS_MSG;
                        while (input_y_n(&character) == false) INVALID_CHAR_MSG;
                    }
                    fclose(working_file);
                    if (character != NO_CHAR) {
                        chosen_option = OPERATE;
                        entry_array = malloc(sizeof(ENTRY));
                        mem_check(entry_array);
                    } else {
                        //If the file is not overwritten user is taken to option choice.
                        chosen_option = NO_OPTION;
                        free(file_name);
                        OPTIONS_PROMPT;
                    }
                    break;
                case 3:
                    //Quit the program.
                    chosen_option = QUIT;
                    QUIT_MSG;
                    break;
                default:
                    INVALID_CHOICE_MAIN_MSG;
                    break;
            }
        }

        //Enter entry operations loop.
        if (chosen_option == OPERATE) ENTRY_OPERATIONS_PROMPT;
        while (chosen_option == OPERATE) {
            int chosen_operation;
            while (input_integer(&chosen_operation) == false) INVALID_INT_COMMAND_MSG;
            switch (chosen_operation) {
                case 1:
                    //Add a new entry to the array.
                    entry_array = new_entry(entry_array, &array_len);
                    PWD_SAVE_SUCCESS_MSG;
                    PRESS_ENTER_MSG;
                    getchar();
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 2:
                    //Search for an entry by website address.
                    if (array_len == 0) {
                        NO_PWD_MSG;
                    } else {
                        WEBSITE_SEARCH_MSG;
                        char *addr_search;
                        addr_search = input_string();
                        print_entries(addr_search, entry_array, array_len);
                        free(addr_search);
                    }
                    //Letting user look at output.
                    PRESS_ENTER_MSG;
                    getchar();
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 3:
                    //Print all entries.
                    print_entries(PRINT_ALL, entry_array, array_len);
                    //Letting user look at output.
                    PRESS_ENTER_MSG;
                    getchar();
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 4:
                    entry_array = delete_entry(entry_array, &array_len);
                    PRESS_ENTER_MSG;
                    getchar();
                    ENTRY_OPERATIONS_PROMPT;
                    break;
                case 5:
                    //Save and exit. Take user back to initial option selection.
                    working_file = fopen(file_name, WRITE_BIN);
                    if (working_file == NULL) {
                        FILE_ERROR_MSG;
                    } else {
                        write_entries(entry_array, array_len, working_file);
                        PWD_WRITE_SUCCESS_MSG;
                        PRESS_ENTER_MSG;
                        getchar();
                    }
                    fclose(working_file);
                    chosen_option = NO_OPTION;
                    free(file_name);
                    array_len = 0;
                    break;
                case 6:
                    //Exit without saving. Take user back to initial option selection.
                    chosen_option = NO_OPTION;
                    free(entry_array);
                    free(file_name);
                    array_len = 0;
                    break;
                default:
                    INVALID_CHOICE_COMMAND_MSG;
                    break;
            }
        }
    }
    return 0;
}

