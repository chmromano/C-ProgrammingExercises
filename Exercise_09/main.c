#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define STRING_LENGTH 20
#define ARRAY_LENGTH 15
#define CATEGORY_LIST "MNECISFPX"

struct car {
    char make[STRING_LENGTH];
    char model[STRING_LENGTH];
    char category;
    char plate[STRING_LENGTH];
    int mileage;
    bool availability;
};

void list_cars(char character, struct car array[]);

bool change_state(char string[], struct car array[]);

void validate_number(int *input);

void validate_character(char *character);

void validate_string(char string[]);

int main() {
    bool run = true;

    int command_input = 0;
    char category_input;
    char license_plate_input[STRING_LENGTH] = {};

    struct car rentals[ARRAY_LENGTH] = {
            //If you really need more than 20 characters to store any of the strings please modify STRING_LENGTH
            {"Smart",        "Fortwo",    'M', "TXS243", 24543,  true},
            {"Renault",      "Twizy",     'N', "ALC241", 9023,   true},
            {"Audi",         "A1",        'E', "MKA947", 846023, false},
            {"Toyota",       "Aygo",      'E', "HFU824", 100293, true},
            {"Ford",         "Focus",     'C', "OKS652", 76201,  true},
            {"Volkswagen",   "ID.3",      'C', "ELC724", 91242,  false},
            {"BMW",          "3 Series",  'I', "JSU735", 86302,  true},
            {"Volvo",        "S90",       'S', "VZW376", 63592,  true},
            {"Jaguar",       "XF",        'S', "UWH571", 34029,  false},
            {"BMW",          "8 Series",  'P', "LWP982", 90283,  true},
            {"Jaguar",       "XJ",        'P', "JGW375", 45932,  false},
            {"Toyota",       "RAV4",      'F', "WZD624", 24543,  true},
            {"Volkswagen",   "Arteon",    'F', "JPA374", 72342,  false},
            {"Aston Martin", "DB11",      'X', "JMB007", 8293,   false},
            {"Lamborghini",  "Aventador", 'X', "LMB287", 13028,  true},
    };

    while (run == true) {
        printf("\nAvailable commands:\n\n1. Print all cars\n2. Print all available cars of a category\n"
               "3. Change car availability\n4. Quit the program\n\nChoose a command: ");

        validate_number(&command_input);

        switch (command_input) {
            case 1:
                list_cars('*', rentals);
                printf("\nPress enter to continue.");
                getchar();
                break;
            case 2:
                printf("\nChoose a category (M, N, E, C, I, S, F, P, or X): ");
                validate_character(&category_input);
                list_cars(category_input, rentals);
                printf("\nPress enter to continue.");
                getchar();
                break;
            case 3:
                printf("\nEnter a license plate: ");
                validate_string(license_plate_input);
                if ((change_state(license_plate_input, rentals)) == true) {
                    printf("\nChange successful. Press enter to continue.");
                } else {
                    printf("\nLicense plate not found. Press enter to continue.");
                }
                getchar();
                break;
            case 4:
                printf("\nProgram stopped.\n");
                run = false;
                break;
            default:
                printf("\nIncorrect input.\n");
                break;
        }
    }

    return 0;
}


void list_cars(char character, struct car array[]) {
    int make_size = strlen("Make");
    int model_size = strlen("Model");
    int category_size = strlen("Category");
    int plate_size = strlen("Plate");
    int mileage_size = strlen("Mileage");
    int availability_size = strlen("Availability");

    int digits = 0;

    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if ((array[i].category == character && array[i].availability == true) || character == '*') {
            if (strlen(array[i].make) > make_size) {
                make_size = (int) strlen(array[i].make);
            }

            if (strlen(array[i].model) > model_size) {
                model_size = (int) strlen(array[i].model);
            }

            if (strlen(array[i].plate) > plate_size) {
                plate_size = (int) strlen(array[i].plate);
            }

            int temp_mileage = array[i].mileage;
            while (temp_mileage != 0) {
                temp_mileage = temp_mileage / 10;
                digits++;
            }
            if (digits > mileage_size) {
                mileage_size = digits;
            }

            digits = 0;
        }
    }

    printf("\n%-*s | %-*s | %-*s | %-*s | %-*s | %-*s\n", make_size, "Make", model_size, "Model", category_size,
           "Category", plate_size, "Plate", mileage_size, "Mileage", availability_size, "Availability");

    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if ((array[i].category == character && array[i].availability == true) || character == '*') {
            printf("%-*s | %-*s | %-*c | %-*s | %*d | ", make_size, array[i].make, model_size, array[i].model,
                   category_size, array[i].category, plate_size, array[i].plate, mileage_size, array[i].mileage);
            if (array[i].availability == true) {
                printf("%-*s\n", availability_size, "Available");
            } else if (array[i].availability == false) {
                printf("%-*s\n", availability_size, "Unavailable");
            }
        }
    }
}


bool change_state(char string[], struct car array[]) {

    //License plate letters are converted to uppercase
    for (int i = 0; i < strlen(string); i++) {
        string[i] = toupper(string[i]);
    }

    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if (strcmp(string, array[i].plate) == 0) {
            array[i].availability = !(array[i].availability);
            return true;
        }
    }

    return false;
}

void validate_number(int *input) {
    int ch;
    bool valid_input = false;

    while (valid_input == false) {
        if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("\nInvalid characters. Please enter a number from 1 to 4: ");
        } else {
            valid_input = true;
        }
    }
}

void validate_character(char *character) {
    int ch;
    bool valid_input = false;

    while (valid_input == false) {
        if (scanf("%c", character) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("\nError. Choose a valid category (M, N, E, C, I, S, F, P, or X): ");
        }

        *character = toupper(*character);

        if (strchr(CATEGORY_LIST, *character) == NULL) {
            printf("\nError. Choose a valid category (M, N, E, C, I, S, F, P, or X): ");
        } else {
            valid_input = true;
        }
    }
}

void validate_string(char string[]) {
    bool valid_input = false;
    int ch;

    while (valid_input == false) {
        fgets(string, STRING_LENGTH, stdin);
        if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
            valid_input = true;
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Plate too long. Enter a plate (maximum 18 characters):\n");
        }
    }
}