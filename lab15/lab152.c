#include <stdio.h>

enum { Maxa = 100 };

int main() {
    int n[Maxa][Maxa];
    int a;
    scanf("%d", &a);
    for (int i = 0; i != a; ++i) {
        for (int j = 0; j != a; ++j) {
            scanf("%d", &n[i][j]);
        }
    }
    long long x1;
    long long x2 = a;
    long long max = n[0][0];
    long long min = n[0][0];  
    for (int i = 0; i != a; i++) {
        for (int j = 0; j != a; j++) {
            if (n[i][j] >= max) {
                if ((x2 > j) && (max == n[i][j])) {
                    x2 = j;
                } else if (max != n[i][j]) {
                    x2 = j;
                }
                max = n[i][j];
            } 
            if (n[i][j] < min) {
                min = n[i][j];
                x1 = i;
            }
        }
    }
    for (int i = 0; i != a; ++i) {
        for (int j = 0; j != a; ++j) {
            if (i == x1) {
                printf("%d ", n[i][j] * n[j][x2]);
            } else {
                printf("%d ", n[i][j]);
            }
        }
        printf("\n");
    }
}