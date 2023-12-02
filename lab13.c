#include <stdio.h> 
#include <stdbool.h> 
#include <wchar.h>
#include <locale.h>

typedef long long Set; 

int IsSeparator(wchar_t c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

bool IsIn(Set a, wchar_t c){ 
    return (a & ~(1 << (c - 'a'))) != a; 
}

bool IsVowel(wchar_t ch) {
    Set russian_vowels[] = {L'а', L'е', L'и', L'о', L'у', L'ы', L'э', L'ю', L'я',
                            L'А', L'Е', L'И', L'О', L'У', L'Ы', L'Э', L'Ю', L'Я'};
    int length = sizeof(russian_vowels) / sizeof(russian_vowels[0]);

    for (int i = 0; i < length; i++) {
        if (ch == russian_vowels[i]) {
            return true;
        }
    }

    return false;
}

void Add(Set *a, wchar_t c){
    if(IsVowel(c)){
        *a |= (1 << (c - 'a')); 
    }
} 
 
int main(){ 
    setlocale(LC_ALL, "" );
    Set a = 0;
    int res = 0;
    bool flag = false; 
    while(1){ 
        wchar_t c = getwchar();
        if (IsVowel(c) && !IsIn(a, c)) {
            Add(&a, c);
            flag = true;
        } else if (IsIn(a, c)) {
            flag = false;
        }
        if (IsSeparator(c)) {
            if (flag) {
                res = 1;
            }
        } 
        if (c == EOF) { 
            break; 
        } 
    }
    printf("%d", res); 
    return 0; 
}
