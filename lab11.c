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
    int prevChar = '0';
    int prevPrevChar = '0';
    int wasCelsius = 0;
    int prevIWIN = 0;
    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isWasDigits = isWasDigits || IsDigit(c);
            isWordIsNumber = isWordIsNumber && (IsDigit(c) || (!isWodStarted && c == '-') || (isWodStarted && IsDigit(prevChar) && c == 'C'));
            wasCelsius = IsDigit(prevPrevChar) && IsDigit(prevChar) && c == 'C';
            isWodStarted = 1;
            if (c == '-') {
                sign = -1;
            }

            if (IsDigit(c)) {
                buffer = buffer * 10 + (c - '0');
            }
            if (!isWordIsNumber){
                if (prevIWIN) {
                    printf("%lld", buffer * sign);
                    if (c == 'C') printf("CC");
                }
                else putchar(c);
            }
            prevIWIN = isWordIsNumber;
            prevPrevChar = prevChar;
            prevChar = c;
        } else {
            if (isWodStarted && isWordIsNumber && isWasDigits && IsDigit(prevPrevChar) && prevChar == 'C') {
                lastNum = buffer * sign;
                printf("%.2fF", (float)lastNum * 9 / 5 + 32);
                prevChar = '0';
                prevPrevChar = '0';
                wordCounter += 1;
                
            } else if (isWodStarted && isWordIsNumber && isWasDigits) {
                printf("%lld", buffer * sign);
                // wasCelsius = 0;
            }
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            wasCelsius = 0;
            buffer = 0;
            prevIWIN = 0;
            sign = 1;
            if (c != EOF) putchar(c);
        }

        if (c == EOF) {
            break;
        }
    
    }

    return 0;
}