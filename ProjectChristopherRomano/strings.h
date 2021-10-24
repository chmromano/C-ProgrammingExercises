//This file is used to hold all strings.

//Print labels
#define NMR "N."
#define ADDR "Address"
#define PWD "Password"

//Option selections strings.
#define OPTIONS_PROMPT printf("\nAvailable options:\n\n1. Open existing file\n2. Create new file\n3. "\
"Quit\n\nChoose an option: ")
#define INVALID_INT_MAIN_MSG printf("Invalid input. Enter a valid choice (1-3): ")
#define INVALID_CHOICE_MAIN_MSG printf("Invalid choice. Enter a valid choice (1-3): ")
#define FILE_EXISTS_MSG printf("A file with that name already exists. Do you want to overwrite it? (Y/N): ")
#define INVALID_CHAR_MSG printf("Invalid character. Enter a valid character (Y/N): ")
#define QUIT_MSG printf("\nQuitting program...\n")

//Password operations menu strings.
#define ENTRY_OPERATIONS_PROMPT printf("\nAvailable operations:\n\n1. New entry\n2. Search entry by address\n3. Print entries "\
"report\n4. Delete entry by address\n5. Save and exit\n6. Exit without saving\n\nChoose an operation: ")
#define INVALID_INT_COMMAND_MSG printf("Invalid input. Enter a valid choice (1-6): ")
#define INVALID_CHOICE_COMMAND_MSG printf("Invalid choice. Enter a valid choice (1-6): ")

//New entry strings.
#define ADDRESS_MSG printf("\nEnter website address: ")
#define PWD_MSG printf("Enter address password: ")
#define MASTER_PWD_MSG printf("Enter master password: ")
#define PWD_SAVE_SUCCESS_MSG printf("\nPassword saved successfully. ")

//Search by address and print entries report strings.
#define WEBSITE_SEARCH_MSG printf("\nEnter website to search: ")
#define NO_WEBSITE_MSG printf("\nNo matches found. ")
#define NO_PWD_MSG printf("\nNo passwords stored. ")

//Password deletion strings.
#define PWD_DELETE_SEARCH_MSG printf("\nEnter website address to delete: ")
#define PWD_DELETE_SUCCESS_MSG printf("\Entry deleted succesfully. ")
#define MULTIPLE_PWD_MSG printf("\nMultiple entries found. ")
#define PWD_DELETE_CHOICE(x) printf("Which entry do you want to delete? (1-%d, 0 to abort): ", x)
#define INVALID_DELETE_MSG(x) printf("Invalid choice. Enter a valid choice (1-%d, 0 to abort): ", x)
#define PWD_DELETE_ABORT_MSG printf("\nPassword deletion aborted. ")

//Save and exit strings.
#define PWD_WRITE_SUCCESS_MSG printf("\nEntries successfully saved. ")

//File handling strings.
#define FILE_OPEN_MSG printf("\nEnter file to open: ")
#define FILE_CREATE_MSG printf("\nCreating file. Enter file name: ")
#define FILE_ERROR_MSG printf("There was an error opening the file.\n")

//General purpose strings.
#define EMPTY_STRING_MSG printf("String cannot be empty. Enter a valid string: ")
#define MEM_ERROR_MSG printf("There was an error allocating memory. Quitting program...")
#define PRESS_ENTER_MSG printf("Press enter to continue.")
#define PRINT_NEWLINE printf("\n")