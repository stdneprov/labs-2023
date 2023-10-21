#include <stdio.h>
#include <stdlib.h>
// Я умею комментить:)
/*
И так тоже могу
*/
int Sign(int x) {
    if (x < 0) {
        return -1;
    } else if (x > 0) {
        return 1;
    } else {
        return 0;
    }
}
//int Min(int x, int y) {
//    if (x > y) {
//        return y;
//    } else {
//        return x;
//    }
//}
//int Max(int x, int y) {
//    if (x > y) {
//        return x;
//    }
//    return y;
//}
int Max(int a, int b) {
    int m;
    m = (a > b) ? a : b;
    return m;
}

int Min(int a, int b) {
    int m;
    m = (a < b) ? a : b;
    return m;
}

int Mod(int a, int b) {
  int m = a % b;
  if (m < 0) {
    m = (b < 0) ? m - b : m + b;
  }
  return m;
}
int main() {
    int i0 = -8, j0 = -5, l0 = 12;
    int i = -8, j = -5, l = 12;
    int d = 0;
    for (int k = 1; k <= 50; k++) {
        i = Mod(((i0 * i0 / (abs(j0 - l0) + k + 1)) - (j0 * j0 / (abs(i0 - l0) + k + 1))), 30);
//        i = (((i0 * i0 / (abs(j0 - l0) + k + 1)) - (j0 * j0 / (abs(i0 - l0) + k + 1))) % 30);
        j = Sign(l0) * Min(i0, j0) - Sign(j0) * Max(i0,l0) + k;
        l = Mod(((i0 - j0) * (j0 - l0) * (l0 - i0)), 20);
//        l = (((i0 - j0) * (j0 - l0) * (l0 - i0)) % 20);
        l0 = l;
        i0 = i;
        j0 = j;
        if ((i0 > (-10)) && (i0 < 0) && (j0 > i0 + 10) && (j0 < 10 - i0)) {
            printf("YES %d \n", k);
            d = 1;
            break;
        }
    }
    if (d == 0) {
        printf("NO\n");
    }
    printf("Конечная точка: %d %d \n", i0, j0);
    printf("Конечное значение динамического параметра: %d \n", l0);
    return 0;
}
