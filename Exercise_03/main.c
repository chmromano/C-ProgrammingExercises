#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 100
#define STUDENT_NUMBER 45000

float calculate_average(int array[], int array_size);

int main(void) {
    int students_list[ARRAY_SIZE] = {};
    int n_students = 0;
    int ch;

    bool valid_input = false;

    printf("Please enter number of students to be graded: ");

    while (valid_input == false) {
        if (scanf("%d", &n_students) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

            /*I needed a way to validate user inputting a non-integer,
                and from my research this seems like a valid way to "flush"
                the buffer. In broad terms I understand what it does.
                Hope it's alright.*/
            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Incorrect character. Please enter a valid number: ");
        } else if (n_students < 1 || n_students > ARRAY_SIZE) {
            printf("The system supports 1-100 students. Please enter a valid number: ");
        } else {
            valid_input = true;
        }
    }

    valid_input = false;

    for (int i = 0; i < n_students; i++) {
        int grade = 0;

        printf("Enter grade for student %d: ", i + STUDENT_NUMBER);

        while (valid_input == false) {
            if (scanf("%d", &grade) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {

                while ((ch = getchar()) != '\n' && ch != EOF);

                printf("Incorrect character. Please enter a valid grade for student %d: ", i + STUDENT_NUMBER);
            } else if (grade < 0 || grade > 5) {
                printf("Invalid grade. Please enter a grade from 0 to 5 for student %d: ", i + STUDENT_NUMBER);
            } else {
                valid_input = true;
            }
        }

        students_list[i] = grade;

        valid_input = false;
    }

    printf("Average grade: %.2f", calculate_average(students_list, n_students));
}

float calculate_average(int array[], int array_size) {
    int sum = 0;
    for (int i = 0; i < array_size; i++) {
        sum += array[i];
    }
    return (float) sum / (float) array_size;
}