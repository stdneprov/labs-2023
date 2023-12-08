#include <stdio.h>

void PrintMatrix(int n, int *matrix) {
    int x0 = 0, x1 = n - 1, y0 = 0, y1 = n - 1;
    int i = n * n;
    while (i > 0) {
        for (int x = x0; x <= x1; x++) {
            printf("%d ", matrix[y0 * n + x]);
            i--;
        }
        y0++;
        for (int y = y0; y <= y1; y++) {
            printf("%d ", matrix[y * n + x1]);
            i--;
        }
        x1--;
        for (int x = x1; x >= x0; x--) {
            printf("%d ", matrix[y1 * n + x]);
            i--;
        }
        y1--;
        for (int y = y1; y >= y0; y--) {
            printf("%d ", matrix[y * n + x0]);
            i--;
        }
        x0++;
    }
    printf("\n");
}

#define N 4

int main(void) {
    int matrix[N][N] = {
        {1, 2, 6, 7},
        {3, 5, 8, 13},
        {4, 9, 12, 14},
        {10, 11, 15, 16},
    };
    PrintMatrix(N, &matrix[0][0]);
    return 0;
}
