#include <stdio.h>
#define MAX_N 7


int main() {
    int matrix[MAX_N][MAX_N];
    int n;
    int newMatrix[MAX_N][MAX_N];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { //вводим матрицу
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 0; i < n; i++) { //создание копии исходной матрицы
        for (int j = 0; j < n; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    int minElem = matrix[0][0];

    for (int i = 0; i < n; i++) { //находим минимальный элемент
        for (int j = 0; j < n; j++) {
            if (minElem > matrix[i][j]) {
                minElem = matrix[i][j];
            }
        }
    }
    int newElemFlag = 0;
    
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == minElem && newElemFlag == 0) {
                for (int f = 0; f < n; f++) {
                    newMatrix[i][f] = matrix[i][n - 1 - f];
                }
                newElemFlag = 1;
            }
        }
        newElemFlag = 0;
     }
    printf("\n");
    for (int i = 0; i < n; i++) { //вывод ответа
        for (int j = 0; j < n; j++) {
            printf("%d ", newMatrix[i][j]);
        }
        printf("\n");
    }

}
