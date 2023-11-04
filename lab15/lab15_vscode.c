//сложение всех столбцов, содержащих мин элемент матрицы, и замена последнего из них на результат сложения

#include <stdio.h>
#include <stdlib.h>

void ScanMatrix(int n, int a[n][n]);
void PrintMatrix(int n, int a[n][n]);
int FindMinElem(int n, int a[n][n]);
int FindMinColCount(int n, int a[n][n], int minEl);
int CalcNewMatrix(int n, int a[n][n], int minEl);

int main()
{
    int matrixSize;
    printf("enter matrix size: ");
    scanf("%d", &matrixSize);
    if ((matrixSize >= 1) && (matrixSize <= 8)) {
        int matrix[matrixSize][matrixSize];
        ScanMatrix(matrixSize, matrix); //вводим матрицу
        printf("\nbefore:");
        PrintMatrix(matrixSize, matrix); //выводим исходную матрицу
        int minElem = FindMinElem(matrixSize, matrix);
        int minColCount = FindMinColCount(matrixSize, matrix, minElem);
        if (minColCount > 1) //если мин столбцов больше 1
            CalcNewMatrix(matrixSize, matrix, minElem); //считаем сумму и вставляем в последний мин столбец
        printf("\nafter:");
        PrintMatrix(matrixSize, matrix);
    }
    return 0;
}

void ScanMatrix(int n, int a[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("enter element [%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

int FindMinElem(int n, int a[n][n]) {
    int minElem = a[0][0];
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (a[i][j] < minElem)
                minElem = a[i][j];
        }
    }
    return minElem;
}

int FindMinColCount(int n, int a[n][n], int minEl) {
    int minColCount = 0;
    int minColNum = -1;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if ((a[i][j] == minEl) && (j != minColNum)) {
                minColNum = j;
                minColCount++;
            }
        }
    }
    return minColCount;
}

int CalcNewMatrix(int n, int a[n][n], int minEl) {
    int minColNum = -1;
    int sum[n];
    for (int k = 0; k < n; k++)
        sum[k] = 0;

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if ((a[i][j] == minEl) && (j != minColNum)) { //ищем ещё элементы равные минимальному в других столбцах
                for (int p = 0; p < n; p++) {
                    sum[p] += a[p][j]; //обновляем сумму
                    minColNum = j;
                }
            }
        }
    }
    int flag = 0;
    for (int j = n - 1; j > 0; j--) {
        for (int i = 0; i < n; i++) {
            if ((a[i][j] == minEl) && (flag == 0)) { //если в столбце встретился мин элемент
                for (int k = 0; k < n; k++)
                    a[k][j] = sum[k]; //меняем столбец на сумму
                flag = 1;
            }
        }
    }
    return 0;
}

void PrintMatrix(int n, int a[n][n]) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < 10)
                printf(" %d ", a[i][j]);
            else
                printf(" %d", a[i][j]);
        }
        printf("\n");
    }
}
