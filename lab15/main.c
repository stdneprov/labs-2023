#include <stdio.h>
#include <stdlib.h>
const int maxn = 400;


typedef struct
{
    int *ptr;
    int size;
} matrix;

matrix MatrixIn(int *ptr) { // ввод матрицы
    
    int *writer = ptr;
    int n = 0;
    while (scanf("%d", writer++) != EOF) {

        if (n*n < (writer - ptr)) {
            ++n;
        }
    }

    matrix res = {ptr, n};
    return res;
}

int GetMatrixElem(matrix mx, int i, int j) { // удобное получение элемента в 0-индексации
    return *(mx.ptr + i * mx.size + j);
}

void PutMatrixElem(matrix mx, int i, int j, int el) { // удобная запись элемента в 0-индексации
    int *where = mx.ptr + i * mx.size + j;
    *where = el;
}

void PrintMatrix(matrix mx) { // вывод матрицы
    for (int i = 0; i < mx.size; ++i) {
        for (int j = 0; j < mx.size; ++j) {
            printf("%d ", GetMatrixElem(mx, i, j));
        }
        putchar('\n');
    }
}

int ColumnSumm(matrix mx, int x) { // сумма всех элементов x-го столбца 
    int sum = 0;
    for (int y = 0; y < mx.size; ++y) {
        sum += GetMatrixElem(mx, y, x);
    }
    return sum;
}

int main() {

    int elements[maxn]; 
    matrix m = MatrixIn((int *)&elements);

    int min = 1e5;
    for (int i = 0; i < m.size; ++i) {
        for (int j = 0; j < m.size; ++j) {
            if (GetMatrixElem(m, i, j) < min) {
                min = GetMatrixElem(m, i, j);
            }
        }
    }

    int cs;
    for (int x = 0; x < m.size; ++x) {
        cs = ColumnSumm(m, x);
        for (int y = 0; y < m.size; ++y) {
            if (GetMatrixElem(m, y, x) == min) {
                PutMatrixElem(m, y, x, cs);
            }
        }
    }

    PrintMatrix(m);
    
    return 0;
}
