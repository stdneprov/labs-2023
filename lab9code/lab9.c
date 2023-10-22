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
    int steps = 0;
    for (k = 0; k < 51; k++) {
        // Обновление координат и параметра движения
        int new_i = Min(Mod(l, 5), Mod(i * k, 5)) + j + k/3;
        int new_j = Max((-3) * i, 2 * j) / 5 - Abs(j - l);
        int new_l = j + Mod(l, 7) + Mod(k * Sign(i), 10);

        // Проверка попадания в область
        if (i >= 5 && i <= 15 && j >= -15 && j <= -5) {
            printf("Yes, step: %d\n", k);
            break;
        }

        // Обновление переменных для следующей итерации
        i = new_i;
        j = new_j;
        l = new_l;

        steps = k; // Запоминаем номер шага для вывода времени попадания
    }

    if (k == 51) {
        // Если точка не достигла заданной области в течение 50 шагов
        printf("No\n");
    }

    // Вывод итоговых координат и параметра движения
    printf("Final coordinates: (i, j) = (%d, %d), l = %d\n", i, j, l);
    printf("Movement end time: %d\n", steps);

    return 0;
}

