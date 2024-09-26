#include <stdbool.h>
#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

bool CheckIsCharValid(int s) {
    return (s >= '0' && s <= '9') || (s >= 'a' && s <= 'f') ||
           (s >= 'A' && s <= 'F');
}

int GetValueOfChar(int s) {
    if (s >= '0' && s <= '9') {
        return s - '0';
    } else if (s >= 'a' && s <= 'z') {
        return 10 + (s - 'a');
    } else {
        return GetValueOfChar(s + ('a' - 'A'));
    }
}

int main() {
    bool goodNumber = 1;
    bool numStarted = 0;
    long long container = 0;
    long long currentNum = 0;
    long long previousNum = 0;
    long long counter = 0;
    int sign = 1;
    while (1) {
        int c = getchar();
        if (IsSeparator(c)) {
            if (goodNumber && numStarted) {
                previousNum = currentNum;
                currentNum = container * sign;
                counter += 1;
            };
            container = 0;
            goodNumber = 1;
            numStarted = 0;
            sign = 1;
        } else {
            if (CheckIsCharValid(c) || (c == '-' && (!numStarted))) {
                if (c == '-') {
                    sign = -1;
                    continue;
                }
                numStarted = 1;
                container = container * 16 + GetValueOfChar(c);
            } else {
                goodNumber = 0;
            }
        }
        if (c == EOF) {
            break;
        }
    }
    if (counter < 2) {
        printf("NO");
    } else {
        if (previousNum < 0) {
            printf("-%llx", -(previousNum));
        } else {
            printf("%llx", (previousNum));
        }
    }
}
