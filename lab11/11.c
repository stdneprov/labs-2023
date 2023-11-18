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
    else{
    return 8;
    }
}

int main() {
    long long wordCounter = 0;
    int isWordStarted = 0;
    int isWordIsRome = 1;
    int doblicateCounter = 0;
    int d = 0;
    int isFlag = 0;
    while (1) {
        int c = getchar();
        if (IsSeparator(c)){
            if (isFlag){
                wordCounter += 1;
                isFlag = 0;
            }
        }
       if (!IsSeparator(c)){
            isWordStarted = 1;
            isWordIsRome = isWordIsRome && IsRome(d);
            }

        if (isWordStarted) {
            if (isWordIsRome){
                if ((firstC(d) > firstC(c)) && (doblicateCounter <= 3)){
                    isFlag = 1;
                    doblicateCounter = 0;
                }
                else if (doblicateCounter > 3){
                    doblicateCounter = 0;
                    isFlag = 0;
                    isWordStarted = 0; 
                }
                else if (firstC(c) == firstC(d)){
                    if (firstC(c) == 2){
                        doblicateCounter = 0;
                        isFlag = 0;
                        isWordStarted = 0;
                    }
                    else{
                        doblicateCounter += 1;
                    }
                }
                else{
                    doblicateCounter = 0;
                    isFlag = 0;
                    isWordStarted = 0;
                }
            }
            isWordStarted = 0;
            isWordIsRome = 1;
        }

        if (c == EOF) {
            break;
        }
        d = c;
    }
    printf("%lld\n", wordCounter);
    return 0;
}
