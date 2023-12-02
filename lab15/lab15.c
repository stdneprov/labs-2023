// Умножение матрицы на транспонированную
#include <stdio.h>

#define MAX_N 8

void PrintMat(int n, int *mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", mat[i * MAX_N + j]);
            printf((j + 1) % n == 0 ? "\n" : " ");
        }
    }
}

void Transpose(int n, int *mat, int *res) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[j * MAX_N + i] = mat[i * MAX_N + j];
        }
    }
}

void MultiplyMat(int n, int *a, int *b, int *res) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i * MAX_N + j] = 0;
            for (int k = 0; k < n; k++) {
                res[i * MAX_N + j] += a[i * MAX_N + k] * b[k * MAX_N + j];
            }
        }
    }
}

int main(void) {
    int mat[MAX_N][MAX_N], trans[MAX_N][MAX_N], res[MAX_N][MAX_N], n;
    while (scanf("%d", &n) > 0) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &mat[i][j]);
        Transpose(n, mat[0], trans[0]);
        MultiplyMat(n, mat[0], trans[0], res[0]);
        PrintMat(n, res[0]);
        printf("\n");
    }

    return 0;
}
