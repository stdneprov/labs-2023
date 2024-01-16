#include <stdio.h>

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int Abs(int a) {
    return a > 0 ? a : -a; //возвращает модуль a
}

int Sign(int a) {
    return a > 0 ? 1 : -1; //возвращает знак a
}

int Mod(int a, int b) {
    int mod;
    return mod = ((a % b) + b) % b; //возвращает остаток от деления (a, b)
}

int main() {
    int i = 24;
    int j = -14;
    int l = 9; //динамический параметр
    int flag = 0; //проверка выполнения условия
    
    for (int k = 1; k < 51; k++) {
        int i1 = Mod((i + k) * (j - k) * (l + k), 25);
        int j1 = Mod(Min((j + k), Max((j - k), (l - k))), 30);
        int l1 = Abs(j - l) * Sign(i) - Abs(i - l) * Sign(j);

        i = i1;
        j = j1;
        l = l1;

        if ((i >= 5 && i <= 15) && (j >= -15 && j <= -5)){
            printf("YES %d", k);
            flag = 1;
            break;
        }

    }

    if (flag == 0) { 
        printf("NO\n");
    }

    return 0;
}