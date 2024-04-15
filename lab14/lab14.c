#include <stdio.h>

enum { Maxa = 100 };

int main() {
    int n[Maxa][Maxa];
    int a;
    scanf("%d", &a);
    int x1;
    int x2;
    for (int i = 0; i != a; ++i) {
        for (int j = 0; j != a; ++j) {
            scanf("%d", &n[i][j]);
        }
    }
    int i = 0;
    x2 = a - 1;
    x1 = 0;
    int count = 0;
    int k = a;
    while (1) {
        printf("%d ", n[x1][x2]);
        count += 1;
        if (count == k * k) {
            break;
        }
        while (x1 != a - 1) {
            x1 += 1;
            printf("%d ", n[x1][x2]);
            count += 1;
        }
        while (x2 != i) {
            x2 -= 1;
            printf("%d ", n[x1][x2]);
            count += 1;
        }
        while (x1 != i) {
            x1 -= 1;
            printf("%d ", n[x1][x2]);
            count += 1;
        }
        while (x2 != a - 2) {
            x2 += 1;
            printf("%d ", n[x1][x2]);
            count += 1;
        }
        i += 1;
        x1 += 1;
        a -= 1;
        x2 = a - 1;
        if (count == k * k) {
            break;
        }    
    }
}