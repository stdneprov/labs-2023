#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int mod(int a, int b) {
    return (a % b + b) % b;
}

int sign(int a) {
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

int abs(int a) {
    if (a>0 && a<0) {
        return a;
    }
    else {
        return 0;
    }
}

int sqr(int a) {
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