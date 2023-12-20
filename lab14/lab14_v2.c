#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\n");
    int mainDiag = (n * 2) - 1;
    int startLine, endLine, column;
    for (int i = 1; i <= mainDiag; i++) {
        if (i <= n) {
            startLine = 1;
            endLine = i;
        } else {
            startLine = i - n + 1;
            endLine = n;
        }

        for (int row = endLine; row >= startLine; row--) {
            column = i - row + 1;
            printf("%d ", matrix[n - column][n - row]);
        }
    }
}
