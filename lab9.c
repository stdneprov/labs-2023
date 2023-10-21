#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int mod(int a, int b){
    return (a % b + b) % b;
}
int main() {
    int i = 6, j = 27, l = -15;
    for (int k = 0; k < 51; ++k){
        int newI = mod((pow(i, 3) - pow(j, 3) + pow(l, 3) - k), 20);
        int newJ = mod(fmin(fmin(i * j * j - k, i * i * l - k), j * l * l - k), 30);
        int newL = mod(fmax(fmin(i * j * j - k, i * i * l - k), j * l * l - k), 30);
        i = newI;
        j = newJ;
        l = newL;
        if (((pow(i + 10, 2) + pow(j + 10, 2)) <= 100) && ((pow(i + 20, 2) + pow(j + 20, 2)) <= 100)){
            printf("Шаг: %d, Время: %d, Координаты: (%d, %d), l: %d\n", k, k + 1, i, j, l);   
            break;         
        }
        else if (k == 50){
            printf("Промах!");
        }
    }
    return 0;
}
