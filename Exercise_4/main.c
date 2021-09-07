#include <stdio.h>
#include <stdbool.h>

void validate_input(int *hour, int *minutes);

int main(void) {
    int cur_hours = 0;
    int cur_minutes = 0;

    int sleep_hours = 0;
    int sleep_minutes = 0;

    int wake_hours = 0;
    int wake_minutes = 0;

    int cur_total = 0;
    int wake_total = 0;

    printf("Enter current time (24 hour format, hh:mm): ");

    validate_input(&cur_hours, &cur_minutes);

    printf("How long do you want to sleep (24 hour format, hh:mm): ");

    validate_input(&sleep_hours, &sleep_minutes);

    cur_total = cur_hours * 60 + cur_minutes;

    wake_total = cur_total + sleep_hours * 60 + sleep_minutes;

    if (wake_total > 24 * 60) {
        wake_total -= 24 * 60;
    }

    wake_minutes = wake_total % 60;
    wake_hours = wake_total / 60;
    if (wake_hours == 24) {
        wake_hours = 0;
    }

    printf("You will wake up at %02d:%02d", wake_hours, wake_minutes);

    return 0;
}

void validate_input(int *hours, int *minutes) {
    int ch;

    bool valid_input = false;

    while (valid_input == false) {
        if (scanf("%d:%d", hours, minutes) != 2 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Enter time in hh:mm 24 hour format: ");
            continue;
        }

        if (*hours > 23 || *hours < 0 || *minutes > 59 || *minutes < 0) {
            printf("Enter hours in range 0-23, minutes range 0-59: ");
        } else {
            valid_input = true;
        }
    }
}