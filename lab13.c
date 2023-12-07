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
    return (ch == 1059) || (ch == 1091) || (ch == 1045) || (ch == 1077) || (ch == 1067) ||
           (ch == 1099) || (ch == 1040) || (ch == 1072) || (ch == 1054) || (ch == 1086) ||
           (ch == 1069) || (ch == 1101) || (ch == 1071) || (ch == 1103) || (ch == 1048) ||
           (ch == 1080) || (ch == 1070) || (ch == 1102) || (ch == 1105) || (ch == 1025);
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
    while(1) {
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
            a = 0;
        } 
        if (c == WEOF) { 
            break; 
        } 
    }
    printf("%d", res); 
    return 0; 
}
