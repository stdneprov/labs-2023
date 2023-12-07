#include <stdio.h>
#define MAX_N 4


int main() {
    int matrix[MAX_N][MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int row_Start = MAX_N;
    int row_End = 0;
    int col_Start = 0;
    int col_End = MAX_N;
    while (row_Start > row_End && col_Start < col_End) {
        for (int i = row_Start - 1; i >= row_End; i--) {
            printf("%d ", matrix[col_Start][i]);
        }
        col_Start += 1;

        for (int i = col_Start; i < col_End; i++) {
            printf("%d ", matrix[i][row_End]);
        }
        row_Start -= 1;

        if (row_End < row_Start) {
            for (int i = row_End + 1; i <= row_Start; i++) {
                printf("%d ", matrix[col_End - 1][i]);
            }
            col_End -= 1;
        }

        if (col_Start < col_End) {
            for (int i = col_End - 1; i >= col_Start; i--) {
                printf("%d ", matrix[i][row_Start]);
            }
            row_End += 1;
        }  
    }
    return 0;
}