#include <stdio.h> 
#include <stdbool.h> 
#include <wchar.h>
#include <locale.h>

typedef long long Set; 

int IsSeparator(wchar_t c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == '\t');
}

bool IsVowel(Set a, wchar_t c) { 
    return (a & ~(1 << (c - L'а'))) != a; 
} 

void Add(Set *a, wchar_t c) {
    *a |= (1 << (c - 'a')); 

} 

bool IsIn(Set a, wchar_t c) { 
    return (a & ~(1 << (c - 'a'))) != a; 
}

int main(){ 
    setlocale(LC_ALL, "" );
    Set a = 0;
    int res = 0;
    Set vowels = 8187822369;
    bool flag = true; 
    while(1) {
        wchar_t c = getwchar();
        if (!IsIn(a, c)) {
            Add(&a, c);
        } else if (IsIn(a, c) && IsVowel(vowels, c)) {
            flag = false;
        }
        if (IsSeparator(c)) {
            if (flag) {
                res = 1;
            }
            a = 0;
            flag = true;
        } 
        if (c == WEOF) { 
            break; 
        } 
    }
    printf("%d", res); 
    return 0; 
}
