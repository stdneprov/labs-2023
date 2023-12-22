#include <stdio.h>

#define MAXN 100
#define SHIFT 13

int main() {
    int m [MAXN * MAXN];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n * n; i++) {
        scanf("%d", m + i);
    }

    int ans [MAXN * MAXN];
    for (int i = 0; i < n * n; i++) {
        ans[(i + SHIFT) % (n * n)] = m[i];
    }
    putchar('\n');
    for (int i = 0; i < n * n; i++) {
        printf("%d ", ans[i]);
        if ((i + 1) % n == 0) putchar('\n');
    }
}