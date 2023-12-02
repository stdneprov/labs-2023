#include <stdio.h>

void PrintMatrix(int n, int *matrix) {
    int offset_x[4] = {1, 0, -1, 0};
    int offset_y[4] = {0, 1, 0, -1};
    int x_s = 0, x_e = n - 1, y_s = 0, y_e = n - 1;
    int x = 0;
    int y = 0;
    int dir = 0;
    for (int i = 0; i < n * n; i++) {
        printf("%d ", matrix[y * n + x]);
        if (x + offset_x[dir % 4] > x_e) {
            dir++;
            y_s++;
        } else if (x + offset_x[dir % 4] < x_s) {
            dir++;
            y_e--;
        } else if (y + offset_y[dir % 4] > y_e) {
            dir++;
            x_e--;
        } else if (y + offset_y[dir % 4] < y_s) {
            dir++;
            x_s++;
        }
        x += offset_x[dir % 4];
        y += offset_y[dir % 4];
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
