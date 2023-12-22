#include <stdio.h>

int main() {
  while(1){
    printf("Введите порядок матрицы или 0, чтобы остановить программу:\n");
    printf("\n");
    int n;
    scanf("%d", &n);
    if (n == 0){
      break;
    }
    printf("\n");
    int m[n][n];
    printf("Введите матрицу:\n");
    printf("\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &m[i][j]);
        }
    }
    printf("\n");
    printf("Исходная матрица:\n");
    printf("\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Вывод матрицы:\n");
    printf("\n");

    int a, b, flag, i, j;
    a = n - 1;
    b = 0;
    flag = 1;
    while ((a >= 0) && (b <= n - 1)){
      if (flag == 1){
        i = a;
        j = 0;
        while ((i >= 0) && (j <= a)){
          printf("%d ", m[i][j]);
          i -= 1;
          j += 1;
        }
        a = a - 1;
        b = b + 1;
        flag = 0;
      }
      else{
        i = b;
        j = n - 1;
        while ((i <= n - 1) && (j >= b)){
          printf("%d ", m[i][j]);
          i += 1;
          j -= 1;
        }
        flag = 1;
      }
    }
    printf("\n\n");
  }
}