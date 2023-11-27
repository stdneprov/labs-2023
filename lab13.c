#include <stdio.h>
#include <locale.h>

typedef unsigned long long Set;

int IsSeperator(long long c) {
    return (c == ' ')||(c == '\n')||(c == 255)||(c == ',')||(c == '\t');
}

void Add(Set *a, long long c) {
    if ((c >= 1072) && (c <= 1103)) { //1072 - а, 1103 - я
        *a |= (1u << (c - 1072));
    }
    if ((c >= 1040) && (c <= 1071)) { //1040 - А, 1071 - Я
        *a |= (1u << (c - 1040));
    }
}

long long GetUnicode() {
    unsigned char c = getchar();
    long long code = 0;
    if (((c & 128) == 0) || (c == 255)) {
        code = c;
    } else if ((c | 31) == 223) { //192 - 1100 0000, 223 - 1101 1111, 31 - 0001 1111
        code = (c & 31) << 6; //31 - 0001 1111 
        c = getchar();
        code |= (c & 63); //63 - 0011 1111
    } else if ((c | 15) == 239) { //224 - 1110 0000, 239 - 1110 1111, 15 - 0000 1111
        code = (c & 15) << 12; //15 - 0000 1111
        c = getchar();
        code |= (c & 63) << 6; //63 - 0011 1111
        c = getchar();
        code |= (c & 63); //63 - 0011 1111
    } else if ((c | 7) == 247) { //240 - 1111 0000, 247 - 1111 0111, 7 - 0000 0111
        code = (c & 7) << 18; //7 - 0111
        c = getchar();
        code |= (c & 63) << 12; //63 - 0011 1111
        c = getchar();
        code |= (c & 63) << 6; //63 - 0011 1111
        c = getchar();
        code |= (c & 63); //63 - 0011 1111
    }
    return code;
}


int main() {
    setlocale(LC_ALL, "");
    long long c;
    Set bitset = 0;
    int flag = 0;

    Set vowels = (1u << 0)|(1u << 5)|(1u << 8)|(1u << 14)|(1u << 19)|(1u << 27)|(1u << 29)|(1u << 30)|(1u << 31);
    Set voiced = (1u << 1)|(1u << 2)|(1u << 3)|(1u << 4)|(1u << 6)|(1u << 7)|(1u << 9)|(1u << 11)|(1u << 12)|(1u << 13)|(1u << 16);

    while(1) {
        c = GetUnicode();
        if (!IsSeperator(c)) {
            Add(&bitset, c);
        } else {
            if (((bitset & ~(vowels | voiced)) == 0) && (bitset != 0)) {
                flag = 1;
            }
            bitset = 0;
        }
        if (c == 255) {
            break;
        }
    }

    if (flag == 1) {
        printf("YES");
    } else {
        printf("NO");
    }
}