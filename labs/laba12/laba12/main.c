#include <stdio.h>
#include <stdlib.h>

#include "lab12_var18.h"

int main() {
  int n;
  if (scanf("%d", &n) == 1) {
    printf("you entered %d\n", n);
  } else {
    printf("something wrong with your input\n");
  }

  printf("%d\n", change_2nd_and_prelast(n));
}