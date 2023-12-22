#include <stdio.h>


int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
        }


    // Находим максимальный элемент в нижнетреугольной матрице
    int min = matrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
    }

    // Умножаем элементы на 
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            matrix[i][j] *= min;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}