#include <math.h>
#include <stdio.h>
const int maxn = 100;

int main(void) {
    int len = 0;
    int massive[maxn * maxn];
    int *buff = massive;
    while (scanf("%d", buff++) != EOF) {
        if (len * len < (buff - massive)) {
            ++len;
        }
    }
    for (int j = len - 1; j >= -(len - 1); --j) {
        for (int i = 0; (i + j) <= (len - 1); ++i) {
            if (((i + j) >= 0) && (i < len)) {
                printf("%d ", massive[i * len + i + j]);
            }
        }
    }
    return 0;
}
