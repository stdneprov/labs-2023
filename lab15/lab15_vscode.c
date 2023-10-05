//сложение всех столбцов, содержащих мин элемент матрицы, и замена последнего из них на результат сложения

#include <stdio.h>
#include <stdlib.h>

void scanMatrix(int n, int a[n][n]);
void printMatrix(int n, int a[n][n]);
int findMinElem(int n, int a[n][n]);
int findMinColCount(int n, int a[n][n], int minEl);
int calcNewMatrix(int n, int a[n][n], int minEl);

int main()
{
    int matrixSize;
    printf("enter matrix size: ");
    scanf("%d", &matrixSize);
    if ((matrixSize >= 1) && (matrixSize <= 8)){
        int matrix[matrixSize][matrixSize];
        scanMatrix(matrixSize, matrix); //вводим матрицу
        printf("\nbefore:");
        printMatrix(matrixSize, matrix); //выводим исходную матрицу
        int minElem = findMinElem(matrixSize, matrix);
        int minColCount = findMinColCount(matrixSize, matrix, minElem);
        if (minColCount > 1) //если мин столбцов больше 1
            calcNewMatrix(matrixSize, matrix, minElem); //считаем сумму и вставляем в последний мин столбец
        printf("\nafter:");
        printMatrix(matrixSize, matrix);
    }
    return 0;
}

void scanMatrix(int n, int a[n][n])
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("enter element [%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

int findMinElem(int n, int a[n][n])
{
    int minElem = a[0][0];
    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if (a[i][j] < minElem)
                minElem = a[i][j];
        }
    }
    return minElem;
}

int findMinColCount(int n, int a[n][n], int minEl)
{
    int minColCount = 0;
    int minColNum = -1;
    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if ((a[i][j] == minEl) && (j != minColNum)){
                minColNum = j;
                minColCount++;
            }
        }
    }
    return minColCount;
}

int calcNewMatrix(int n, int a[n][n], int minEl)
{
    int minColNum = -1;
    int sum[n];
    for (int k = 0; k < n; k++)
        sum[k] = 0;

    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if ((a[i][j] == minEl) && (j != minColNum)){ //ищем ещё элементы равные минимальному в других столбцах
                for (int p = 0; p < n; p++){
                    sum[p] += a[p][j]; //обновляем сумму
                    minColNum = j;
                }
            }
        }
    }
    for (int j = n - 1; j > 0; j--){
        for (int i = 0; i < n; i++){
            if (a[i][j] == minEl){ //если в столбце встретился мин элемент
                for (int k = 0; k < n; k++)
                    a[k][j] = sum[k]; //меняем столбец на сумму
                return 0;
            }
        }
    }
}

void printMatrix(int n, int a[n][n])
{
    printf("\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][j] < 10)
                printf(" %d ", a[i][j]);
            else
                printf(" %d", a[i][j]);
        }
        printf("\n");
    }
}
