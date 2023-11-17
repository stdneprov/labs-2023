#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsRome(char c){
    return (c == 'I') || (c == 'V') || (c == 'X') || (c == 'L') || (c == 'C') || (c == 'D') || (c == 'M');
}

int firstC(char c){
    if (c == 'I'){
        return 1;
    }
    else if (c == 'V'){
        return 2;
    }
    else if (c == 'X'){
        return 3;
    }
    else if (c == 'L'){
        return 4;
    }
    else if (c == 'C'){
        return 5;
    }
    else if (c == 'D'){
        return 6;
    }
    else if (c == 'M'){
        return 7;
    }
    return 8;

}

int main() {
    long long wordCounter = 0;
    int isWordStarted = 0;
    int isWordIsRome = 1;
    int doblicateCounter = 0;
    int d = 0;
    int isFlag = 1;
    while (1) {
        int c = getchar();
        if (IsSeparator(c)){
            doblicateCounter = 0;
            if (isFlag){
                wordCounter += 1;
            }
            else{
                isFlag = 1;
            }
        }
        if (!IsSeparator(c)) {
            isWordStarted = 1;
            isWordIsRome = isWordIsRome && IsRome(c);
        }
        if (isWordStarted) {
            if (isWordIsRome){
                if (!((firstC(c) < firstC(d)) && (doblicateCounter <= 3))){
                    isFlag = 0;
                    doblicateCounter = 0;
                }
                else if (firstC(c) == firstC(d)){
                    doblicateCounter = doblicateCounter + 1;
                }
                else{
                    doblicateCounter = 0;
                }
            }
            d = c;
            isFlag = 0;
            isWordStarted = 0;
            isWordIsRome = 1;
        }

        if (c == EOF) {
            break;
        }
    }
    printf("%lld\n", wordCounter - 1);
    return 0;
}
