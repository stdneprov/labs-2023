#include <stdio.h>
#include <stdlib.h>
const int maxn = 400;

/*  
    это вариант 25, обход по спирали против часовой с правого нижнего угла
    
    v < < < < <      v < < < <
    v v < < < ^      v v < < ^
    v v v < ^ ^      v v - ^ ^
    v v - ^ ^ ^      v > ^ ^ ^
    v > > ^ ^ ^      > > > ^ |
    > > > > ^ |
*/
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

int main() {

    int elements[maxn]; 
    matrix m = MatrixIn((int *)&elements);

    for (int k = 1; k < (m.size + 1) / 2 + 1; ++k) { // номер "кольца", начиная с внешних

        int y = m.size - k, x = m.size - k; // устанавливаем начальный элемент (правый нижний угол текущего кольца)

        while (y >= k - 1) { // принтим правую сторону снизу вверх, пока не уйдем за пределы
            
            printf("%d ", GetMatrixElem(m, y, x));
            --y;
        }
        ++y;
        --x; // корректируем положение следующего элемента

        while (x >= k - 1) { // принтим верхнюю сторону справа налево

            printf("%d ", GetMatrixElem(m, y, x));
            --x;
        }
        ++x;
        ++y; // корректируем

        while (y <= m.size - k) { // принтим левую сторону сверху вниз

            printf("%d ", GetMatrixElem(m, y, x));
            ++y;
        }
        --y;
        ++x; // корректируем

        while (x < m.size - k) { // принтим нижнюю сторону, пока не упрёмся в начальный элемент

            printf("%d ", GetMatrixElem(m, y, x));
            ++x;
        }
    }

    putchar('\n');
    
    return 0;
}
