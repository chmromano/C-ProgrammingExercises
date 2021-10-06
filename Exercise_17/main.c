#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_LENGTH 32
#define FILE_NAME "file"
#define READ_B "rb"
#define APPEND_B "ab"

void write_car(char file_name[]);

void print_cars(char file_name[]);

void validate_number(int *input, bool choice);

void validate_string(char string[], bool make);

void validate_float(float *input);

struct car {
    char make[STRING_LENGTH];
    char model[STRING_LENGTH];
    int price;
    float emissions;
};

int main() {
    bool run = true;
    while (run == true) {
        printf("\nAvailable commands:\n\n1. Print all cars in the file\n2. Add new car to end of file\n"
               "3. Quit the program\n\nChoose a command: ");

        int input = 0;
        validate_number(&input, true);

        switch (input) {
            case 1:
                print_cars(FILE_NAME);
                break;
            case 2:
                write_car(FILE_NAME);
                break;
            case 3:
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

void print_cars(char file_name[]) {
    FILE *my_file;
    my_file = fopen(file_name, READ_B);

    if (my_file == NULL) {
        print_cars("There was an error opening the file.");
    } else {
        struct car car;
        for (int i = 1; fread(&car, sizeof(struct car), 1, my_file) != 0; ++i) {
            printf("\nCar no. %d:\n\tMake:      %s\n\tModel:     %s\n\tPrice:     %d€\n\tEmissions: %.1f g(co2)/km\n",
                   i, car.make, car.model, car.price, car.emissions);
        }
    }

    fclose(my_file);
}

void write_car(char file_name[]) {
    FILE *my_file;
    my_file = fopen(file_name, APPEND_B);

    if (my_file == NULL) {
        print_cars("There was an error opening the file.");
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