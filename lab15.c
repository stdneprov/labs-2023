#include <stdio.h>
#define MAX_N 7


int main() {
    int matrix[MAX_N][MAX_N];
    int n;
    int NewMatrix[MAX_N][MAX_N];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { //вводим матрицу
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 0; i < n; i++) { //создание копии исходной матрицы
        for (int j = 0; j < n; j++) {
            NewMatrix[i][j] = matrix[i][j];
        }
    }

    int MinElem = matrix[0][0];

    for (int i = 0; i < n; i++) { //находим минимальный элемент
        for (int j = 0; j < n; j++) {
            if (MinElem > matrix[i][j]) {
                MinElem = matrix[i][j];
            }
        }
    }
    int NewElemFlag = 0;
    
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == MinElem && NewElemFlag == 0) {
                for (int f = 0; f < n; f++) {
                    NewMatrix[i][f] = matrix[i][n - 1 - f];
                }
                NewElemFlag = 1;
            }
        }
        NewElemFlag = 0;
     }
    printf("\n");
    for (int i = 0; i < n; i++) { //вывод ответа
        for (int j = 0; j < n; j++) {
            printf("%d ", NewMatrix[i][j]);
        }
        printf("\n");
    }

}