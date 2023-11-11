
#include <stdio.h>
#include <stdbool.h>

int IsSep(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int main() {
    long long wordCounter = 0;
    bool isWordStarted = 0;
    int countSlash = 0;
    while (1) {
        int c = getchar();
        if (c == '/' && countSlash < 2){
            countSlash ++;
            continue;
        } else if (c != '/' && countSlash == 1){
            countSlash = 0;
        }
        else{
            if (!IsSep(c)) {
                isWordStarted = 1;
            } else if (isWordStarted) {
                if(countSlash == 2){
                    wordCounter += 1;
                }
                isWordStarted = 0;
            }
            if (c == '\n'){
                countSlash = 0;
            }
            if (c == EOF) {
                break;
            }
        }

        
    }

    printf("%lld\n", wordCounter);

    return 0;
}
