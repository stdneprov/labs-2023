#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <locale.h>

typedef long long Set;

int IsSeparator(wchar_t c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

bool IsInSet(Set a, wchar_t c) {
    return (a & ~(1 << (c - 'a'))) != a;
}

bool IsConsonant(wchar_t c){
    return(wcschr(L"йцкнгшщзхфвпрлджчсмтбЙЦКНГШЩЗХФВПРЛДЖЧСМТБ", c));
}

void AddToSet(Set *a, wchar_t c){
    if(IsConsonant(c)){
        *a |= (1 << (c - 'a'));
    }
}

int main(){
    setlocale(LC_ALL, "" );
    Set a = 0;
    bool UniqueConsonant = false;
    int result = 0;
    while(1){
        wchar_t c = getwchar();
        if (IsConsonant(c) && !IsInSet(a, c)) {
            AddToSet(&a, c);
            UniqueConsonant = true;
        } else if (IsInSet(a, c)) {
            UniqueConsonant = false;
        }
        if (IsSeparator(c)) {
            if (UniqueConsonant) {
                result = 1;
            }
        }

        if (c == EOF) {
            break;
        }
    }

    if (result == 1){
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}