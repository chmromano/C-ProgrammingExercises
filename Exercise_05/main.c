#include <stdio.h>
#include <stdbool.h>

void multiply(int result_vector[3], int source_vector[3], int matrix[3][3]);

void validate_matrix(int matrix[3][3]);

void validate_vector(int vector[3]);

int main(void) {
    int result_vector[3] = {};
    int source_vector[3] = {};
    int multiplication_matrix[3][3] = {};

    validate_matrix(multiplication_matrix);

    validate_vector(source_vector);

    printf("Multiplication matrix:\n");

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            printf("%4d ", multiplication_matrix[y][x]);
        }
        printf("\n");
    }

    printf("Source vector:\n");

    for (int i = 0; i < 3; i++) {
        printf("%4d ", source_vector[i]);
        printf("\n");
    }

    multiply(result_vector, source_vector, multiplication_matrix);

    printf("Result vector:\n");

    for (int i = 0; i < 3; i++) {
        printf("%4d ", result_vector[i]);
        printf("\n");
    }

    return 0;
}

void multiply(int result_vector[3], int source_vector[3], int matrix[3][3]) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            result_vector[y] += matrix[y][x] * source_vector[x];
        }
    }
}

void validate_matrix(int matrix[3][3]) {
    int tmp_1 = 0;
    int tmp_2 = 0;
    int tmp_3 = 0;

    for (int i = 0; i < 3; i++) {
        int ch;

        bool valid_input = false;

        printf("Enter matrix row %d in [x, y, z] format: ", i + 1);

        while (valid_input == false) {
            if (scanf("%d,%d,%d", &tmp_1, &tmp_2, &tmp_3) != 3 || ((ch = getchar()) != '\n' && ch != EOF)) {

                while ((ch = getchar()) != '\n' && ch != EOF);

                printf("Incorrect character. Enter matrix row %d in [x, y, z] format: ", i + 1);
                continue;
            } else {
                matrix[i][0] = tmp_1;
                matrix[i][1] = tmp_2;
                matrix[i][2] = tmp_3;

                valid_input = true;
            }
        }
    }
}

void validate_vector(int vector[3]) {
    int ch;

    int tmp_1 = 0;
    int tmp_2 = 0;
    int tmp_3 = 0;

    bool valid_input = false;

    printf("Enter source vector in [x, y, z] format: ");

    while (valid_input == false) {
        if (scanf("%d,%d,%d", &tmp_1, &tmp_2, &tmp_3) != 3 || ((ch = getchar()) != '\n' && ch != EOF)) {

            while ((ch = getchar()) != '\n' && ch != EOF);

            printf("Incorrect character. Enter source vector in [x, y, z] format: ");
            continue;
        } else {
            vector[0] = tmp_1;
            vector[1] = tmp_2;
            vector[2] = tmp_3;

            valid_input = true;
        }
    }
}