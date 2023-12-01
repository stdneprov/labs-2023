#include <stdio.h>

int FindMax(int n, int m[n][n]) {
    long long max = -1e18, jSt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m[i][j] > max) {
                max = m[i][j];
                jSt = j;
            }
        }
    }
    return jSt;
}

void SwapValues(int n, int maxSt, int m[n][n]) {
    int DigitsFromSt[n];
    for (int i = 0; i < n; ++i) {
        DigitsFromSt[i] = m[i][maxSt];
    }
    for (int i = 0; i < n; ++ i){
        m[i][maxSt] = DigitsFromSt[n - i - 1];
    }
}

void PrintResult(int n, int m[n][n]) {
    printf("\n");
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int m[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &m[i][j]);
        }
    }

    SwapValues(n, FindMax(n, m), m);
    PrintResult(n, m);
    return 0;
}