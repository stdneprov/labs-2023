#include <stdio.h>
#include <stdbool.h>


long long Abs(long long x) {
    if(x < 0) {
        return -x;
    }
    return x;
}

long long Length(long long n) {
    long long r = 0;
    while(n > 0) {
        r++;
        n /= 10;
    }
    return r - 1;
}

long long Iter(long long x) {
    long long res = 1;
    while(x >= 1) {
        res *= 10;
        x -= 1;
    }
    return res;
}

long long Res(long long number) {
    number = Abs(number);
    long long discharge = Length(number);
    long long iterator = Iter(discharge);
    long long res = 0;
    while(discharge > 0) {
        if(discharge % 2 != 0) {
            res *= 10;
            res += (number / iterator) % 10;
        }   
        discharge--;
        iterator /= 10;
    }
    return res;
}

int main(void) {
    long long number;
    int sign = 1;

    while(scanf("%lld", &number)) {
        if(number < 0) {
            sign = -1;
        }
        if(Res(number) != 0) {
            long long result = sign * Res(number);
            printf("%lld", result);
        }
    }
    return 0;
}