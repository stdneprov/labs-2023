// Удалить все чётные цифры из числа
#include <stdio.h>
#include <stdbool.h>

#define ll long long int

bool IsSeparator(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.' ||
           c == EOF;
}

ll WithoutDivisableByTwo(ll num) {
    ll res = 0;
    int sign = num > 0 ? 1 : -1;
    num *= sign;
    ll digit = 1;
    for (; num > 0; num /= 10) {
        if (num % 2 != 0) {
            res += (num % 10) * digit;
            digit *= 10;
        }
    }
    return res * sign;
}

int main(void) {
    ll num = 0;
    int res;
    while ((res = scanf("%lld", &num)) != EOF) {
        if (res == 1) {
            printf("%lld\n", WithoutDivisableByTwo(num));
        } else {
            while (!IsSeparator(getchar())) continue;
        }
    }
    return 0;
}
