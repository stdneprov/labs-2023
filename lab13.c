#include <stdio.h>
#include <wchar.h> //для работы с 2-х байтовым юникодом
#include <locale.h> //для работы русской локализации
#include <stdbool.h>

int IsSeparator(wchar_t ch) { 
    return (ch == ' ') || (ch == ',') || (ch == '\n') || (ch == '\t') || (ch == WEOF); 
}

int IsRus(wchar_t ch) { //является ли символ буквой кириллицы
    return (ch >= 1040 && ch <= 1103);
}

int main() {       
    setlocale(LC_ALL, "");
    long long current_set = 0;
    long long previous_set = 0;
    int answer = 0;
    
    while (1) {
        wchar_t ch = getwchar();
        if (IsSeparator(ch)) {
            if (current_set != previous_set && previous_set != 0 ) {
                answer += 1;
            }
            previous_set = current_set;
            current_set = 0;
        } else {
            long long letter;
            if (IsRus(ch)) {
                letter = 1u << (ch - 1040);
            } else {
                letter = 1u << (ch - 'a');
            }
            current_set = current_set | letter;
        }

        if (ch == WEOF) {
            break;
        }
    }
    if (answer - 1 != 0) {
        printf("YES");
    } else {
        printf ("NO");
    }
}
