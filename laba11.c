#include <stdio.h>
#include <stdbool.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int Comprassion(char a, char b){
    if (a >= '0' && a <= '9' && b == 'A'){
        return 1;
    }
    else if (a >= '0' && a <= '9' && b >= '0' && b <= '9'){
        return b > a;
    }
    else{
        return 0;
    }
}

int Output(long long x){
    if (x < 0){
        printf("%c", '-');
        x = -x;
    }
    if (x > 0){
        Output(x / 11);
        if (x % 11 != 10){
            printf("%lld", x % 11);
        }
        else{
            printf("%c", 'A');
        }
    }
}

int main() {
    bool isWordStarted = 0;
    bool correct = 1;
    long long buffer = 0;
    int sign = 1;
    int previous;
    int c = '0';
    while (1) {
        previous = c;
        c = getchar();
        if (!IsSeparator(c)) {
            if (isWordStarted == 0 && c == '-'){
                sign = -1;
                c = '0';
            }
            else if (!(((c >= '0' && c <= '9' || c == 'A') && Comprassion(previous, c) )|| previous == '0' && c == '0')){
                correct = 0;
            }
            else{
                if (buffer == 0){
                    if (c != 'A'){
                        buffer = c - '0';
                    }
                    else{
                        buffer = 10;
                    }
                }
                else{
                    if (c != 'A'){
                        buffer = buffer * 11 + (c - '0');
                    }
                    else{
                        buffer = buffer * 11 + 10;
                    }
                }
            }
            isWordStarted = 1;
        } else if (isWordStarted) {
            if (correct){
                if (buffer == 0){
                    printf("%d", 0);
                    printf("%c", ' ');
                }
                else{
                    Output(buffer * sign);
                    printf("%c", ' ');
                }
            }
            buffer = 0;
            sign = 1;
            c = '0';
            correct = 1;
            isWordStarted = 0;
        }
        if (c == EOF) {
            break;
        }
    }
    return 0;
}
