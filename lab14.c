#include <stdio.h>
#include <stdlib.h>

enum { maxn = 100 };

int main() {
    int n;
    printf("Введи размер матрицы(n): ");
    scanf("%d", &n);
    int matrix[maxn][maxn];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
        
    }
    int circle = 1;
    printf("\n");
    while(circle < (n + 1) / 2 + 1) { 
        int line = n - circle, row = circle - 1; 
        while (line >= circle - 1) { 
            printf("%d ", matrix[line][row]);
            --line;
        }
        ++line;
        ++row; 
        while (row <= n - circle) { 
            printf("%d ", matrix[line][row]);
            ++row;
        }
        --row;
        ++line; 
        while (line <= n - circle) { 
            printf("%d ", matrix[line][row]);
            ++line;
        }
        --line;
        --row;
        while (row > circle - 1) { 
            printf("%d ", matrix[line][row]);
            --row;
        }
        circle++;
    }
    return 0;
}