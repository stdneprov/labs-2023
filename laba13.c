#include <stdio.h>  
#include <stdbool.h>  
#include <wchar.h> 
#include <locale.h> 
 
typedef long long Set;  
 
int IsSeparator(wchar_t c) { 
    return (c == ' ') || (c == ',') || (c == '\n') || (c == WEOF) || (c == '\t'); 
} 
 
bool IsConsonan(Set a, wchar_t c){ 
    return (a & ~(1 << (c - L'а'))) != a; 
} 
 
void Add(Set *a, wchar_t c){ 
    *a |= (1 << (c - L'а'));  
}  
 
int main(){  
    setlocale(LC_ALL, ""); 
    Set consonans = 66567902; 
    Set curConsonan = 0; 
    Set prevConsonan = 0; 
 
    int answer = 0; 
    while(1){  
        wchar_t c = getwchar(); 
        if (IsSeparator(c)){ 
            if ((curConsonan == prevConsonan) && (curConsonan != 0)){ 
                answer = 1; 
            } 
            prevConsonan = curConsonan; 
            curConsonan = 0; 

        } else { 
            if (IsConsonan(consonans, c)) { 
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
