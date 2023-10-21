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
    int i = 5, j = 5, l = 4, k = 0, I, J, L;
    while (k<=51) {
        if (k == 51) {
            printf("NO\n");
            break;
        }
        else {
            if (((sqr(i+10) + sqr(j+10)) <= 100) && ((sqr(i+20) + sqr(j+20))<=100)) {
                printf("YES %d\n", k);
                break;
            }
        }
    I = i;
    J = j;
    L = l;
    i = I / 3 - abs(I-k)*sign(L-J);
    j = mod(J,10) - mod(max(I, L), k+1);
    l = I + mod(J*k, 5) + L / 5 + 3;
    k = k + 1;
    }
}