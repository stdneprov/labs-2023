#include <stdio.h>


int main() {
    int n;
    scanf("%d", &n);
    int matrix[7][7];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int totalDiag = n + n - 1;
    int startRow = 0;
    int endRow = 0;
    int col = 0;
    for (int diag = 1; diag <= totalDiag; ++diag) {
        if (diag <= n) {
            startRow = 1;
            endRow = diag;
        } else {
            startRow = diag - n + 1;
            endRow = n;
        }

        for (int row = endRow; row >= startRow; --row) {
            col = diag - row + 1;
            printf("%d ", matrix[row - 1][col - 1]);
        }
    }
}