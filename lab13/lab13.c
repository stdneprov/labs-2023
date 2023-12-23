#include <stdbool.h>
#include <stdio.h>

typedef long long Set;

bool IsSep(long long c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == EOF;
}

long long ReadWideChars() {
    long long c1 = getchar();
    long long c2 = 0;
    // 1100 0000
    if ((c1 & (7 << 5)) == 192) {
        c1 = c1 & ~(-1 << 6);  // убираем первые незначащие символы
        c2 = getchar();
        c1 = (c1 << 6) | (c2 & ~(-1 << 7));
    } else if ((c1 & (15 << 4)) == 224) {  // 1110 0000
        c1 = c1 & ~(-1 << 5);
        for (int i = 0; i < 2; i++) {
            c2 = getchar();
            c1 = (c1 << 6) | (c2 & ~(-1 << 7));
        }
    } else if ((c1 & (31 << 3)) == 240) {  // 1111 0000
        c1 = c1 & ~(-1 << 4);
        for (int i = 0; i < 3; i++) {
            c2 = getchar();
            c1 = (c1 << 6) | (c2 & ~(-1 << 7));
        }
    }
    return c1;
}

Set GetVowels() {
    Set a = 1LL | (1LL << 5) | (1LL << 6) | (1LL << 9) | (1LL << 15) |
            (1LL << 20) | (1LL << 28) | (1LL << 30) | (1LL << 31) |
            (1LL << 32) | (1LL << 27) | (1LL << 29);  // множество гласных + ь/ъ
    return a;
}

bool CheckInSet(Set a, long long c) { return (a & ~(1 << (c - 1040))) != a; }

bool CheckIsConsonant(Set a, long long c) {
    // обрабатываем ё Ё
    if (c == 1105) {
        return 0;
    }
    if (c == 1025) {
        return 0;
    }

    if (c >= 1072 & c <= 1103) {
        c -= 32;  // переводим в заглавные
    }

    if (c < 1040 || c > 1071) {
        return 0;  // не кириллица
    }

    c += (c >= 1046) ? 1: 0;  // к буквам после ё добавляем плюс один чтобы не сьехал set

    return CheckInSet(a, c);
}

int main() {
    Set consonants = ~GetVowels();  // реверсим set гласных, т.е получаем согласные
    long long WordCounter = 0;
    bool WordStarted = 0;
    bool FirstLetterIsConsonant = 0;
    bool LastLetterIsConsonant = 0;
    while (1) {
        long long c = ReadWideChars();
        if (!IsSep(c)) {
            if (!WordStarted) {
                if (CheckIsConsonant(consonants, c)) {
                    FirstLetterIsConsonant = 1;
                }
                WordStarted = 1;
            }
            LastLetterIsConsonant = CheckIsConsonant(consonants, c);
        } else {
            if (WordStarted && LastLetterIsConsonant && FirstLetterIsConsonant) {
                WordCounter += 1;
            }
            WordStarted = 0;
            LastLetterIsConsonant = 0;
            FirstLetterIsConsonant = 0;
        }

        if (c == EOF) {
            break;
        }
    }
    printf("%lld", WordCounter);
}
