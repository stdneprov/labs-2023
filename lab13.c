#include <stdio.h>
#include <stdlib.h>

typedef long long Set;

void Add(Set* a, int value) {
    *a |= (1 << (value - 1));
}

int IsSep(int c) {
    return ((c == ' ') || (c == ',') || (c == '\t') || (c == EOF) || (c == '\n'));
}

int Rusalf(int uni) {

    if (uni == 1025 || uni == 1105) {
        return 33; // буква ё и Ё

 } else if (uni < 1040) {
        return 0; //мимо

 } else if (uni < 1072) {
        return uni - 1039; // заглавные А-Я

 } else if (uni < 1104) {
        return (uni - 1071); // строчные а-я

 } else {
        return 0;//мимо
    }
}

int GetCharUni() {
    char c = getchar();

    if (c == EOF) {
        return EOF;
    }

    int uni = 0;

    if ((c & (1 << 7)) == 0) { // однобайтовая

        uni = c;

 } else if ((c & (1 << 5)) == 0) { //двухбайтовая

        uni = (c & ~(-1 << 5)); 
        uni <<= 6;
        uni |= (getchar() & ~(-1 << 6)); 

 } else if ((c & (1 << 4)) == 0) { //трёхбайтовая

        uni = (c & ~(-1 << 4));
        for (int i = 0; i < 2; ++i) {
            uni <<= 6;
            uni |= (getchar() & ~(-1 << 6));   
        }

 } else if ((c & (1 << 3)) == 0) { // четырёхбайтовая

        uni = (c & ~(-1 << 3));
        for (int i = 0; i < 3; ++i) {
            uni <<= 6;
            uni |= (getchar() & ~(-1 << 6));   
        }

    }

    return uni;
}


int main() {

    Set glasn = 8120713505; // ё яюэь ыъщш чцхф утср понм лкйи зжед гвба
    Set word = 0;

    while (1) {
        int c = GetCharUni(); // получаем юникод
        if (IsSep(c)) { // конец слова
            word &= glasn; // нас интересуют согласные
            
            int count = 0;

            while (word > 0) { // считаем согласные
                count += word & 1;
                word >>= 1;
                if (count > 1) { // больше двух - бан
                    break;
                }
            }

            if (count == 1) { // одна - лайк
                printf("1\n");
                break;
            }

            word = 0; // сбрасываем слово

            if (c == EOF) { 
                printf("0\n");
                break;
            }
        }

        int rushn = Rusalf(c); //Если русский алфавит
        
        if (rushn) {
            Add(&word, rushn);
        }
    }

    return 0;
}