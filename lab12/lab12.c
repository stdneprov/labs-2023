// Удалить все чётные цифры из числа
#include <stdio.h>
#include <stdbool.h>

#define ll long long int

bool isSeparator(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.' ||
           c == EOF;
}

void PrintRec(ll num) {
    if (num != 0) {
        PrintRec(num / 10);
        if (num % 2 != 0)
            printf("%lld", num % 10);
    }
}

void Print(ll num) {
    if (num == 0) {
        printf("0\n");
        return;
    }
    if (num < 0) {
        printf("-");
        num *= -1;
    }
    PrintRec(num);
    printf("\n");
}

int main(void) {
    ll num = 0;
    int res;
    while ((res = scanf("%lld", &num)) != EOF) {
        if (res == 1) {
            Print(num);
        } else {
            while (!isSeparator(getchar())) continue;
        }
    }
    return 0;
}
