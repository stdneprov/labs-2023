#include <stdio.h>

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int Mod(int a, int b) {
    return (a % b + b) % b;
}

int Sign(int a) {
    if (a>0) {
        return 1;
    }
    if (a<0) {
        return -1;
    }
    else {
        return 0;
    }
}

int Abs(int a) {
    return a > 0 ? a : -a;
}

int Sqr(int a) {
    return a * a;
}

int main() {
    int i = 5, j = 5, l = 4, k = 0, i0, j0, l0;
    while (k <= 51) {
        if (k == 51) {
            printf("NO\n");
            break;
        }
        else {
            if (((Sqr(i + 10) + Sqr(j + 10)) <= 100) && ((Sqr(i + 20) + Sqr(j + 20)) <= 100)) {
                printf("YES %d\n", k);
                break;
            }
        }
    i0 = i;
    j0 = j;
    l0 = l;
    i = i0 / 3 - Abs(i0  -k)*Sign(i0 - j0);
    j = Mod(j0, 10) - Mod(Max(i0, l0), k+1);
    l = i0 + Mod(j0 * k, 5) + l0 / 5 + 3;
    k = k + 1;
    }
}