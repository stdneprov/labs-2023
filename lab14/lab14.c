#include <stdio.h>


enum { maxn = 7 };

int main() {
    int MatrixIn[maxn][maxn];
    int MatrixOut[maxn][maxn];
    int n;
    scanf("%d", &n);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            scanf("%d", &MatrixIn[i][j]);
        }
    }

    int j = 0;
    int k = 0;
    int m = 0;
    for (int i = n - 1; i >= 0; --i) {
        int b = i;
        while (i != (n)) {
            MatrixOut[k][m] = MatrixIn[i][j];
            m += 1;
            if (m == n) {
                k += 1;
                m = 0;
            }

            j += 1;
            i += 1;
        }
        i = b;
        j = 0;
    }
    
    int i = 0;
    for (int j = 1; j < n; j++) {
        int c = j;
        while(j != n) {
            MatrixOut[k][m] = MatrixIn[i][j];
            m += 1;
            if (m == n) {
                k += 1;
                m = 0;
            }
            
            i += 1;
            j += 1;
        }
        j = c;
        i = 0;
    }

    for (int k = 0; k != n; ++k) {
        for (int m = 0; m != n; ++m) {
            printf("%d ", MatrixOut[k][m]);
        }
    }

    putchar('\n');
}