// Есть ли гласная входящая в состав всех слов
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

int vowels_u[] = L"AEIOUАЕЁИОУЫЭЮЯ";
int vowels_l[] = L"aeiouаеёиоуыэюя";
int vowels_cnt = sizeof(vowels_u) / (sizeof(vowels_u[0])) - 1;

bool IsSeparator(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.' ||
           c == EOF;
}

int Mask(int c) {
    int res = 0;
    for (int i = 0; i < vowels_cnt; i++) {
        if (vowels_u[i] == c || vowels_l[i] == c) {
            res = res | 1 << i;
            break;
        }
    }
    return res;
}

int FullMask(void) {
    int res = 0;
    for (int i = 0; i < vowels_cnt; i++) {
        res = res | 1 << i;
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
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int res = FullMask();
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
            cur |= Mask(c);
        }
        if (c == EOF)
            break;
    };
    for (int i = 0; i < vowels_cnt; i++) {
        if (res & (1 << i)) {
            printf("%lc\n", vowels_u[i]);
        }
    }
    return 0;
}

