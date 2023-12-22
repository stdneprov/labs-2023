#include <stdio.h>

enum { M = 100 };

int main() {
    int mat[M][M];
    int x;
    scanf("%d", &x);
    for (int i = 0; i != x; ++i) {
        for (int j = 0; j != x; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
    int x1 = x - 1;
    int x2 = x - 1;
    int k = 0;
    int m = x;
    int j = 0;
    while (1) {
        k += 1;
        printf("%d(0) ", mat[x1][x2]);
        if (k == m * m) {
            break;
        }
        while (x2 != j) {
            x2 -= 1;
            printf("%d(1) ", mat[x1][x2]);
            k += 1;
        }
        while (x1 != j) {
            x1 -= 1;
            printf("%d(2) ", mat[x1][x2]);
            k += 1;
        }
        while (x2 != x - 1) {
            x2 += 1;
            printf("%d(3) ", mat[x1][x2]);
            k += 1;
        }
        while (x1 != x - 2) {
            x1 += 1;
            printf("%d(4) ", mat[x1][x2], x1);
            k += 1;
        }
        j += 1;
        x -= 1;
        // x1 -= 1;
        x2 -= 1;
        if (k == m * m) {
            break;
        }        
        }
}