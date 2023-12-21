#include <stdio.h>

typedef long long Set;

int IsSep(long long s) {
    return ((s == ' ') || (s == ',') || (s == '\t') || (s == '\n')) ||
           (s == EOF);
}

void Add(long long x, Set* alf) {
    if (x == 1105 || x == 1025) {
        *alf |= 1LL << 33;
    } else {
        if (x >= 1072) {
            x -= 32;
        }
        *alf |= 1 << (x - 1040);
    }
}

int GetCharMy(void) {
    int x;
    x = getchar();
    if (x == EOF) {
        return EOF;
    } else if ((x & (1 << 7)) == 0) {
    } else if ((x & (1 << 5)) == 0) {
        x = (x & ~(-1 << 5)) << 6;
        x |= (getchar() & ~(-1 << 6));
    } else if ((x & (1 << 4)) == 0) {
        x = x & ~(-1 << 4);
        for (int i = 0; i < 2; ++i) {
            x <<= 6;
            x |= (getchar() & ~(-1 << 6));
        }
    } else if ((x & (1 << 3)) == 0) {
        x = x & ~(-1 << 3);
        for (int i = 0; i < 3; ++i) {
            x <<= 6;
            x |= (getchar() & ~(-1 << 6));
        }
    }
    return x;
}

int IsRus(long long x) {
    return (x == 1105 || x == 1025) || (x > 1039 && x < 1104);
}

int IsSogl(long long x) {
    if (IsRus(x)) {
        Set zero = 0;
        Add(x, &zero);
        return ((zero | 66567902) == 66567902);
    }
    return 0;
}

int IsSwist(Set x) { return ((x | 4325504) == 4325504); }

int main(void) {
    int a, len = 0;
    Set nowWord = 0;
    while (1) {
        a = GetCharMy();
        if (!IsRus(a) && !IsSep(a)) {
            len = 0;
            nowWord = 0;
            continue;
        }
        if (IsSep(a)) {
            if (IsSwist(nowWord) && (len > 0)) {
                printf("1\n");
                return 0;
            }
            len = 0;
            nowWord = 0;
        }
        if (a == EOF) {
            break;
        }
        if (IsSogl(a)) {
            Add(a, &nowWord);
        }
        len += 1;
    }
    printf("0\n");
    return 0;
}
