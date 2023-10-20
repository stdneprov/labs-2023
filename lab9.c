#include <stdio.h>
#include <stdlib.h>

#define I0 12
#define J0 4
#define L0 3
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define modFixed(a, b) (((a) >= 0) ? (a % b) : (b + (a % b)))

int main() {
    int i = I0, j = J0, l = L0;
    int flag = -1;
    int iNew, jNew;
    for (int k = 0; k <= 50; k++) {
        if (i + j <= -10 && i + j >= -20) {
            flag = k;
            break;
        }
        iNew = modFixed((i * j/(abs(l) + 1)) + (j * l/(abs(i) + 1)) + (i * l/(abs(j) + 1)), 30);
        jNew = modFixed(i * max(j, l), 20) + modFixed(j * max(i, l), 30) - k;
        l = modFixed(max(max(i*j, i*l), j*l), 30) + 20;
        i = iNew;
        j = jNew;
    }
    if (flag == -1) {
        printf("NO, i = %d, j = %d, l = %d\n", i, j, l);
    } else {
        printf("YES %d, i = %d, j = %d, l = %d\n", flag, i, j, l);
    }
}