#include <stdio.h>
#include <stdbool.h>

int IsSeparator(char c) {
    return (c != '1') && (c != '2') && (c != '3') && (c != '4') && (c != '5') && (c != '6') && (c != '7') && (c != '8') && (c != '9') && (c != '0');
}

int main() {
    long long positiveNumberCounter = 0;
    bool isNumberStarted = 0;
    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isNumberStarted = 1;
        } else if (isNumberStarted) {
            positiveNumberCounterCounter += 1;
            isNumberStarted = 0;
        }

        if (c == EOF) {
            break;
        }
    }

    printf("%lld\n", positiveNumberCounter);

    return 0;
}