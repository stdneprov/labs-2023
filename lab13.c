#include <stdio.h>
#include <stdlib.h>
#define SOGL11 66567390  // множество согласных

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == '\t') || (c == EOF);
}

int KolvoBite(int bite) { //считает кол-во байт
    if (bite >> 7 == 0) {
        return 1;
    } else if ((bite >> 5 == 6)) {
        return 2;
    } else if ((bite >> 4 == 14)) {
        return 3;
    }
    return 4;
}

typedef long long Set;

void DobavitLittle(Set *a, char bukva) { //добавляет в множество маленькие буквы
    *a |= 1 << (bukva - 1071);
}

void DobavitBig(Set *a, char bukva) { //добавляет в множество большие буквы
    *a |= 1 << (bukva - 1039);
}

int main() {
    int result = 0;
    int result1 = 0; //результат для одного слова (1 значит, что в слове только 1 согласная)
    Set a = 0; //множество глассных букв нынешнего слова
    while(1) {
        int c = getchar();
        
        if (IsSeparator(c)) {
            if (result1 == 1) { // сравнивает множества
                result = 1;
            }
            result1 = 0;
            if (c != EOF) {
                continue;
            }
        }
        if (c == EOF) { //заканчивает программу
            break;
        }
        if (KolvoBite(c) == 1) { //считывает все байты одной буквы
            continue;
        }
        if (KolvoBite(c) == 2) {
            int c2 = getchar();
            int full = ((c & 31) << 6) | (c2 & 63); //преобразует в юникод
            if ((((1 << (full - 1072)) & SOGL11) != 0) || (((1 << (full - 1040)) & SOGL11) != 0)) { 
                if (full > 1040 && full < 1072) { //проверяет на то, большая ли это буква
                    DobavitBig(&a, full);
                    result1 += 1;
                } else {
                    DobavitLittle(&a, full);
                    result1 += 1;
                }
            }

        }
        if (KolvoBite(c) == 3) { //считывает все байты одной буквы
            int c2 = getchar();
            int c3 = getchar();
            continue;
        }
        if (KolvoBite(c) == 4) { //считывает все байты одной буквы
            int c2 = getchar();
            int c3 = getchar();
            int c4 = getchar();
            continue;
        }
    }
    printf("%d\n", result);
    return 0;
}

