#include <stdio.h> 
#include <stdbool.h> 
#include <wchar.h>
#include <locale.h>

typedef long long Set; 

int IsSeparator(wchar_t c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == '\t');
}

bool IsConsonant(Set a, wchar_t c) { 
    return (a & ~(1 << (c - L'а'))) != a; 
} 

void AddToSet(Set *a, wchar_t c) {
    *a |= (1 << (c - 'a')); 

} 

bool IsInSet(Set a, wchar_t c) { 
    return (a & ~(1 << (c - 'a'))) != a; 
}

int main(){ 
    setlocale(LC_ALL, "" );
    Set a = 0;
    int res = 0;
    Set consonant = 66567902;
    bool uniqueconsonant = true; 
    while(1) {
        wchar_t c = getwchar();
        if (!IsInSet(a, c)) {
            AddToSet(&a, c);
        } else if (IsInSet(a, c) && IsConsonant(consonant, c)) {
            uniqueconsonant = false;
        }

        if (IsSeparator(c)) {
            if (uniqueconsonant) {
                res = 1;
            }
            a = 0;
            uniqueconsonant = true;
        } 

        if (c == WEOF) { 
            break; 
        } 
    }

    printf("%d\n", res); 
    return 0; 
}