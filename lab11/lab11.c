#include <stdio.h>
#include <stdbool.h>

int IsSeparated(char c) {
    return (c == ' ' || c == ',' || c == '\n' || c == EOF || c == '\t');
}

int IsDigit(char c){
    return (c >= '0' && c <= '9');
}

int main() {
    bool isWasDigit = 0;
    bool isWordStarted = 0;
    bool isWordIsNumber = 1;
    bool leaderNul = 1;
    long long buffer = 0;
    int sign = 1;
    int countNul = 0;

    while (1) {
        int c = getchar();

        if (!IsSeparated(c)) {
            isWasDigit = isWasDigit || IsDigit(c);
            isWordIsNumber = isWordIsNumber && ((IsDigit(c)) || (!isWordStarted && c == '-' ));
            isWordStarted = 1;

            if (c == '-') {
                sign = -1;
            }

            if (IsDigit(c)) {
                buffer = buffer * 10 + (c - '0');
                if (c != '0') {
                    leaderNul = 0;
                }
                if (leaderNul) {
                    countNul += 1;
                }
            }
        } else {
            if (isWordStarted && isWasDigit && isWordIsNumber && sign == 1) {
                if (buffer == 0) {
                    countNul -= 1;
                }
                for (int i = 0; i < countNul; i++) {
                    putchar('0');
                }
                printf("0%lld\n", buffer);
            } else if(isWordStarted && isWasDigit && isWordIsNumber && sign == -1) {
                if (buffer == 0) {
                    countNul -= 1;
                }
                putchar('-');
                for (int i = 0; i < countNul; i++) {
                    putchar('0');
                }
                printf("0%lld\n", buffer);
            }
            isWasDigit = 0;
            isWordIsNumber = 1;
            isWordStarted = 0;
            buffer = 0;
            sign = 1;
            leaderNul = 1;
            countNul = 0;
        }


        if (c == EOF) {
            break;;
        }
    }

}