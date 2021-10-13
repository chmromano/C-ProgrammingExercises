#include <stdio.h>
#include <stdbool.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUGMSG(x, y) printf(x, y)
#else
#define DEBUGMSG(x, y)
#endif

#define LOOP 5

bool get_integer(int *input);

int main() {
    for (int i = 0; i < LOOP; i++) {
        int input = 0;
        printf("Loop %d\nEnter an integer: ", i + 1);
        while(get_integer(&input) == false) printf("Wrong input. Enter a valid integer: ");
        DEBUGMSG("Loop variable: %d\n\n", input);
    }
    return 0;
}

//Improved function to validate integer.
bool get_integer(int *input) {
    bool success = true;
    int ch;
    if (scanf("%d", input) != 1 || ((ch = getchar()) != '\n' && ch != EOF)) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        success = false;
    }
    return success;
}