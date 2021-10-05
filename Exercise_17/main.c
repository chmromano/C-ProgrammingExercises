#include <stdio.h>
#include <stdbool.h>

#define STRING_LENGTH 30
#define FILE_NAME "file"
#define READ_B "rb"
#define APPEND_B "ab"

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

                getchar();
                break;
            case 2:
                print_cars(FILE_NAME);
                getchar();
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

    if(my_file == NULL) {
        print_cars("There was an error opening the file.");
    } else {
        struct car car;
        for (int i = 1; fread(&car, sizeof(struct car), 1, my_file) != 0; ++i) {
            printf("\nItem %d:\n\tMake: %s\n\tModel: %s\n\tPrice: %d€\n\tEmissions: %f g(co2)/km\n",
                   i, car.make, car.model, car.price, car.emissions);
        }
    }

    fclose(my_file);
}

void write_car(char file_name[]) {
    FILE *my_file;
    my_file = fopen(file_name, APPEND_B);

    if(my_file == NULL) {
        print_cars("There was an error opening the file.");
    } else {
        struct car car;
        for (int i = 1; fread(&car, sizeof(struct car), 1, my_file) != 0; ++i) {
            printf("\nItem %d:\n\tMake: %s\n\tModel: %s\n\tPrice: %d€\n\tEmissions: %f g(co2)/km\n",
                   i, car.make, car.model, car.price, car.emissions);
        }
    }

    fclose(my_file);
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