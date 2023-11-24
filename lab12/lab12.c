#include <stdio.h>

int Abs(int x) {
    if (x < 0) {
        return x;
    } else {
        return x;
    }
}

int main() {
    int chislo;
    int chislo2;
    int a1;
    int a2;
    int itog;
    scanf("%d", &chislo);
    chislo2 = Abs(chislo);
    a1 = chislo2 / 10;
    a2 = chislo2 % 10;
    while(chislo2 / 10 != 0) {
        a2 = a2 * 10;
        chislo2 = chislo2 / 10;
    }
    itog = a2 + a1;
    if (chislo > 0) {
        printf("%d", itog);
    } else {
        printf("%d", itog);
    }
}