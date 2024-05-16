#include <stdio.h>
#include <stdbool.h>
/*
gfg
fgfgf
gg
*/
int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int NotThree(int r) {
    int x;
    x = r;
    while (x > 0) {
        if ((x % 5 > 2) && (x % 5 < 5)) {
            return 1;
        }
        if (x / 5 == 0) {
            return 0;
        }
        x = x / 5;
    }
}

int main() {
    int boof, start = 1;
    int k = 0;
    boof = 0;
    while (1) {
        int c = getchar();
//        printf("%lld\n", start);
//        printf("%lld\n", boof);
        if (IsSeparator(c)) {
            start = 1;
            if ((boof > 0) && (NotThree(boof))) {
//            if ((boof > 0)) {
                if (k == 1) {
                    printf("-%lld\n", boof);
                }
                else {
                    printf("%lld\n", boof);
                }
            }
            boof = 0;
            k = 0;

        }
        if (start == 1) {
            if (c >= '0' && c <= '4') {
                boof = boof * 5 + (c - '0');
//                printf("jj %lld\n", boof);
            } else if (c == '-' && boof == 0) {
                k += 1;
                if (k > 1) {
                    boof = 0;
                    start = 0;
                    k = 0;
                }
            } else if (!(IsSeparator(c))){
                boof = 0;
                start = 0;
                k = 0;
            }
        }
        if (c == EOF) {
            break;
        }
    }
//    printf("%lld\n", boof);

    return 0;
}
