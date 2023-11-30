#include <stdio.h>
#include <stdlib.h>
const int maxn = 400;

// я не понял как передавать в функции в качестве параметров массивы нефиксированных размеров
// поэтому функции работают через указатель на первый элемент матрицы

int ColumnSumm(int *ptr, int x, int size) { // сумма всех элементов x-го столбца 
    int sum = 0;
    for (int y = 0; y < size; ++y) {
        sum += *(ptr + y * size + x);
    }
    return sum;
}

void PrintMatrix(int *ptr, int size) { // вывод матрицы
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", *(ptr + i * size + j));
        }
        putchar('\n');
    }
}

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
    int *matrixPtr = &matrix[0][0];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = elements[i * n + j];
        }
    }

    int modifiedMatrix[n][n];
    int *modMatrixPtr = &modifiedMatrix[0][0];

    for (int x = 0; x < n; ++x) {
        int cs = ColumnSumm(matrixPtr, x, n);

        for (int y = 0; y < n; ++y) {

            if (matrix[y][x] == min) {
                modifiedMatrix[y][x] = cs;
            } else {
                modifiedMatrix[y][x] = matrix[y][x];
            }
        }
    }

    PrintMatrix(modMatrixPtr, n);
    
    return 0;
}
