#include <stdio.h>

//To sort more than 3 numbers just change this
#define TO_READ 3

int main() {
    int unsorted_array[TO_READ] = {};
    int sorted_array[TO_READ] = {};

    int unsorted_array_size = TO_READ;

    int smallest = 0;
    int smallest_index = 0;

    FILE *my_file;
    my_file = fopen("numbers.txt", "r");

    if (my_file == NULL) {
        printf("\nThere was an error opening the file.\n");
    } else {
        for (int i = 0; i < TO_READ; i++) {
            fscanf(my_file, "%d", &unsorted_array[i]);
        }

        for (int i = 0; i < TO_READ; i++) {

            smallest = unsorted_array[0];
            smallest_index = 0;

            for (int j = 0; j < unsorted_array_size; j++) {
                if (unsorted_array[j] < smallest) {
                    smallest = unsorted_array[j];
                    smallest_index = j;
                }
            }

            unsorted_array_size--;
            sorted_array[i] = smallest;

            for (int k = smallest_index; k <= unsorted_array_size; k++) {
                if (smallest_index != unsorted_array_size) {
                    unsorted_array[k] = unsorted_array[k + 1];
                }
            }
        }

        fclose(my_file);
        my_file = fopen("numbers.txt", "w");

        for (int i = 0; i < TO_READ; i++) {
            fprintf(my_file, "%d\n", sorted_array[i]);
        }
    }

    return 0;
}