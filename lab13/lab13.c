#include <stdio.h>
#include <stdlib.h>

int IsGlas(int bukva) {
    return (bukva == 1045) || (bukva == 1045) || (bukva == 1048) || (bukva == 1054) || (bukva == 1059) || (bukva == 1080) || (bukva == 1086) || (bukva == 1091);
}

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == '\t');
}

int CharBytes(int twin) {
    if (twin >> 7 == 0) {
        return 1;
    } else if (twin >> 5 == 6) {
        return 2;
    } else if (twin >> 4 == 14) {
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
    int n, sec, result = 0;
    Set a = 0;
    Set b = 0;
    while(1) {
        int c = getchar();
        
        if (IsSeparator(c)) {
            if (a == b && a != 0) {
                result = 1;
            }
            b = a;
            a = 0;
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
            if (((m > 1040 && m < 1066) || (m > 1072 && m < 1098)) && !(IsGlas(m))) {
                if (m > 1040 && m < 1072) {
                    AddBig(&a, m);
                } else {
                    AddLittle(&a, m);
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