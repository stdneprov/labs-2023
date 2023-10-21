#include <stdio.h>
#include <stdlib.h>

#define I0 12
#define J0 4
#define L0 3
#define Max(a,b) (((a) > (b)) ? (a) : (b))
#define ModFixed(a, b) (((a) >= 0) ? (a % b) : (b + (a % b)))

int main() {
    int i = I0, j = J0, l = L0;
    int flag = -1;
    int iNew, jNew;
    for (int k = 0; k <= 50; k++) {
        if (i + j <= -10 && i + j >= -20) {
            flag = k;
            break;
        }
        iNew = ModFixed((i * j/(abs(l) + 1)) + (j * l/(abs(i) + 1)) + (i * l/(abs(j) + 1)), 30);
        jNew = ModFixed(i * Max(j, l), 20) + ModFixed(j * Max(i, l), 30) - k;
        l = ModFixed(Max(Max(i*j, i*l), j*l), 30) + 20;
        i = iNew;
        j = jNew;
    }
    if (flag == -1) {
        printf("NO, i = %d, j = %d, l = %d\n", i, j, l);
    } else {
        printf("YES %d, i = %d, j = %d, l = %d\n", flag, i, j, l);
    }
}