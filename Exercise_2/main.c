#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 12

int main(void) {
    float my_array[ARRAY_SIZE] = {};
    float income = 0;

    bool valid_input = false;

    printf("Enter yearly gross income: ");

    while (valid_input == false) {
        int ch;

        if (scanf("%f", &income) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            /*I needed a way to validate user inputting a non-integer,
                and from my research this seems like a valid way to "flush"
                the buffer. In broad terms I understand what it does.
                Hope it's alright.*/
            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Incorrect character. Please enter a positive number: ");
        } else if (income <= 0) {
            printf("Please enter a positive number: ");
        } else {
            valid_input = true;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (i == 6) {
            my_array[i] = (income / 12.5) * 1.5;
        } else {
            my_array[i] = income / 12.5;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("element[%2d] = %14.4f\n", i, my_array[i]);
    }

    printf("total       = %14.4f", income);
}