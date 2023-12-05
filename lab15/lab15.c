#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[8][8];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int maxElem = 0;
    int minStr = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > maxElem) {
                maxElem = matrix[i][j];
                minStr = i;
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += matrix[minStr][i];
    }
    printf("%d", sum);
}