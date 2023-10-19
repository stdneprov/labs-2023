#include <stdio.h>
#include <stdlib.h>

#define I0 8
#define J0 15
#define L0 10

int Min(int a, int b);
int Max(int a, int b);
int Sign(int a);

int main() {
    int ik = I0;
    int jk = J0;
    int lk = L0;
    int iNew = ik;
    int jNew = jk;
    int lNew = lk;
    int result = 0;
    for (int k = 1; k <= 50; k++) {
        iNew = ((ik + jk) % (abs(Min(jk - lk, lk - k)) + 1) - k) % 20 + 10;
        jNew = Max((ik + jk) / (2 + Sign(jk * lk - ik * k)), (jk + lk) / (2 + Sign(ik * jk - lk * k))) - 10;
        lNew = Max(ik, jk) * Min(ik, lk) % 30;
        if ((iNew >= -10) && (iNew <= 0) && (iNew <= 10 - jNew) && (iNew <= jNew - 10)){
            result = 1;
            printf("YES %d\n", k);
            printf("Coordinates: (%d;%d)\n", ik, jk);
            printf("Motion parameter value: %d\n", lk);
            break;
        }
        ik = iNew;
        jk = jNew;
        lk = lNew;
    }
    if (result == 0)
        printf("NO");
    return 0;
}

int Min(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

int Max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int Sign(int a) {
    if (a > 0)
        return 1;
    else if (a == 0)
        return 0;
    else
        return -1;
}