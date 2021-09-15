#include <stdio.h>
#include <stdbool.h>

int verify_int();

float verify_float();

int main() {
    int n_to_read = 0;
    float sum = 0;

    FILE *my_file;
    my_file = fopen("numbers.txt", "r");

    if (my_file == NULL) {
        printf("\nThere was an error opening the file.\n");
    } else {
        fscanf(my_file, "%d", &n_to_read);

        for (int i = 0; i < n_to_read; i++) {
            float tmp_float = 0;
            fscanf(my_file, "%f", &tmp_float);
            sum += tmp_float;
        }

        printf("Average of %d numbers is: %.2f", n_to_read, sum / (float) n_to_read);
    }

    return 0;
}

/*
int verify_int() {
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

float verify_float() {
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
*/