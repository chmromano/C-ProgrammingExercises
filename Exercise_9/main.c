#include <stdio.h>
#include <stdbool.h>

#define STRING_LENGTH 20
#define ARRAY_LENGTH 15

struct car {
    char make[STRING_LENGTH];
    char model[STRING_LENGTH];
    char category;
    char plate[STRING_LENGTH];
    int mileage;
    bool availability;
};

void list_cars(char character, struct car array[]);

void validate_number(int *input);

int main() {
    bool run = true;
    int command_input = 0;
    char category_input;
    char license_plate_input[STRING_LENGTH] = {};

    struct car rentals[ARRAY_LENGTH] = {
            {"Smart",        "Fortwo",   'M', "TXS243", 24543,  true},
            {"Renault",      "Twizy",    'N', "ALC241", 9023,   true},
            {"Audi",         "A1",       'E', "MKA947", 76023,  false},
            {"Toyota",       "Aygo",     'E', "HFU827", 100293, true},
            {"Ford",         "Focus",    'C', "OKS652", 76201,  true},
            {"Volkswagen",   "ID.3",     'C', "ELC724", 91242,  false},
            {"BMW",          "3 Series", 'I', "JSU735", 86302,  true},
            {"Volvo",        "S90",      'S', "VZW376", 63592,  true},
            {"Jaguar",       "XF",       'S', "UWH571", 34029,  false},
            {"BMW",          "8 Series", 'P', "LWP982", 90283,  true},
            {"Jaguar",       "XJ",       'P', "JGW375", 45932,  false},
            {"Toyota",       "RAV4",     'F', "WZD62",  24543,  true},
            {"Volkswagen",   "Arteon",   'F', "JPA374", 72342,  false},
            {"Aston Martin", "DB11",     'X', "JMB007", 8293,   false},
            {"Lamborghini",  "Huracán",  'X', "LMB287", 13028,  true},
    };

    while (run == true) {
        printf("Available commands:\n1. Print all cars\n2. Print all available cars of a category\n"
               "3. Change car availability\n4. Quit the program\n");
        
        validate_number(&command_input);

        switch (command_input) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                run = false;
                break;
            default:
                break;
        }
    }

    return 0;
}

void list_cars(char character, struct car array[]) {

    printf("Make Model Category Plate Mileage Availability");

    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if ((array[i].category == character && array[i].availability == true) || character == '*') {

        }
    }
}

void validate_number(int *input) {
    int ch;

    bool valid_input = false;

    printf("Choose a command: ");

    while (valid_input == false) {
        if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Invalid characters. Please enter a number from 1 to 4: ");
        } else if (*input < 1 || *input > 4) {
            printf("Please enter a number from 1 to 4: ");
        } else {
            valid_input = true;
        }
    }
}