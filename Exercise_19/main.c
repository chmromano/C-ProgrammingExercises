#include <stdio.h>
#include <stdbool.h>

#define DEBUG

#ifdef DEBUG
#define DEBUGMSG(x, y) printf(x, y)
#else
#define DEBUGMSG(x, y)
#endif

#define LOOP 5

bool input_integer(int *input);

int main() {
    for (int i = 0; i < LOOP; i++) {
        printf("\nLoop %d\nEnter an integer: ", i + 1);
        int input = 0;
        while(input_integer(&input) == false) printf("Wrong input. Enter a valid integer: ");
        DEBUGMSG("DEBUG: input = %d\n", input);
    }
    return 0;
}

//Improved function to validate integer.
bool input_integer(int *input) {
    bool success = true;
    int ch;
    if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        success = false;
    }
    return success;
}