#include <stdio.h>


int main() {
  int n;
  printf("Enter matrix size: ");
  scanf("%d", &n);
  printf("\n");
  int mx[n][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &mx[i][j]);
    }
  }
  printf("\n");
  for (int i = 0; i < n; ++i) {
    int s = n - 1;
    int c = n - 1 - i;
    while (c >= 0) {
      printf("%d ", mx[s][c]);
      s--;
      c--;
    }
    s++;
    c++;
    c = s + 1;
    s = 0;
    while (c < n) {
      printf("%d ", mx[s][c]);
      s++;
      c++;
    }
  }
  return 0;
}