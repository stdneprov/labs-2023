#include <stdio.h>  
#include <stdbool.h>  
#include <wchar.h> 
#include <locale.h> 
 
typedef long long Set;  
 
int IsSeparator(wchar_t c) { 
    return (c == ' ') || (c == ',') || (c == '\n') || (c == WEOF) || (c == '\t'); 
} 
 
bool IsConsonan(wchar_t c){ 
    return (wcschr(L"ЙЦКНГШЩЗХФВПРЛДЖЧСМТБйцкнгшщзхфвпрлджчсмтб", c)); 
} 
 
bool IsVowel(wchar_t c){ 
    return (wcschr(L"УЕЫАОЭЯИЮуеаоэяию", c)); 
} 
 
void Add(Set *a, wchar_t c){ 
    *a |= (1 << (c - 'a'));  
}  
 
int main(){  
    setlocale(LC_ALL, ""); 
 
    Set curVowel = 0; 
    Set curConsonan = 0; 
    Set prevVowel = 0; 
    Set prevConsonan = 0; 
 
    int answer = 0; 
    while(1){  
        wchar_t c = getwchar(); 
        if (IsSeparator(c)){ 
            if (((curConsonan == prevConsonan) && (curConsonan != 0) ) || ((curVowel == prevVowel) && (curVowel != 0))){ 
                answer = 1; 
            } 
            prevConsonan = curConsonan; 
            prevVowel = curVowel; 
            curConsonan = 0; 
            curVowel = 0; 
        } else { 
            if (IsVowel(c)) { 
                Add(&curVowel, c); 
            } else { 
                Add(&curConsonan, c); 
            } 
        } 
        if (c == WEOF) {  
            break;  
        }  
    } 
    printf("%d\n", answer);  
    return 0;  
}