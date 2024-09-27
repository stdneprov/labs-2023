#include <stdio.h>

int Length(long long n) {
    int l = 0;
    while (n != 0) {
        l++;
        n = n / 10;
    }
    return l;
}

long long Pow(long long n, int k) {
    long long r = 1;
    for (int i = 0; i < k; i++) {
        r = r * n;
    }
    return r;
}

long long delDigits(long long n) {
    int l = Length(n);
    int sign = n > 0 ? 1 : -1;
    if (l == 1) {
        return n;
    }
    else if (l == 2) {
        return 0;
    }
    else if (l == 3) {
        n = n * sign;
        n = n / 100 * 10 + n % 10;
        n = n * sign;
    }
    else {
        n = n * sign;
        n = n / Pow(10, l - 1) * Pow(10, l - 2) + n % Pow(10, l - 2);
        n = n / 100 * 10 + n % 10;
        n = n * sign;
    }
    return n;
}

int main(void) {
    long long num;
    while (scanf("%lld", &num) == 1) {
        printf("%lld\n", delDigits(num));
    }
    return 0;
}