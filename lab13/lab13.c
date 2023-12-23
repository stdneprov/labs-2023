#include <stdio.h>
#include <stdlib.h>
#define SOGL11 66567390


int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == '\t') || (c == EOF);
}

int CharBytes(int twin) {
    if (twin >> 7 == 0) {
        return 1;
    } else if ((twin >> 5 == 6)) {
        return 2;
    } else if ((twin >> 4 == 14)) {
        return 3;
    }
    return 4;
}

typedef long long Set;

void AddLittle(Set *a, char wer) {
    *a |= 1 << (wer - 1071);
}

void AddBig(Set *a, char wer) {
    *a |= 1 << (wer - 1039);
}

int main() {
    int n, result = 0;
    int result1 = 0;
    Set a = 0; 
    while(1) {
        int c = getchar();
        
        if (IsSeparator(c)) {
            if (result1 == 1) { 
                result = 1;
            }
            result1 = 0;
            if (c != EOF) {
                continue;
            }
        }
        if (c == EOF) { 
            break;
        }
        if (CharBytes(c) == 1) { 
            continue;
        }
        if (CharBytes(c) == 2) {
            int rus = getchar();
            int m = ((c & 31) << 6) | (rus & 63);
            if ((((1 << (m - 1072)) & SOGL11) != 0) || (((1 << (m - 1040)) & SOGL11) != 0)) { 
                if (m > 1040 && m < 1072) { 
                    AddBig(&a, m);
                    result1 += 1;
                } else {
                    AddLittle(&a, m);
                    result1 += 1;
                }
            }


        }
        if (CharBytes(c) == 3) {
            int c2 = getchar();
            int c3 = getchar();
            continue;
        }
        if (CharBytes(c) == 4) {
            int c2 = getchar();
            int c3 = getchar();
            int c4 = getchar();
            continue;
        }
    }
    printf("%d\n", result);
    return 0;
}