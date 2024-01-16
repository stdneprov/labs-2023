#include <stdio.h>

int Sign(int x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else (x == 0); {
        return 0;
    }
}
int Max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
int Mod(int a, int b) {
    return (a % b + b) % b;
}
int Abs(int x) {
    if (x < 0) {
        return x;
    } else {
        return x;
    }
}
int main() {
    int k = 1;
    int i = 0;
    int j = 0;
    int l = 0;
    int l0 = -7;
    int j0 = -3;
    int i0 = 0;
    for (k; k<=50; k++) {
        i = Abs(i0 - j0 + l0) / (3 - Sign(i0 - j0 + k)) + 10;
        j = Abs(i0 + j0 - l0) / (3 - Sign(j0 - i0 + k)) + 10;
        l = Mod(Max(i0 * j0, j0 * l0) * (k + 1), 40);
        i0 = i;
        j0 = j;
        l0 = l;
        if (k == 50) { 
            printf("NO");
        }
        if (((i - 10) * (i - 10) + (j - 10) * (j - 10) <= 100) && ((i - 10) * (i - 10) + (j - 10) * (j - 10) >= 25)) {
            printf("YES %d", k);
            break;
        }   
    }
}