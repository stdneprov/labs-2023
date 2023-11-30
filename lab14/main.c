#include <stdio.h>
#include <stdlib.h>
const int maxn = 400;


int main() {

    int elements[maxn];
    int min = 1e5;

    int size = 0; // количество элементов
    int n = 0; // порядок матрицы
    
    while (scanf("%d", &elements[size]) != EOF) {
        if (elements[size] < min) {
            min = elements[size];
        }
        ++size;
        if (n * n < size) {
            ++n;
        }
    }

    int matrix[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = elements[i * n + j];
        }
    }

    for (int k = 1; k < (n + 1) / 2 + 1; ++k) { // номер "кольца", начиная с внешних

        int y = n - k, x = n - k; // устанавливаем начальный элемент (правый нижний угол текущего кольца)

        while (y >= k - 1) { // принтим правую сторону снизу вверх, пока не уйдем за пределы
            
            printf("%d ", matrix[y][x]);
            --y;
        }
        ++y;
        --x; // корректируем положение следующего элемента

        while (x >= k - 1) { // принтим верхнюю сторону справа налево

            printf("%d ", matrix[y][x]);
            --x;
        }
        ++x;
        ++y; // корректируем

        while (y <= n - k) { // принтим левую сторону сверху вниз

            printf("%d ", matrix[y][x]);
            ++y;
        }
        --y;
        ++x; // корректируем

        while (x < n - k) { // принтим нижнюю сторону, пока не упрёмся в начальный элемент

            printf("%d ", matrix[y][x]);
            ++x;
        }
    }

    putchar('\n');
    
    return 0;
}
