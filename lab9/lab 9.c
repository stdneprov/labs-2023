#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define START_I 10
#define START_J 20
#define START_L -1

int Mod(int x, int y) {
    int k = ((x % y) + y) % y;

    return k;
}

int Sign(int a) {
    if (a > 0) {
        return 1;
    } else if (a == 0) {
        return 0;
    } else {
        return -1;
    }
}


int main() {
    int i = START_I, j = START_J, l = START_L;
    int k;

    for (k = 0; k < 50; k++) {
        
        //Условие
        int newI = Mod((abs(fmax(i * (k + 5), j * (k + 6)))) - (abs(fmin(j * (k + 7), l * (k + 8)))), 20);
        int newJ = Mod((3 - Sign(i - j)) * abs(fmin((i * l) + 5, fmin((j * l) - 3, (i * j) + 6))), 25) - 7;
        int newL = Mod((i), 10) + Mod((j), 10) + Mod((l), 10);
        

        i = newI;
        j = newJ;
        l = newL;

        // попадание в квадрат со стороной 10
        if (i >= 5 && i <= 15 && j >= -15 && j <= -5) {
            printf("YES %d\n", k);
            break;
        }
    }

    if (k == 50) {
        printf("NO\n");
    }

    return 0;
}