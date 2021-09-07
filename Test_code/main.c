#include <stdio.h>

int main() {
    int apple = 3;
    int *fruit = &apple;
    printf("Apple = %d\n", *fruit);

    return 0;
}
