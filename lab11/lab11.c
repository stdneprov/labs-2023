// Подсчитать количество положительных десятичных чисел в строке, допустимых 16-битными процессорами.
#include <stdio.h>
#include <stdbool.h>

#define MAX 65536

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsDigit(char c) {
    return (c >= '0' && c <= '9');
}

int main() {
    long long numCounter = 0;
    long long buffer = 0;
    bool isWordStarted = 0;
    bool isNum = 1;
    int goodNumCount = 0;
    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isNum = isNum && IsDigit(c);
            isWordStarted = 1;

            if (IsDigit(c)) {
                buffer = buffer * 10 + (c - '0');
            }
        } else {
            if (isWordStarted && isNum) {
                numCounter++;
                
                if ((numCounter == 1) || (buffer < MAX)) {
                    goodNumCount++;
                }
            }
            buffer = 0;
            isWordStarted = 0;
            isNum = 1;
        }
        if (c == '\n') {
            if (numCounter > 0) {
                printf("%d\n", goodNumCount);
            }
            else {
                printf("NO");
            }
            goodNumCount = 0;
        } else if (c == EOF) {
            break;
        }
    }
    return 0;
}
