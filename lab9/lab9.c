#include <stdio.h>
#include <stdlib.h>
// Я умею комментить:)
/*
И так тоже могу
*/
int sign(int x) {
    if (x < 0) {
        return -1;
    }
    else if (x > 0) {
        return 1;
    } else {
        return 0;
    }
}
int min(int x, int y) {
    if (x > y) {
        return y;
    }
    else{
        return x;
    }
}
int max(int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}

int main() {
    int i0 = -8, j0 = -5, l0 = 12;
    int i = -8, j = -5, l = 12;
    int d = 0;
    for (int k = 1; k <= 50; k++) {
        i = ((i0 * i0 / (abs(j0 - l0) + k + 1)) - (j0 * j0 / (abs(i0 - l0) + k + 1))) % 30;
        j = sign(l0) * min(i0, j0) - sign(j0) * max(i0,l0) + k;
        l = ((i0 - j0) * (j0 - l0) * (l0 - i0)) % 20;
        l0 = l;
        i0 = i;
        j0 = j;
        if ((i0 >= (-10)) && (i0 <= 0) && (j0 >= i0 + 10) && (j0 <= 10 - i0)){
            printf("Цель попадёт в зону через %d шагов \n", k);
            d = 1;
            break;
        }
    }
    if (d == 0) {
        printf("к цели не пришли");
    }
    printf("Конечная точка: %d %d \n", i0, j0);
    printf("Конечное значение динамического параметра: %d \n", l0);
    return 0;
}
