#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF);
}

int IsDigit(char c) {
    return c >= '0' && c <= '9';
}

int main() {
    long long wordCounter = 0;
    int isWodStarted = 0;
    int isWordIsNumber = 1;
    int isWasDigits = 0;
    long long buffer = 0;
    long long lastNum = 0;
    int sign = 1;
    int prevChar = 0;
    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isWasDigits = isWasDigits || IsDigit(c);
            isWordIsNumber = isWordIsNumber && (IsDigit(c) || (!isWodStarted && c == '-') || (isWodStarted && c == 'C'));
            isWodStarted = 1;

            if (c == '-') {
                sign = -1;
            }

            if (IsDigit(c)) {
                buffer = buffer * 10 + (c - '0');
            }
            prevChar = c;
        } else {
            if (isWodStarted && isWordIsNumber && isWasDigits && prevChar == 'C') {
                lastNum = buffer * sign;
                printf("%.2fF\n", (float)lastNum * 9 / 5 + 32);
                wordCounter += 1;
            }
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            buffer = 0;
            sign = 1;

        }

        if (c == EOF) {
            break;
        }
    }

    if (wordCounter < 1) {
        printf("NO\n");
        return 0;
        
    }
    return 0;
}