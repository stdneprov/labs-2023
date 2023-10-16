#include <stdio.h>
#include <math.h>


int sgn(int val)
{
   return (val > 0) ? (1) : ((val < 0) ? (-1) : (0));
}

int main() {
    int i = -11, j = -6, l = -5;
    int k;

    for (k = 0; k < 50; k++) {
        int new_i = (i + j + l) * (k + l) % 25 - i * j * l * (k + 2) % 10 + 10;
        int new_j = fmin((i + j + l) * (k + 3) % 25, i * j * l * (k + 4) % 25) + 10;
        int new_l = 2 * sgn(l) * abs((i + j + l) * (k + 5) % 10 - i * j * l * (k + 6) % 25);
        
        i = new_i;
        j = new_j;
        l = new_l;

        if (i >= 5 && i <= 15 && j >= -15 && j <= -5) {
            printf("Попадание на шаге %d. Время: %d, Координаты: (%d, %d), l: %d\n", k, k + 1, i, j, l);
            break;
        }
    }

    if (k == 50) {
        printf("Промах. Время окончания: %d, Координаты: (%d, %d), l: %d\n", k, i, j, l);
    }

    return 0;
}
