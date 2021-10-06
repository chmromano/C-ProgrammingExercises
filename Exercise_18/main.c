#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 32
#define FILE_NAME "file"
//Reading modes.
#define READ "r"
#define READ_B "rb"
#define APPEND_B "ab"
//Defined strings.
#define MAKE "make"
#define MODEL "model"
#define PRICE "price"
#define EMISSIONS "emissions"
#define STRING_INTEGERS "1234567890"
#define STRING_FLOATS "1234567890."

bool car_read(char list_file[], char car_file[], char json[]);

void car_write(char file_name[]);

void car_print(char file_name[]);

void validate_number(int *input, bool choice);

void validate_string(char string[], bool make);

void validate_float(float *input);

bool validate_filename(char string[]);

bool read_int(int *input, char string[]);

bool read_float(float *input, char string[]);

struct car {
    char make[STRING_LENGTH];
    char model[STRING_LENGTH];
    int price;
    float emissions;
};

int main() {
    bool run = true;
    while (run == true) {
        printf("\nAvailable commands:\n\n1. Print all cars in the file\n2. Add car manually\n"
               "3. Add car from text file\n4. Quit the program\n\nChoose a command: ");
        int input = 0;
        validate_number(&input, true);
        switch (input) {
            case 1:
                car_print(FILE_NAME);
                break;
            case 2:
                car_write(FILE_NAME);
                break;
            case 3:
                printf("Enter file to read from: ");
                //String to hold filename of json.
                char *car_file = NULL;
                car_file = (char *) malloc(sizeof(char));
                if (car_file == NULL) {
                    printf("Error allocating memory. Ending program.");
                    exit(1);
                }
                car_file[0] = '\0';

                while (validate_filename(car_file) == false);

                //String to hold the actual json (in string form).
                char *json = NULL;
                json = (char *) malloc(sizeof(char));
                if (json == NULL) {
                    printf("Error allocating memory. Ending program.");
                    exit(1);
                }
                json[0] = '\0';

                if (car_read(FILE_NAME, car_file, json)) {
                    printf("\nCar successfully read.\n");
                } else {
                    printf("\nThere was an error reading the car.\n");
                }

                free(car_file);
                free(json);
                break;
            case 4:
                run = false;
                printf("\nQuitting program...\n");
                break;
            default:
                printf("\nInvalid choice.\n");
                break;
        }
    }
    return 0;
}

// Function to read car json from file A and append it to file B. It got very complicated. The parsing and validating is
// done in "blocks" to make it as readable as possible. If any block fails success is set to false for the whole function.
bool car_read(char list_file[], char car_file[], char json[]) {
    bool success = true;

    FILE *my_file;
    my_file = fopen(car_file, READ);
    if (my_file == NULL) {
        printf("There was an error opening the file.");
        success = false;
    } else {
        int allocated = 0;
        int character;
        //Get all characters from the file into a string.
        while ((character = fgetc(my_file)) != EOF) {
            allocated++;
            json = (char *) realloc(json, (allocated + 1) * sizeof(char));
            if (json == NULL) {
                printf("Error reallocating memory. Ending program.");
                exit(1);
            }
            json[allocated - 1] = (char) character;
            json[allocated] = '\0';
        }
        fclose(my_file);

        //Parsing of string starts from here.
        struct car car;
        char *ptr;

        // BLOCK-1: parsing for make. Pointer arithmetic and strstr() to get the index of where it was found. Use of
        // count to keep track of double-quotes delimiters and start reading after the second one that is encountered.
        // Save index_start of the actual value to make it easier to parse. Copy value to struct at the end.
        if ((ptr = strstr(json, MAKE)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            for (int i = position; count != 3; ++i) {
                if (json[i] == 34) {
                    index_start = i + 1;
                    count++;
                }
                if (count == 2) {
                    temp_string[i - index_start] = json[i];
                }
            }
            strcpy(car.make, temp_string);
        } else {
            success = false;
        }

        // BLOCK-2: parsing for model. Same logic as BLOCK-1.
        if ((ptr = strstr(json, MODEL)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            for (int i = position; count != 3; ++i) {
                if (json[i] == 34) {
                    index_start = i + 1;
                    count++;
                }
                if (count == 2) {
                    temp_string[i - index_start] = json[i];
                }
            }
            strcpy(car.model, temp_string);
        } else {
            success = false;
        }

        // I am not proud of these two blocks, but I couldn't come up with anything better.
        // BLOCK-3: parsing for price. Same logic to find start of value as blocks 1 and 2, but use of many booleans to
        // parse and keep track of start or end of numbers (not a perfect implementation), and extra integer validation
        // at the end.
        if ((ptr = strstr(json, PRICE)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            bool numbers_over = false;
            for (int i = position; count != 2; ++i) {
                if (json[i] == 58 || ((json[i] < 48 || json[i] > 57) && numbers_over == true)) {
                    index_start = i + 1;
                    count++;
                }
                if (count == 1) {
                    if (json[i] > 47 && json[i] < 58) {
                        temp_string[i - index_start] = json[i];
                        numbers_over = true;
                    } else if (numbers_over == false && (json[i] < 48 || json[i] > 57)) {
                        temp_string[i - index_start] = json[i];
                    }
                }
            }
            if (!read_int(&car.price, temp_string)) success = false;
        } else {
            success = false;
        }

        // BLOCK-4: parsing for emissions. Same logic as BLOCK-3, with lots of booleans (not a perfect implementation),
        // and extra float validation at the end.
        if ((ptr = strstr(json, EMISSIONS)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            bool numbers_over = false;
            for (int i = position; count != 2; ++i) {
                if (json[i] == 58 || ((json[i] < 48 || json[i] > 57) && numbers_over == true)) {
                    if (json[i] == 46) {
                        numbers_over = false;
                    } else {
                        index_start = i + 1;
                        count++;
                    }
                }
                if (count == 1) {
                    if (json[i] > 47 && json[i] < 58) {
                        temp_string[i - index_start] = json[i];
                        numbers_over = true;
                    } else if ((numbers_over == false && (json[i] < 48 || json[i] > 57))) {
                        temp_string[i - index_start] = json[i];
                    }
                }
            }
            if (!read_float(&car.emissions, temp_string)) success = false;
        } else {
            success = false;
        }

        //If reading was successful append the new car to the other file.
        if (success == true) {
            my_file = fopen(list_file, APPEND_B);
            if (my_file == NULL) {
                printf("There was an error opening the file.");
                success = false;
            } else {
                fwrite(&car, sizeof(struct car), 1, my_file);
            }
            fclose(my_file);
        }
    }

    return success;
}

// Function to print all cars in the file (same as EX17).
void car_print(char file_name[]) {
    FILE *my_file;
    my_file = fopen(file_name, READ_B);

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        struct car car;
        int i;
        for (i = 1; fread(&car, sizeof(struct car), 1, my_file) != 0; ++i) {
            printf("\nCar no. %d:\n\tMake:      %s\n\tModel:     %s\n\tPrice:     %d euro\n\tEmissions: %.1f g(co2)/km\n",
                   i, car.make, car.model, car.price, car.emissions);
        }
        if (i == 1) printf("\nNo cars in the file.\n");
    }

    fclose(my_file);
}

// Manually write car to file (same as EX17).
void car_write(char file_name[]) {
    FILE *my_file;
    my_file = fopen(file_name, APPEND_B);

    if (my_file == NULL) {
        printf("There was an error opening the file.");
    } else {
        char make[STRING_LENGTH] = {};
        char model[STRING_LENGTH] = {};
        int price = 0;
        float emissions = 0;

        printf("\nEnter make: ");
        validate_string(make, true);
        printf("Enter model: ");
        validate_string(model, false);
        printf("Enter price: ");
        validate_number(&price, false);
        printf("Enter emissions: ");
        validate_float(&emissions);

        struct car car;
        strcpy(car.make, make);
        strcpy(car.model, model);
        car.price = price;
        car.emissions = emissions;

        fwrite(&car, sizeof(struct car), 1, my_file);
    }

    fclose(my_file);
}

// Function to validate integers.
void validate_number(int *input, bool choice) {
    int ch;
    bool valid_input = false;

    while (valid_input == false) {
        if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Invalid characters. Please try again: ");
        } else if (choice == false && *input < 0) {
            printf("Invalid price value. Please try again: ");
        } else {
            valid_input = true;
        }
    }
}

// Function to validate strings.
void validate_string(char string[], bool make) {
    bool valid_input = false;
    int ch;

    while (valid_input == false) {
        fgets(string, STRING_LENGTH, stdin);
        if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
            valid_input = true;
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF);

            if (make == true) {
                printf("Make too long. Please try again (maximum 30 characters):");
            } else {
                printf("Model too long. Please try again (maximum 30 characters):");
            }
        }
    }
}

// Function to validate floats.
void validate_float(float *input) {
    int ch;
    bool valid_input = false;

    while (valid_input == false) {
        if (scanf("%f", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Invalid characters. Please try again: ");
        } else if (*input < (float) 0.0) {
            printf("Invalid emissions value. Please try again: ");
        } else {
            valid_input = true;
        }
    }
}

//Function to validate the filename.
bool validate_filename(char string[]) {
    bool success = true;
    bool read_string = true;
    int allocated = 0;

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
        printf("Enter valid file name: ");
        success = false;
    }

    return success;
}

// Function to read integer from string.
bool read_int(int *input, char string[]) {
    bool read_success = true;
    for (int i = 0; i < strlen(string); i++) {
        if (strchr(STRING_INTEGERS, string[i]) == NULL) {
            read_success = false;
            break;
        }
    }
    *input = atoi(string);
    return read_success;
}

// Function to read float from string.
bool read_float(float *input, char string[]) {
    bool read_success = true;
    bool first_dot = false;
    for (int i = 0; i < strlen(string); i++) {
        if (strchr(STRING_FLOATS, string[i]) == NULL) {
            read_success = false;
            break;
        }
        //Checking for invalid second dot.
        if (string[i] == '.') {
            if (first_dot == false) {
                first_dot = true;
            } else {
                read_success = false;
                break;
            }
        }
    }
    *input = (float) atof(string);
    return read_success;
}