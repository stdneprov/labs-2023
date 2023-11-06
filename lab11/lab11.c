#include <stdbool.h>
#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int main() {
    bool goodNumber = 1;
    bool numStarted = 0;
    long long container = 0;
    long long currentNum = -1;
    long long previousNum = -1;
    int sign = 1;
    while (1) {
        int c = getchar();
        if (IsSeparator(c)) {
            if (goodNumber) {
                previousNum = currentNum;
                currentNum = container * sign;
            };
            container = 0;
            goodNumber = 1;
            numStarted = 0;
            sign = 1;
        } else {
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
                (c >= 'A' && c <= 'F') || (c == '-' && (!numStarted))) {
                numStarted = 1;
                if (c == '-') {
                    sign = -1;
                } else if (c >= 'a' && c <= 'f') {
                    container = container * 16 + (10 + (c - 'a'));
                } else if (c >= 'A' && c <= 'F') {
                    container = container * 16 + (10 + (c - 'A'));
                } else {
                    container = container * 16 + (c - '0');
                }
            } else {
                goodNumber = 0;
            }
        }
        if (c == EOF) {
            break;
        }
    }
    if (previousNum == -1) {
        printf("NO");
    } else {
        if (previousNum < 0) {
            printf("-%x", abs(previousNum));
        } else {
            printf("%x", abs(previousNum));
        }
    }
}
