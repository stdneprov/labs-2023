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
    if(ch == L'а' || ch == L'е' || ch == L'и' || ch == L'о' || ch == L'у' || ch == L'ы' || ch == L'э' || ch == L'ю' || ch == L'я'
     || ch == L'А' || ch == L'Е' || ch == L'И' || ch == L'О' || ch == L'У' || ch == L'Ы' || ch == L'Э' || ch == L'Ю' || ch == L'Я') {
        return true;
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
