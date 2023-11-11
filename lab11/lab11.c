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
    long long buffer = 0;
    int sign = 1;

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
            }
        } else {
            if (isWordStarted && isWasDigit && isWordIsNumber && sign == 1) {
                printf("0%lld\n", buffer);
            } else if(isWordStarted && isWasDigit && isWordIsNumber && sign == -1) {
                printf("-0%lld\n", buffer);
            }
            isWasDigit = 0;
            isWordIsNumber = 1;
            isWordStarted = 0;
            buffer = 0;
            sign = 1;
        }


        if (c == EOF) {
            break;;
        }
    }

}