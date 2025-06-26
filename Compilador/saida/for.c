#include <stdio.h>

int main() {
int soma;
    soma = 0;
    for (int i = 0; i < 5; i++) {
        soma = (soma + i);
        printf("%d\n", soma);
    }
    return 0;
}
