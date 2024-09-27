#include <stdio.h>
#include <stdbool.h>

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

int Square(int a) {
    return a * a;
}

bool CheckEllipse(int i, int j) {
    // (i - center_i)^2 / radius_i^2 + (j - center_j) ^ 2 / radius_j^2 <= 1
    // (i - 20)^2 / 10^2 + (j - 0)^2 / radius_j^2 <= 1
    // (i - 20)^2 / 100 + 4*j^2 / 100 <= 1
    // (i - 20)^2  + 4*j^2 <= 100
    return Square(i - 20) + 4 * Square(j) <= 100;
}

int main(void) {
    int i = -10;
    int j = -10;
    int l = 6;
    for (int k = 1; k <= 50; k++) {
        int i1 =
            Abs(Max(Mod(Min(i + j, i + l), 30), Mod(Max(i + l, j + k), 25)));
        int j1 =
            Mod(Abs(i + k), 10) + Mod(Abs(j + k), 10) + Mod(Abs(l + k), 10);
        int l1 = Mod((Cube(i) + Cube(j) + Cube(l) - k), 35);
        i = i1;
        j = j1;
        l = l1;

        if (CheckEllipse(i, j)) {
            printf("YES %d\n", k);
            printf("i=%d\tj=%d\tl=%d\n", i, j, l);
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
