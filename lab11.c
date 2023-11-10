#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsDigit(char c) {
    return (('0' <= c) && (c <= '9'));
}

int main() {
    long long summa1 = 0;
    long long summa2 = 0;
    long long summa = 0;
    int numberStarted = 0;
    int sepBefore = 1;
    int sepOrMinusBefore = 1;
    while (1) {
        int c = getchar();
        if (IsDigit(c) && (sepOrMinusBefore || numberStarted)) {
            numberStarted = 1;
            summa = summa + c - '0';
        } else if (IsSeparator(c) && numberStarted) {
            numberStarted = 0;
            summa2 = summa1;
            summa1 = summa;
        } else if (!IsDigit(c)) {
            numberStarted = 0;
            summa = 0;
        }
        sepOrMinusBefore = (IsSeparator(c) || (c == '-' && sepBefore));
        sepBefore = IsSeparator(c);
        if (c == EOF) {
            break;
        }
    }
    printf("%lld\n", summa2);
    return 0;
} 