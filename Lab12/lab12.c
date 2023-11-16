#include <stdio.h>
#include <stdbool.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsOkay(long long r) {
    long long x;
    x = r;
    while (x > 0) {
        if (x % 10 == (x % 100) / 10) {
            return 0;
            printf("%d", x % 10);
        }
        if (x / 10 == 0) {
            return 1;
        }
        x = x / 10;
    }
}

int Abs(long long r) {
    if (r < 0) {
        return -r;
    }
    return r;
}

int main() {
    while(1) {
        long long a;
        scanf("%lld", &a);
        if (IsOkay(Abs(a))) {
            printf("%lld ", a);
        }
        int c = getchar();
        if (c == EOF) {
            break;
        }
    }

    return 0;
}