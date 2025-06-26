#include <stdio.h>

int main() {
int x;
    x = 0;
    for (int i = 0; i < 3; i++) {
        x = (x + i);
        if (x > 2) {
            printf("%d\n", x);
        }
    }
    return 0;
}
