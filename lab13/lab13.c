// Есть ли гласная входящая в состав всех слов
#include <stdio.h>
#include <stdbool.h>

bool IsSeparator(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.' ||
           c == EOF;
}

int Mask(int c, int *vowels_u, int *vowels_l) {
    int res = 0;
    for (int i = 0; i < 15; i++) {
        if (vowels_u[i] == c || vowels_l[i] == c) {
            res = res | 1 << i;
            break;
        }
    }
    return res;
}

int GetWChar(void) {
    int c = getchar();
    if (c >> 7 == 0) {
        return c;
    }
    if (c >> 5 == 6) {
        int c2 = getchar();
        return ((c & 31) << 6) | (c2 & 63);
    }
    if (c >> 4 == 14) {
        int c2 = getchar();
        int c3 = getchar();
        return ((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63);
    }
    if (c >> 3 == 30) {
        int c2 = getchar();
        int c3 = getchar();
        int c4 = getchar();
        return ((c & 7) << 18) | ((c2 & 63) << 12) | ((c3 & 63) << 6) |
               (c4 & 63);
    }
    return -1;
}

int main(void) {
    int res = 0xFFFF;
    int cur = 0;
    int c;
    bool is_word = true;
    while (true) {
        c = GetWChar();
        if (IsSeparator(c)) {
            if (is_word)
                res &= cur;
            is_word = false;
            cur = 0;
        } else {
            is_word = true;
            cur |= Mask(c, L"AEIOUАЕЁИОУЫЭЮЯ", L"aeiouаеёиоуыэюя");
        }
        if (c == EOF)
            break;
    };
    if (res != 0)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
