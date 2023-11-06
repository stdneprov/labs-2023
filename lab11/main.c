#include <stdio.h>
#include <stdlib.h>


int isSep(int c) {
    return (c == ' ' || c == ',' || c == '\t' || c == EOF || c == '\n');
}


int isOctDig(int c) {
    return ('0' <= c && c <= '7');
}


int main() {
    int isOctNum = 1;
    long long curNum = 0;
    long long counter = 0;

    while (1) {
        int c = getchar();

        if (isSep(c)) {

            if (0010 <= curNum && isOctNum) {
                counter += 1;
                curNum = 0;
            }
            isOctNum = 1;
            
            if (c == EOF) {
                break;
            }

        } else if (!isOctDig(c) && isOctNum) {
            isOctNum = 0;
            curNum = 0;

        } else if (isOctNum) {
            curNum *= 8;
            curNum += c - '0';

            if (curNum > 001000) {
                isOctNum = 0;
                curNum = 0;
            }
        }
    }

    printf("%lli\n", counter);
    
    return 0;
}