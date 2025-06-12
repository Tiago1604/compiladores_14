#include <stdio.h>

int main() {
int maior;
int y;
int x;
    x = 3;
    y = 7;
    if (x > y) {
        maior = x;
    } else {
        maior = y;
        printf("%d\n", maior);
    }
    return 0;
}
