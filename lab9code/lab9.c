#include <stdio.h>

//Введение необходимых математических функций

int Abs(int a) {
    return a > 0 ? a : -a;
}

int Mod(int a, int b) {
    return (a % b + b) % b;
}

int Sign(int x) {
    return (x > 0) - (x < 0);
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    // Начальные данные
    int i = 22;
    int j = 10;
    int l = 10;

    // Итеративный цикл
    int k;
    for (k = 0; k < 51; k++) {
        // Обновление координат и параметра движения
        int newI = Min(Mod(l, 5), Mod(i * k, 5)) + j + k/3;
        int newJ = Max((-3) * i, 2 * j) / 5 - Abs(j - l);
        int newL = j + Mod(l, 7) + Mod(k * Sign(i), 10);

        // Проверка попадания в область
        if (i >= 5 && i <= 15 && j >= -15 && j <= -5) {
            printf("Yes %d\n", k);
            break;
        }

        // Обновление переменных для следующей итерации
        i = newI;
        j = newJ;
        l = newL;
    }

    if (k == 51) {
        // Если точка не достигла заданной области в течение 50 шагов
        printf("No %d\n", k);
    }

    return 0;
}

