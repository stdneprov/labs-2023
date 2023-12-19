#include <stdio.h>

enum { maxn = 100 };

int main() {
    int n, k, count = 0;
    scanf("%d", &n);
    int m[maxn][maxn];
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            scanf("%d", &m[i][j]);
        }
    }
    for (int i = 0; i != -1; ++i) {
        k = 0;
        while (k <= i) {
            if ((i % 2 != 0) && (n - k - 1 > -1) && (n - (i - k) - 1 > -1)) {
                printf("%d ", m[n - (i - k) - 1][n - k - 1]);
                count += 1;
            } else if ((n - k - 1 > -1) && (n - (i - k) - 1 > -1)) {
                printf("%d ", m[n -  k - 1][n - (i - k) - 1]);
                count += 1;
            }
            k += 1;
            if (count == (n * n)) {
            break;
        }
        }
        if (count == (n * n)) {
            break;
        }
    }
    printf("\n");  
}