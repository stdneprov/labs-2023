#include <stdbool.h>
#include <stdio.h>


void InputMatrix(int *m, int size){
    for (int i = 0; i < size * size; i++){
        scanf("%d", &m[i]);
    }
}

void PrintMatrix(int *m, int size) {
    for (int i = 0; i < size * size; i++) {
        printf("%d", m[i]);
        if (((i + 1) % size) == 0) {
            putchar('\n');
        } else {
            putchar(' ');
        }
    }
}

void SquareMatrix(int *m, int *r, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int result = 0;
            for (int k = 0; k < size; k++) {
                result += m[i * size + k] * m[k * size + j];
            }
            r[i * size + j] = result;
        }
    }
}

int main() {
    int m[64];
    int result[64];
    int size = 0;
    scanf("%d", &size);
    InputMatrix(m, size);

    SquareMatrix(m, result, size);
    PrintMatrix(result, size);
}
