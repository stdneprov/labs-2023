#include <stdio.h>
                         // яюэьыъщшчцхфутсрпонмлкйизжедгвба
#define Gluhie 66487296  // 00000011111101101000010000000000 
#define SOGL11 66567390  // 00000011111101111011110011011110

typedef long long Set;

void Add(Set *a, char c) {
    *a |= (1 << (c - 1040));
}

void Add2(Set *a, char c) {
    *a |= (1 << (c - 1072));
}

int IsSeparator(char c) {
    return (c == ' ') || (c == '\n') || (c == '\t') || (c == EOF);
}

int main() {
    Set a = 0;
    int k = 0;
    while (1) {
        int c = getchar();
        if (IsSeparator(c)) {
            if (((a & Gluhie) == a) && (a != 0)) {
                k += 1;
            }
            a = 0;
        }
        if (c == EOF) {
            break;
        }
        if (c >> 7 == 0) {
            continue;        
        } else if (c >> 5 == 6) {
            int c1 = getchar();
            int i = ((c & 31) << 6) | (c1 & 63);
            if ((i >= 1040) && (i <=1071)) {
                if (((1 << (i - 1040)) & SOGL11) != 0) {
                    Add(&a, i); 
                }  
            }
            if ((i >= 1072) && (i <= 1103)) {
                if (((1 << (i - 1072)) & SOGL11) != 0) {
                    Add2(&a, i);
                }
            }
            //11010000 10111111   00010000000000 00111111
            //00011111 00111111   00010000111111 1072 1040 
        } else if (c >> 4 == 14) {
            int c1 = getchar();
            int c2 = getchar();
            continue;
        } else {
            int c1 = getchar();
            int c2 = getchar();
            int c3 = getchar();
            continue;
        }
    }
    if (k > 0) {
        printf("YES");
    } else {
        printf("NO");
    }
    return 0;
}