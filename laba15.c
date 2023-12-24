#include <stdio.h>
#include <stdlib.h>
#define MAXN 10

int main() {
    int n; // размерность матрицы
    scanf("%d", &n);

    int matrix[MAXN][MAXN];
    int flag = 1;
    // Вводим значения элементов матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Проверяем кососимметричность матрицы и заменяем соответствующие элементы на нули
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == -matrix[j][i]) {
                matrix[i][j] = 0;
                matrix[j][i] = 0;
            }
        }
    }

    // Выводим матрицу
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
            if (matrix[i][j] != 0){
                flag = 0;
            }
        }
        printf("\n");
    }

    printf("%d\n", flag);
    return 0;
}