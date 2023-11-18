#include <stdio.h>

int IsSeparator(char c){
    return (c == ' ') || (c == EOF) || (c == '\n') || (c == ', ') || (c == '\t');
}
int IsDigitForBCD(char c){
    return (c == '0') || (c == '1');
}

int main(){
    long long numberCounter = 0;
    int isNumberStarted = 0;
    int countDigitBeforeCurrentEl = 0;
    long long buffer = 0;
    int sepBefore = 1;
    while(1){
        int c = getchar();
        if ((IsDigitForBCD(c)) && (isNumberStarted == 0) && (sepBefore == 1)) {
            isNumberStarted = 1;
            countDigitBeforeCurrentEl += 1;
            buffer = buffer * 2 + (c - '0');
        } else if ((IsDigitForBCD(c) && (isNumberStarted == 1) && (countDigitBeforeCurrentEl < 4))) {
            countDigitBeforeCurrentEl += 1;
            buffer = buffer * 2 + (c - '0');
        } else if (countDigitBeforeCurrentEl == 4) {
            if (IsDigitForBCD(c) && (buffer <= 9)) {
                countDigitBeforeCurrentEl = 0;
                countDigitBeforeCurrentEl += 1;
                buffer = 0;
                buffer = buffer * 2 + (c - '0');
            } else if (IsSeparator(c) && (buffer <= 9)) {
                countDigitBeforeCurrentEl = 0;
                isNumberStarted = 0;
                buffer = 0;
                numberCounter += 1;
            } else {
                countDigitBeforeCurrentEl = 0;
                isNumberStarted = 0;
                buffer = 0;
            }
        } else {
            countDigitBeforeCurrentEl = 0;
            isNumberStarted = 0;
            buffer = 0;
        }
        sepBefore = IsSeparator(c);
        if (c == EOF) {
            break;
        }
        }
    if (numberCounter > 0) {
        printf("%lld\n", numberCounter);
    } else {
        printf("not found\n");
    }
    
    return 0;
}