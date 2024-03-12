#include <stdio.h>
#include <stdlib.h>
                         // яюэьыъщшчцхфутсрпонмлкйизжедгвба
#define GLAS 3892855073  // 11101000000010000100000100100001 // множество гласных букв(и больших и маленьких кроме "ё")

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == '\t');
}

// Считаем байты
int CharBytes(int twin) { 
    if (twin >> 7 == 0) {
        return 1;
    } else if ((twin >> 5 == 6)) {
        return 2;
    } else if ((twin >> 4 == 14)) {
        return 3;
    }
    return 4;
}

int main() {
    int result = 0;
    int first = 0;
    int last = 0;
    int k = 0; //нужен для проверки того, что у нас первая буква
    while(1) {
        int c = getchar(); //считываем первый байт
        int rus, c2, c3, c4;
        if (IsSeparator(c)) {
            if (first + last == 2) {
                result = 1;
            }
            first = 0;
            last = 0;
            k = 0;
        }
        if (c == EOF) {
            break;
        }
        if (CharBytes(c) == 1) {
            continue;
        }
        if (CharBytes(c) == 2) {
            rus = getchar();
            int m = ((c & 31) << 6) | (rus & 63);
            if ((((1 << (m - 1072)) & GLAS) != 0) || (m == 1025) || (m == 1105)) {  //1025 и 1105 это коды большой и маленькой буквы ё
                if (k == 0) {
                    first = 1;
                }
                last = 1;
            } else {
                last = 0;
            }
            k = 1;


        }
        if (CharBytes(c) == 3) {
            c2 = getchar();
            c3 = getchar();
            continue;
        }
        if (CharBytes(c) == 4) {
            c2 = getchar();
            c3 = getchar();
            c4 = getchar();
            continue;
        }
    }
    printf("%d\n", result);
    return 0;
}
