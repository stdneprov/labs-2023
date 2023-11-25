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

    for (int i = 0; i < n; ++i) {
        int r = m[i][i];
        m[i][i] = m[0 + i][n - i - 1];
        m[0 + i][n - i - 1] = r;
    }

    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    return 0;
}