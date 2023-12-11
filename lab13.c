
#include <stdio.h>  
#include <stdbool.h>  
#include <wchar.h>  //считывать юникод
#include <locale.h> //работали все языки

typedef long long Set;  

int IsSeparator(wchar_t c) { 
    return (c == ' ') || (c == ',') || (c == '\n') || (c == WEOF) || (c == '\t'); //проверка на разделители
} 

void Add(Set *a, wchar_t c) {
    if (c >= 1040 & c <= 1071) {
        *a |= (1 << (c - 1040));
    } else if (c >= 1072 & c <= 1103) {
        *a |= (1 << (c - 1072));
    }
}  

int NumAlph(char* c) {
    return ((c[0] & 31) << 6) | (c[1] & 63) - 1072;
}

int main(){  
    Set notSogl = (1 << (NumAlph("а"))) | (1 << (NumAlph("о"))) | (1 << (NumAlph("у"))) | (1 << (NumAlph("э"))) | (1 << (NumAlph("ы"))) | (1 << (NumAlph("я"))) | (1 << (NumAlph("ё"))) | (1 << (NumAlph("е"))) | (1 << (NumAlph("ю"))) | (1 << (NumAlph("и"))) | (1 << (NumAlph("ь"))) | (1 << (NumAlph("ъ")));        
    setlocale(LC_ALL, ""); //все локализации

    Set curSogl = 0; //для текущего слова, хранит все согласные
    Set prevSogl = 0; //все согласные с предудышим словом

    int answer = 0; //ответ
    while(1){  
        wchar_t c = getwchar(); //считываем символ
        if (IsSeparator(c)){ 
            if ((((curSogl & ~notSogl) == (prevSogl & ~notSogl)))) { //сравниваем буквы
                answer = 1; 
            } 
            prevSogl = curSogl; //пересваиваем
            curSogl = 0; //обнуляю 
        } else { 
                Add(&curSogl, c); 
        } 
        if (c == WEOF) {  
            break;  
        }  
    } 
    printf("%d\n", answer);  
    return 0;  
}

