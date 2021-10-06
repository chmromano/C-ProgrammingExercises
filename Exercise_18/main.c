#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STRING_LENGTH 32
#define FILE_NAME "file"
#define READ_B "rb"
#define APPEND_B "ab"
#define READ "r"
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
    int input = 0;

    while (run == true) {
        printf("\nAvailable commands:\n\n1. Print all cars in the file\n2. Add car manually\n"
               "3. Add car from text file\n4. Quit the program\n\nChoose a command: ");

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

                char *car_file = NULL;
                car_file = (char *) malloc(sizeof(char));
                if (car_file == NULL) {
                    printf("Error allocating memory. Ending program.");
                    exit(1);
                }
                car_file[0] = '\0';

                while (validate_filename(car_file) == false);

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

bool car_read(char list_file[], char car_file[], char json[]) {
    bool success = true;

    int allocated = 0;
    int character = 0;

    FILE *my_file;
    my_file = fopen(car_file, READ);
    if (my_file == NULL) {
        printf("There was an error opening the file.");
        success = false;
    } else {
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

        struct car car;
        char *ptr;

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

        if ((ptr = strstr(json, MODEL)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            position = ptr - json;
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

        /* I am not proud of these two parsers, but I have a very busy week with very little time
        and couldn't come up with anything better, sorry :( */
        if ((ptr = strstr(json, PRICE)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            for (int i = position; count != 8; ++i) {
                if (json[i] < 48 || json[i] > 57) {
                    index_start = i + 1;
                    count++;
                }
                if (count == 7) {
                    temp_string[i - index_start] = json[i];
                }
            }
            if (!read_int(&car.price, temp_string)) success = false;
        } else {
            success = false;
        }

        if ((ptr = strstr(json, EMISSIONS)) != NULL) {
            char temp_string[STRING_LENGTH] = {};
            int position = ptr - json;
            int count = 0;
            int index_start = 0;
            for (int i = position; count != 12; ++i) {
                if ((json[i] < 48 || json[i] > 57) && json [i] != 46) {
                    index_start = i + 1;
                    count++;
                }
                if (count == 11) {
                    temp_string[i - index_start] = json[i];
                }
            }
            if (!read_float(&car.emissions, temp_string)) success = false;
        } else {
            success = false;
        }

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

//Reading integer
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

//Function to read doubles
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
    *input = atof(string);
    return read_success;
}