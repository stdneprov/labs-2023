#include <stdio.h>
#include <stdbool.h>

// (1 байт)  0aaa aaaa &1111 1111 - 255 или 1000 0000 - 128
// (2 байта) 110x xxxx 10xx xxxx первый байт в интервале 1100 0000(192) до 1101 1111(223), второй байт 1000 0000(128) до 1011 1111 (191)   , сдвиг на 6 бит
// (3 байта) 1110 xxxx 10xx xxxx 10xx xxxx первый байт в интервале 1110 0000(224) до 1110 1111(239), остальные байты со 128 до 191  сдвиг на 12 бит, первые 4 бита из первого байта
// (4) 1111 0xxx ???? 10xx xxxx 10xx xxxx 10xx xxxx - интервал 240,247 сдвиги 18 12 6 
//для 2 байт зн 1ого &0001 1111(31) - маска
//для 3 байт зна 1ого &0000 1111(15) - маска
//для 4 байт зн 1ого &0000 0111(7)
//для ост байт - &0011 1111(63)

long long To_Unicode(){
    long long value = 0;
    unsigned char c = getchar();
    if (((c & 128) == 0) || (c == 255)) {
        value = c;
    }else if ((c >= 192) && (c <= 223)) {
        value |= ((c & 31) << 6);
        c = getchar();
        value |= (c & 63);
    }else if ((c >= 224) && (c <= 239)) {
        value |= (c & 15) << 12;
        c = getchar();
        value |= (c & 63) << 6;
        c = getchar();
        value |= (c & 63);
    }else if ((c >= 240) && (c <= 247)) {
        value |= (c & 7) << 18;
        c = getchar();
        value |= (c & 63) << 12;
        c = getchar();
        value |= (c & 63) << 6;
        c = getchar();
        value |= (c & 63);
    }
    return value;
}

int IsSeparator(char c) {
    return ((c == ' ') || (c == 255) || (c == '\n') || (c == '\t') || (c == ','));
}

typedef long long Set;


long long Get_Unicode(char *c) { //принимает два байта
    long long value = 0;
    value |= ((c[0] & 31) << 6); //сдвиг первого байта
    value |= (c[1] & 63); //второй байт
    return value;
}

bool IsIn(Set a, long long c) {
    return (a & ~(1 << (c - Get_Unicode("А")))) != a;
}

void Add(Set *a, long long c) {
    *a |= (1u << (c - Get_Unicode("А")));
}

void Clear(Set *a) {
    *a &= ~(*a);
}


// Б, В, Г, Д, Ж, З, Й, К, Л, М, Н, П, Р, С, Т, Ф, Х, Ц, Ч, Ш, Щ.
int main() {
    Set consonant = ((1u << Get_Unicode("Б") - Get_Unicode("А")) | (1u << Get_Unicode("В")- Get_Unicode("А")) | (1u << Get_Unicode("Г") - Get_Unicode("А")) | (1u << Get_Unicode("Д") - Get_Unicode("А")) | (1u << Get_Unicode("З") - Get_Unicode("А"))
    | (1u << Get_Unicode("Й") - Get_Unicode("А")) | (1u << Get_Unicode("К") - Get_Unicode("А")) | (1u << Get_Unicode("Л") - Get_Unicode("А")) | (1u << Get_Unicode("М") - Get_Unicode("А")) | (1u << Get_Unicode("Н") - Get_Unicode("А")) | (1u << Get_Unicode("П") - Get_Unicode("А"))
    | (1u << Get_Unicode("Р") - Get_Unicode("А")) | (1u << Get_Unicode("С") - Get_Unicode("А")) | (1u << Get_Unicode("Т") - Get_Unicode("А")) | (1u << Get_Unicode("Ф") - Get_Unicode("А")) | (1u << Get_Unicode("Х") - Get_Unicode("А")) | (1u << Get_Unicode("Ц") - Get_Unicode("А")) 
    | (1u << Get_Unicode("Ч") - Get_Unicode("А")) | (1u << Get_Unicode("Ш") - Get_Unicode("А")) | (1u << Get_Unicode("Щ") - Get_Unicode("А")));

    Set letters_previos;
    Set letters;
    long long c;
    bool first_Word = 1;
    while(true) {
        c = To_Unicode();
        if (!IsSeparator(c) && first_Word) {
            if (IsIn(consonant, c)) {
                Add(&letters_previos, c);
            } else {
                continue;
            }
        } else if (IsSeparator(c) && first_Word) {
            first_Word = 0;
        } else if (!IsSeparator(c) && !first_Word) {
            if (IsIn(consonant, c)) {
                Add(&letters, c);
            } else {
                continue;
            }
        } else if (IsSeparator(c) && !first_Word){
            letters_previos &= letters;
            Clear(&letters);
        }
        if (c == 255) { //eof
            break;
        }

    }
    if (letters_previos != 0) {
        printf("YES");
    } else {
        printf("NO");
    }
    return 0;
}
