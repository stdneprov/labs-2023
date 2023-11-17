#include <stdio.h>
#include <stdlib.h>

void PrintTrinaryR(int a) {
    if (a > 0) {
        PrintTrinaryR(a / 3);
        putchar((a % 3) + '0');
    }
}

void PrintTrinary(int a) {
    if (a < 0) {
        putchar('-');
        a *= -1;
    }

    if (a == 0) {
        putchar('0');
    }

    PrintTrinaryR(a);
}

int IsSeparator(char c) {
    return(c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsDigit(char c) {
    return c >= '0' && c <= '2';
}

int main() {
    int isWordStarted = 0;
    int isWordNumber = 1;
    int isWasDigits = 0;
    long long buffer = 0;
    int sign = 1;
    while(1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isWasDigits = isWasDigits || isDigit(c);
            isWordNumber = isWordNumber && (isDigit(c) || (!isWordStarted && c == '-'));
            isWordStarted = 1;

            if (c == '-') {
                sign = -1;
            }

            if (IsDigit(c)) {
                buffer = buffer * 3 + (c - '0');
            }
        } else {
            if (isWordStarted && isWordNumber && isWasDigits) {
                if (buffer % 3 == 0) { 
                    PrintTrinary(buffer * sign);

                }


            }

            isWordStarted = 0;
            isWordNumber = 1;
            isWasDigits = 0;
            buffer = 0;
            sign = 1;


        }
    }

}