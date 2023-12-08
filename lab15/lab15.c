#include <stdio.h>


enum { maxn = 8 };

int main() {
    int matrix[maxn][maxn];

    int n;
    scanf("%d", &n);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int SumOfDiagElem = 0;
    int CrossingWithSideDiag = 0;
    int j = 0;
    int k = n - 1;
    int m = 0;
    for (int i = n - 1; i >= 0; --i) {
        int b = i;
        while (i != (n)) {
            if (k == i && m == j) {
                CrossingWithSideDiag = 1;
            }
            SumOfDiagElem += matrix[i][j];
            j += 1;
            i += 1;
        }

        if (CrossingWithSideDiag == 1) {
            matrix[k][m] = SumOfDiagElem;
            k -= 1;
            m += 1;
        }

        i = b;
        j = 0;
        SumOfDiagElem = 0;
        CrossingWithSideDiag = 0;
    }
    
    int i = 0;
    for (int j = 1; j < n; j++) {
        int c = j;
        while(j != n) {
            if (k == i && m == j) {
                CrossingWithSideDiag = 1;
            }
            SumOfDiagElem += matrix[i][j];
            i += 1;
            j += 1;
        }

        if (CrossingWithSideDiag == 1) {
            matrix[k][m] = SumOfDiagElem;
            k -= 1;
            m += 1;
        }

        j = c;
        i = 0;
        SumOfDiagElem = 0;
        CrossingWithSideDiag = 0;
    }
    
    for (int k = 0; k != n; ++k) {
        for (int m = 0; m != n; ++m) {
            printf("%d ", matrix[k][m]);
        }
        putchar('\n');
    }

}