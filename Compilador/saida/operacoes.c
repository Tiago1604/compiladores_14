#include <stdio.h>

int main() {
int igual;
int w;
int z;
int y;
int x;
    x = 5;
    y = 2;
    z = ((x * y) + 3);
    w = (x / y);
    printf("%d\n", z);
    printf("%d\n", w);
    if (x == y) {
        igual = 1;
    } else {
        igual = 0;
        printf("%d\n", igual);
    }
    return 0;
}
