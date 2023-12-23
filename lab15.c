#include <stdio.h>
#include <stdbool.h>
#define MAX_N 7


typedef long long Set;

void Add(Set *a, int c) {
    *a |= (1 << c);
}

void Clear(Set *a, int c) {
    *a &= ~(*a);
}

bool IsIn(Set a, int c) {
    return (a & ~(1 << c )) != a;
}


int main() {
    int n;
    int matrix[MAX_N][MAX_N];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d",&matrix[i][j]);
        }
    }
    int minEl = matrix[0][0];
    Set strings = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (minEl > matrix[i][j]) {
                strings = 0;
                minEl = matrix[i][j];
                Add(&strings, i);
            } else if (minEl == matrix[i][j]) {
                Add(&strings, i);
            }
        }
    }
    
    int newMatrix[MAX_N][MAX_N];
    int newMatrixRow = 0;
    for (int i = 0; i < n; i++) {
        if (!IsIn(strings, i)) {
            for (int j = 0; j < n; j++) {
                newMatrix[newMatrixRow][j] = matrix[i][j];
            }
            newMatrixRow++;
        }
    }

    for (int i = 0; i < newMatrixRow; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", newMatrix[i][j]);
        }
        printf("\n");
    }
}