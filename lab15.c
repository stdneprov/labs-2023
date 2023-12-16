#include <stdio.h>

#define MAX_SIZE 8
#define SHIFT_COUNT 113

void shiftMatrixClockwise(int matrix[MAX_SIZE][MAX_SIZE], int size, int shiftCount);
void readMatrix(int matrix[MAX_SIZE][MAX_SIZE], int size);

int main() {
    int size;
    int matrix[MAX_SIZE][MAX_SIZE];

    printf("Введи размер матрицы (1 <= N <= 8): ");
    scanf("%d", &size);

    printf("Введи элементы матрицы:\n");
    readMatrix(matrix, size);

    printf("\nИсходная матрица:\n");
    printMatrix(matrix, size);

    shiftMatrixClockwise(matrix, size, SHIFT_COUNT);

    printf("\nМатрица после сдвига:\n");
    printMatrix(matrix, size);

    return 0;
}

void shiftMatrixClockwise(int matrix[MAX_SIZE][MAX_SIZE], int size, int shiftCount) {
    int temp;
    int layer, i;

    while (shiftCount > 0) {
        temp = matrix[0][0];
        for (i = 0; i < size - 1; i++) {
            matrix[0][i] = matrix[0][i + 1];
        }

        for (layer = 1; layer < size - 1; layer++) {
            int next = matrix[layer][size - 1];
            matrix[layer][size - 1] = temp;
            temp = next;
        }

        for (i = size - 2; i >= 0; i--) {
            int next = matrix[size - 1][i];
            matrix[size - 1][i] = temp;
            temp = next;
        }

        for (layer = size - 2; layer >= 1; layer--) {
            int next = matrix[layer][0];
            matrix[layer][0] = temp;
            temp = next;
        }

        shiftCount--;
    }
}

void readMatrix(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}