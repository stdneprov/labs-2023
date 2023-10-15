#include <stdio.h>

int Max(int a, int b) {
    return a > b ? a : b;
}
int Min(int a, int b) {
    return a < b ? a : b;
}
int Mod(int a, int b) {
    return (a % b) >= 0 ? a % b : b + (a % b);
}
int Abs(int a) {
    return a >= 0 ? a : -a;
}
int Cube(int a) {
    return a * a * a;
}

int main(void) {
    int i = -10;
    int j = -10;
    int l = 6;
    int res = 0;

    for (int k = 1; k <= 50; k++) {
        int i1 =
            Abs(Max(Mod(Min(i + j, i + l), 30), Mod(Max(i + l, j + k), 25)));
        int j1 =
            Mod(Abs(i + k), 10) + Mod(Abs(j + k), 10) + Mod(Abs(l + k), 10);
        int l1 = Mod((Cube(i) + Cube(j) + Cube(l) - k), 35);
        i = i1;
        j = j1;
        l = l1;
        if (i == 10 && j == 0) {
            res |= 0x000f;
        }
        if (i == 30 && j == 0) {
            res |= 0x00f0;
        }
        if (i == 20 && j == 5) {
            res |= 0x0f00;
        }
        if (i == 20 && j == -5) {
            res |= 0xf000;
        }
        if (res == 0xffff) {
            printf("YES %d\n", k);
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
