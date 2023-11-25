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
    int sign = a > 0 ? 1 : -1;
    int flag = 0;
    a *= sign;
    a = Reverse(a);
    while (a > 0) {
        result += a % 10;
        a /= 10;
        flag += 1;
        if (flag == 2) {
            printf("%d\n", result);
            result = 0;
            flag = 0;
        }
    }

    return result;
}

int main() {
    int a;
    while (scanf("%d", &a) == 1) {
        Sum(a);
    }
}