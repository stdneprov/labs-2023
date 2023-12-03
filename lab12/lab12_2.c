#include <stdio.h>

int Reverse(int a) {
    int result = 0;
    int sign = a > 0 ? 1 : -1;
    a *= sign;
    while (a > 0) {
        result = result * 10 + a % 10;
        a /= 10;
    }
    return result * sign;
}   

int Sum(int a) {
    int result = 0;
    int flag = 0;
    while (a > 0) {
        result += a % 10;
        result += (a / 10) % 10;
        a /= 10;
        flag += 1;
        if (a == 0) {
            break;
        }
        if (result >= 0 && result <= 9) {
            printf("%d\n", result);
        }
        result = 0;
    }

    return result;
}

int main() {
    int a;
    while (scanf("%d", &a) != EOF) {
        Sum(a);
    }
}