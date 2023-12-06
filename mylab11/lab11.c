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
    int StartofInch = 0;
    int isWasIn = 0;
    int isWasI = 0;
    int isWasIni = 0;
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

            isWordIsMeasure = isWordIsNumber & StartofInch && c == 'n' && OnlyOnce;
            if (isWodStarted && !isWordIsMeasure && isWordIsNumber && ((!OnlyOnce && c == 'i') || (OnlyOnce && StartofInch && c != 'n'))) {
                if (sign == -1 && buffer == 0 && !isWasDigits) {
                    printf("-");
                } else if (sign == -1) {
                printf("-%lld", buffer);
                } else {
                    printf("%lld", buffer);
                }

                if (isWasIn) {
                    printf("in");
                } else if (isWasI) {
                    printf("i");
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
                        StartofInch = 0;
                        isWordIsMeasure = 0;
                        buffer = 0;
                        sign = 1;
                        isWasIn = 0;
                        isWasI = 0;
                        OnlyOnce = 1;
                        isWasIni = 0;
                        break;
                    }

                }

                continue;
            }

            isWasIn = ((StartofInch && c == 'n') || isWasIn) && !isWasIni;
            StartofInch = (c == 'i');
            isWasI = (StartofInch || isWasI) && !isWasIn;
            isWasIni = (isWasIn && c == 'i') || isWasIni;
            isWordIsNumber = (isWordIsNumber && (IsDigit(c) || (c == '-' && !isWodStarted))) || isWordIsMeasure || StartofInch;
            if (c == '-' && !isWodStarted) {
                sign = -1;
            }

            if (!isWodStarted && c == 'i') {
                putchar(c);
                while (1) {
                    int c = getchar();
                    if (!IsSeparator(c)) {
                        putchar(c);
                    } else {
                        putchar(c);
                        isWasMinusFirst = 0;
                        isWodStarted = 0;
                        StartofInch = 0;
                        isWordIsNumber = 1;
                        isWasDigits = 0;
                        isWordIsMeasure = 0;
                        buffer = 0;
                        sign = 1;
                        isWasIn = 0;
                        isWasI = 0;
                        OnlyOnce = 1;
                        isWasIni = 0;
                        break;
                    }
                }
                continue;
            }

            isWodStarted = 1;
            if (IsDigit(c)) {
                buffer = buffer * 10 + (c - '0');
            }

            if (!isWordIsNumber && isWodStarted && isWasDigits) {
                if (sign == -1) {
                    printf("-");
                }
                printf("%lld", buffer);
                if (isWasIni) {
                    printf("ini");
                } else if (isWasIn) {
                    printf("in");
                } else if (isWasIni) {
                    printf("i");
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
                        StartofInch = 0;
                        isWordIsNumber = 1;
                        isWasDigits = 0;
                        isWordIsMeasure = 0;
                        buffer = 0;
                        sign = 1;
                        isWasIn = 0;
                        isWasI = 0;
                        OnlyOnce = 1;
                        isWasIni = 0;
                        break;
                    }
                }
            } else {
                if (!isWordIsNumber && !isWasDigits) {
                    if (isWasMinusFirst) {
                        printf("-");
                    }
                    
                    if (isWasIni) {
                        printf("ini");
                    } else if (isWasIn) {
                        printf("in");
                    } else if (isWasI) {
                        printf("i");
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
                            StartofInch = 0;
                            isWordIsNumber = 1;
                            isWasDigits = 0;
                            isWordIsMeasure = 0;
                            buffer = 0;
                            sign = 1;
                            isWasIn = 0;
                            isWasI = 0;
                            OnlyOnce = 1;
                            isWasIni = 0;
                            break;
                        }

                    }

                }

            }

        } else if (isWodStarted && isWordIsMeasure && isWasDigits && isWordIsNumber) {
            doubledBuffer = buffer * 25.4;
            if ((int)doubledBuffer == doubledBuffer) {
                printf("%dмм", (int)doubledBuffer * sign);
            } else {
                printf("%.1fмм", doubledBuffer * sign);
            }

            putchar(c);
            isWasMinusFirst = 0;
            isWodStarted = 0;
            StartofInch = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            isWasIn = 0;
            isWasI = 0;
            OnlyOnce = 1;
            isWasIni = 0;
        } else if (isWodStarted && !isWordIsMeasure && isWordIsNumber && !StartofInch) {
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
            StartofInch = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            isWasIn = 0;
            isWasI = 0;
            OnlyOnce = 1;
            isWasIni = 0;
        } else if (isWodStarted && !isWasDigits && isWordIsNumber) {
            if (sign == -1) {
                printf("-");
            }

            if (isWasIni) {
                printf("ini");
            } else if (isWasIn) {
                printf("in");
            } else if (isWasI) {
                printf("i");
            }

            putchar(c);
            isWasMinusFirst = 0;
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            StartofInch = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            isWasIn = 0;
            isWasI = 0;
            OnlyOnce = 1;
            isWasIni = 0;
        } else if (isWodStarted && !isWordIsMeasure && isWordIsNumber && StartofInch) {
            if (sign == -1) {
                printf("-");
            }

            printf("%lld", buffer);
            if (isWasIni) {
                printf("ini");
            } else if (isWasI) {
                printf("i");
            }

            putchar(c);
            isWasMinusFirst = 0;
            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            StartofInch = 0;
            isWordIsMeasure = 0;
            buffer = 0;
            sign = 1;
            isWasIn = 0;
            isWasI = 0;
            OnlyOnce = 1;
            isWasIni = 0;
        } else if (c != EOF) {
            putchar(c);
        }

        if (c == EOF) {
            break;
        }
    }

    return 0;
}
