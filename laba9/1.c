#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

#define I0 -12
#define J0 -22
#define L0 11

int Mod(int x, int y) {
    int k = ((x % y) + y) % y;
    return ((x % y) + y) % y;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int Sign(int x) {
    return (x > 0) - (x < 0);
}

int Abs(int a) {
    return a > 0 ? a : -a;
}

int main() {
    int i = I0, j = J0, l = L0;
    int flag = 0;

    for (int k = 0; k < 50; k++) {
        int iN = Max(Mod(Min(i - j, j - l), 20), Mod(Min(i - l, j - k), 20)) + 10;
        int jN = Sign(i - j) * Min(Mod(i, 20), Mod(j, 20)) - Mod(Max(Abs(j - l), Abs(k - 20)), 20) + 20;
        int lN = Mod(i, 10) * Mod(j, 10) + Mod(l, 10);


        i = iN; 
        j = jN;
        l = lN;

        if (i >= -10 && (j >= i + 10) && (j <= -i + 10)) {
            printf("YES %d\n", k);
            flag = 1;
            break;
        }


    }

    if (!flag) {
        printf("NO\n");

    }
}
