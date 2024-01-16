#include <stdio.h>
#define MAX_N 7
int main() {

    int matrix[MAX_N][MAX_N];
    int n;
    scanf("%d", &n);
    int x, y; //координаты элементов массива, по которым будем двигаться

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j ++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    if (n % 2 == 0) { //при четном n (кол-ве столбцов в матрице)
        for (int column = n - 1; column > -1; column--) {
        if (column % 2 != 0) { //нечетная колонна
            x = n - 1 - column; 
            y = n - 1; 
            while (x > -1) {
                printf("%d ", matrix[x][y]);
                x--;
                y--;
            }
        } else {
            x = 0;
            y = column;
            while (y < n) {
                printf("%d ", matrix[x][y]);
                x++;
                y++;
            }
        }
        }
        } else { //при нечетном n
        for (int column = n - 1; column > -1; column--) { //нечетная колонна
        if (column % 2 == 0) {
            x = n - 1 - column; 
            y = n - 1; 
            while (x > -1) {
                printf("%d ", matrix[x][y]);
                x--;
                y--;
            }
        } else {
            x = 0;
            y = column;
            while (y < n) {
                printf("%d ", matrix[x][y]);
                x++;
                y++;
            }
        }
        }
    }
        for (int column = n - 2; column > -1; column--) {
            if (column % 2 == 0) { //четная колонна
                x = n - 1;
                y = column;
                while (y > -1) {
                    printf("%d ", matrix[x][y]);
                    x--;
                    y--;
                }
            } else {
                x = n - 1 - column;
                y = 0;
                while(x < n) {
                    printf("%d ", matrix[x][y]);
                    x++;
                    y++;
                }
            }

        }
    
}
