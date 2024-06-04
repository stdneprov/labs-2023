#include <stdio.h>
#include <stdlib.h>

typedef long long Set;

int IsSeparator(long long c);
void Add(Set *a, long long c);
long long GetUnicode();

int main() {
    Set firstKindVowels = 671629569; // аоуэыи
    Set secondKindVowels = 7516192800; // яёюе
    Set word = 0;
    long long c = 0;
    while(1) {
        c = GetUnicode();
        if (!IsSeparator(c)) {
            Add(&word, c);
        } else {
            if (((word & ~firstKindVowels) == word) && ((word & ~secondKindVowels) != word)) { // еслив слове есть гласные второго типа но нет гласных первого типа
                printf("YES");
                break;
            }
            word = 0;
            if (c == EOF) {
                printf("NO");
                break; 
            }
        }
    }
    return 0;
}

int IsSeparator(long long c) {
    return (c == ' ') || (c == ',') || (c == '\t') || (c == '\n') || (c == EOF);
}

void Add(Set *a, long long c) {
    if ((c >= 1040) && (c <= 1071)) { // А-Я
        *a |= (1 << (c - 1040));
    } else if ((c >= 1072) && (c <= 1103)) { // а-я
        *a |= (1 << (c - 1072));
    } else if ((c == 1025)) { // Ё
        *a |= (1 << (c - 990));
    } else if (c == 1105) { // ё
        *a |= (1 << (c - 1073)); 
    } 
}

long long GetUnicode() {
    char c = getchar();
    if (c == EOF) {
      return EOF;
    }
    long long letterCode = 0;
    if ((c & (1 << 7)) == 0) { // если число подходит под маску однобайтового - 0ххххххх
        letterCode = c;
    } else if ((c & (3 << 6)) == (3 << 6)) { // если число подходит под маску двухбайтового - 110ххххх...
        letterCode = (c & 31) << 6; // первый байт
        letterCode |= (getchar() & 63); // второй байт
    } else if ((c & (7 << 5)) == (7 << 5)) { // если число подходит под маску трёхбайтового - 1110хххх...
        letterCode = (c & 15) << 12;
        letterCode |= (getchar() & 63) << 6;
        letterCode |= (getchar() & 63);
    } else if ((c & (15 << 4)) == (15 << 4)) { // если число подходит под маску четырёхбайтового - 11110ххх...
        letterCode = (c & 7) << 18;
        letterCode |= (getchar() & 63) << 12;
        letterCode |= (getchar() & 63) << 6;
        letterCode |= (getchar() & 63);
    }
    return letterCode; 
}
