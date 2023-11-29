#include <stdio.h>
#include <stdlib.h>
const int maxn = 20;

/*  
    прога очень чувствительна к формату ввода
    числа в строке разделены ОДНИМ пробелом, лишних пробелов в начале и конце строк быть НЕ ДОЛЖНО
    после последнего числа в строке идет ОДИН перенос строки
    в конце и в начале НЕ ДОЛЖНО БЫТЬ пустых строк
    то есть например:

    11 12 13 14\n
    21 22 23 24\n
    31 32 33 34\n
    41 42 43 44EOF

    спасибо за понимание
*/

int ColumnSumm(int matrix[maxn][maxn], int x, int size) { // сумма всех элементов x-го столбца 
    int sum = 0;
    for (int y = 0; y < size; ++y) {
        sum += matrix[y][x];
    }
    return sum;
}

void PrintMatrix(int matrix[maxn][maxn], int size) { // вывод матрицы
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {

    int matrix[maxn][maxn];
    int min = 1e5;

    char c = ' ';

    int i, j;
    i = 0;
    while (c != EOF) { 
        j = 0;
        c = ' ';
        while (c != '\n' && c != EOF) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
            c = getchar();
            ++j;
        }
        ++i;
    }
    // после ввода в переменной i остаётся количество строк матрицы (то есть её размер)

    int modifiedMatrix[maxn][maxn];

    for (int x = 0; x < i; ++x) {
        int cs = ColumnSumm(matrix, x, i);

        for (int y = 0; y < i; ++y) {

            if (matrix[y][x] == min) {
                modifiedMatrix[y][x] = cs;
            } else {
                modifiedMatrix[y][x] = matrix[y][x];
            }
        }
    }

    PrintMatrix(modifiedMatrix, i);
    
    return 0;
}
