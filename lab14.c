#include <stdio.h>

enum { maxn = 100 };

int main() {
    int m[maxn][maxn];
    int dir[4] = { 0, 1, 0, -1 };
    int n;
    scanf("%d", &n);
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != n; ++j)
        scanf("%d", &m[i][j]);

    int l = 0;
    int p = 0;
    int i = (n - 1) / 2, j = (n - 1) / 2;
    while (l!= n) {
        l += (p + 1) % 2;
        for (int k = 0; k != l; ++k) {
            printf("%d ", m[i][j]);
            j += dir[p % 4];
            i += dir[(p + 1) % 4];
        }
        ++p;
    }
    putchar('\n');
    
}