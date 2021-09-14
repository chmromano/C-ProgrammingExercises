#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int input = 0;
    int sum = 0;
    int counter = 0;

    float average = 0;

    bool valid_input = false;

    do {
        int ch;

        printf("Please enter a positive integer: ");

        while (valid_input == false) {
            if (scanf("%d", &input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

                /*I needed a way to validate user inputting a non-integer,
                and from my research this seems like a valid way to "flush"
                the buffer. In broad terms I understand what it does.
                Hope it's alright.*/
                while ((ch = getchar()) != '\n' && ch != EOF);

                printf("Incorrect character. Please enter a positive integer: ");
            } else {
                valid_input = true;
            }
        }

        if (input < 0) {
            printf("Only positive integers are accepted. ");
        } else if (input > 0) {
            sum += input;
            counter++;
        }
        valid_input = false;

    } while (input != 0);

    average = (float) sum / (float) counter;

    printf("Average: %.2f", average);
}
