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
    int sign = 1;
    long long max = 0;
    int flag = 0;
    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isWasDigits = isWasDigits || IsDigit(c);
            isWordIsNumber = isWordIsNumber && (IsDigit(c) || (!isWodStarted && c == '-'));
            isWodStarted = 1;

            if (c == '-') {
                sign = -1;
            }

            if (IsDigit(c)) {
                buffer += (c - '0');
                flag += 1;
                if (flag == 2) {
                    printf("%d\n", buffer);
                    flag = 0;
                    buffer = 0;
                }
            }
        } else {
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
}
