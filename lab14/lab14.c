//вариант 18

#include <stdio.h>
#include <stdlib.h>

void SnakeOutput(int n, int a[n][n]);

int main() {
    int matrixSize = 0;
    scanf("%d", &matrixSize);
    if ((matrixSize >= 2) && (matrixSize <= 7)) {
        int matrix[matrixSize][matrixSize];
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++)
                scanf("%d", &matrix[i][j]);
        }
        SnakeOutput(matrixSize, matrix);
    }
    return 0;
}

void SnakeOutput(int n, int a[n][n]) {
    int step = 1;
    int sign;
    int start = 0;
    if (n % 2 == 0) {
        start = n / 2 - 1;
        sign = 1;
    }
    else {
        start = n / 2;
        sign = -1;
    }
    int curI = start;
    int curJ = start;
    printf("%d ", a[curI][curJ]);
    while (step < n) {
        for (int j = 0; j < step; j++) {
            curJ += 1 * sign;;
            printf("%d ", a[curI][curJ]);
        }
        for (int i = 0; i < step; i++) {
            curI += 1 * sign;
            printf("%d ", a[curI][curJ]);
        }
        sign *= -1;
        step++;
    }
    for (int j = 0; j < step - 1; j++) {
            curJ += 1 * sign;;
            printf("%d ", a[curI][curJ]);
        }
}
