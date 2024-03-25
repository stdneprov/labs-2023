#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == '\n') || (c == '\t');
}

int Mod(int a, int b) {
    return (a % b + b) % b;
}

int main() {
    int count = 1;
    int count1 = 0;
    char a = ' ';
    while (1) {
        int c = getchar();
        if (c == '\n') {
            count = 0;
        }
        if (c == EOF) {
            break;
        }
        if (IsSeparator(c) && (c != a)) {
            count += 1;
            count = Mod(count, 26);
            printf("%c", c);
        } else if (c >= 'a' && c <= 'z') {
            if (c - count < 'a') {
                count1 = -count;
                printf("%c", c + Mod(count1, 26));
            } else {
                printf("%c", c - count);
            }
        } else if (c >= 'A' && c <= 'Z') {
            if (c - count < 'A') {
                count1 = -count;
                printf("%c", c + Mod(count1, 26));
            } else {
                printf("%c", c - count);
            }
        } else {
            printf("%c", c);
        }
        a = c; 
        if (c == '\n') {
            a = ' ';
        }
    }
}