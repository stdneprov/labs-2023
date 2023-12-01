#include <stdio.h>

#define MAXN 100

int main() {
    int m[MAXN][MAXN];
    int s[MAXN * MAXN];
    int k = 0;
    while (scanf("%d", s + k) != EOF) k++;
    int n = 0;
    while (k > n * n) n++;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = s[i * n + j];
        }
    }
    int i = 0;
    int j = n;
    for (int k = 1; k <= n; k++) {
        i += 1 - (k % 2);
        j += 0 - (k % 2);
        printf("%d ", m[i][j]);
        for (int p = 1; p < k; p++) {
            i += 2 * (k % 2) - 1;
            j += 2 * (k % 2) - 1;
            printf("%d ", m[i][j]);
        }
    }
    for (int k = n - 1; k >= 1; k--) {
        i += 0 + (k % 2);
        j += -1 + (k % 2);
        printf("%d ", m[i][j]);
        for (int p = 1; p < k; p++) {
            i += 2 * (k % 2) - 1;
            j += 2 * (k % 2) - 1;
            printf("%d ", m[i][j]);
        }
    }
    return 0;
}