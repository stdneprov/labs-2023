#include <stdio.h>
#include <math.h>


int defineSgn(int val) {
    if(val > 0){
        return 1;
    }
    else if(val < 0){
        return -1;
    }
    return 0;
   
}

int Mod(int x, int div) {
    int m = x % div;
    if(m < 0) {
        m = (div < 0) ? m - div: m + div;
    }
    return m;
}


int main() {
    int i = -11, j = -6, l = -5;
    int k;

    for (k = 0; k < 50; k++) {
        int newI = Mod((i + j + l) * (k + l), 25) - Mod(i * j * l * (k + 2), 10) + 10;
        int newJ = fmin(Mod((i + j + l) * (k + 3), 25), Mod(i * j * l * (k + 4), 25)) + 10;
        int newL = 2 * defineSgn(l) * abs(Mod((i + j + l) * (k + 5), 10) - Mod(i * j * l * (k + 6), 25));
        
        i = newI;
        j = newJ;
        l = newL;

        if (i >= 5 && i <= 15 && j >= -15 && j <= -5) {
            printf("Попадание на шаге %d. Время: %d, Координаты: (%d, %d), l: %d\n", k, k + 1, i, j, l);
            break;
        }
    }

    if (k == 50) {
        printf("Промах. Время окончания: %d, Координаты: (%d, %d), l: %d\n", k, i, j, l);
    }

    return 0;
}
