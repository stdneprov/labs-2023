
#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsDigit(char c) {
    return c >= '0' && c <= '9';
}

int main() {
    int isWodStarted = 0;
    int isWordIsNumber = 1;
    int isWasDigits = 0;
    int isWordIsMeasure = 0;
    int isWasMinusFirst = 0;
    int isWasC = 0;
    int OnlyOnce = 1;
    long long buffer = 0;
    int sign = 1;
    double doubledBuffer = 0;
    while (1) {
        int c = getchar();       
        if (!IsSeparator(c)) {
            isWasMinusFirst = isWasMinusFirst || (c == '-');
            isWasDigits = isWasDigits || IsDigit(c);
            if (isWordIsMeasure) {
                OnlyOnce = 0;
            }

            isWordIsMeasure = isWordIsNumber && (c == 'C') && OnlyOnce;
            isWasC = (c == 'C') || isWasC;
            isWordIsNumber = (isWordIsNumber && ((IsDigit(c) && !isWasC) || (c == '-' && !isWodStarted))) || isWordIsMeasure;
            if (c == '-' && !isWodStarted) {
                sign = -1;
            }
            isWodStarted = 1;
            if (IsDigit(c) && !isWasC) {
                buffer = buffer * 10 + (c - '0');
            }

            if (!isWordIsNumber && isWodStarted && isWasDigits && !isWordIsMeasure) {
                if (sign == -1) {
                    printf("-");
                }
                printf("%lld", buffer);
                if (isWasC) {
                    printf("C");
                }
                putchar(c);
                while (1) {
                    int c = getchar();
                    if (!IsSeparator(c)) {
                        putchar(c);
                    } else {
                        putchar(c);
                        isWasMinusFirst = 0;
                        isWodStarted = 0;
                        isWordIsNumber = 1;
                        isWasDigits = 0;
                        isWordIsMeasure = 0;
                        buffer = 0;
                        sign = 1;
                        OnlyOnce = 1;
                        isWasC = 0;
                        break;
                    }
                }
            } else {
                if (!isWordIsNumber && !isWasDigits) {
                    if (isWasMinusFirst) {
                        printf("-");
                    }
                    
                    if (isWasC) {
                        printf("C");
                    }

                    putchar(c);
                    while (1) {
                        int c = getchar();
                        if (!IsSeparator(c)) {
                            putchar(c);
                        } else {
                            putchar(c);
                            isWasMinusFirst = 0;
                            isWodStarted = 0;
                            isWordIsNumber = 1;
                            isWasDigits = 0;
                            isWordIsMeasure = 0;
                            buffer = 0;
                            sign = 1;
                            OnlyOnce = 1;
                            isWasC = 0;
                            break;
                        }

                    }

                }

            }

        } else if (isWodStarted && isWordIsMeasure && isWasDigits && isWordIsNumber) {
            doubledBuffer = buffer;
            if ((int)doubledBuffer == doubledBuffer) {
                printf("%dF", (((int)doubledBuffer * sign) / 5) * 9 + 32);
            } else {
                printf("%.2fF", ((doubledBuffer * sign) / 5) * 9 + 32);
            }

            putchar(c);
            isWasMinusFirst = 0;
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            OnlyOnce = 1;
            isWasC = 0;
        } else if (isWodStarted && !isWordIsMeasure && isWordIsNumber) {
            if (sign == -1 && buffer == 0 && !isWasDigits) {
                printf("-");
            } else if (sign == -1) {
                printf("-%lld", buffer);
            } else {
                printf("%lld", buffer);
            }

            putchar(c);
            isWasMinusFirst = 0;
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            OnlyOnce = 1;
            isWasC = 0;
        } else if (isWodStarted && !isWasDigits && isWordIsNumber) {
            if (sign == -1) {
                printf("-");
            }

            if (isWasC) {
                printf("C");
            }

            putchar(c);
            isWasMinusFirst = 0;
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            OnlyOnce = 1;
            isWasC = 0;
        } else if (c != EOF) {
            putchar(c);
        }

        if (c == EOF) {
            break;
        }
    }

    return 0;
}