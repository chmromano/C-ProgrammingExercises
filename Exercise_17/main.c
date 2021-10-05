#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_LENGTH 30
#define FILE_NAME "file"
#define READ_B "rb"
#define APPEND_B "ab"

void write_car(char file_name[]);

void print_cars(char file_name[]);

void validate_number(int *input);

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
        printf("\nAvailable commands:\n\n1. Print all cars in the file\n2. Add new car to end of file\n"
               "3. Quit the program\n\nChoose a command: ");

        validate_number(&input);

        switch (input) {
            case 1:
                print_cars(FILE_NAME);
                break;
            case 2:
                write_car(FILE_NAME);
                break;
            case 3:
                run = false;
                break;
            default:
                printf("\nIncorrect input.\n");
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
            printf("\nCar no. %d:\n\tMake: %s\n\tModel: %s\n\tPrice: %d€\n\tEmissions: %.3f g(co2)/km\n",
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
        scanf("%s", make);
        printf("Enter model: ");
        scanf("%s", model);
        printf("Enter price: ");
        scanf("%d", &price);
        printf("Enter emissions: ");
        scanf("%f", &emissions);

        struct car car;
        strcpy(car.make, make);
        strcpy(car.model, model);
        car.price = price;
        car.emissions = emissions;

        fwrite(&car, sizeof(struct car), 1, my_file);
    }

    fclose(my_file);
}

void validate_number(int *input) {
    int ch;
    bool valid_input = false;

    while (valid_input == false) {
        if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("\nInvalid characters. Please enter a number from 1 to 3: ");
        } else {
            valid_input = true;
        }
    }
}