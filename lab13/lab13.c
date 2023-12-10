#include <stdio.h>
#include <stdbool.h>

typedef long long Set;

int IsSeparated(char c) {
    return (c == ' ' || c == ',' || c == '\n' || c == EOF || c == '\t');
}



int Rus(int c) {
    if (c == 1025 || c == 1105) {
        return 33;
    } else if (c < 1040) {
        return 0;
    } else if (c >= 1040 && c < 1072) {
        return c - 1039;
    } else if (c >= 1072 && c < 1104) {
        return c - 1071;
    } else {
        return 0;
    }
}

void Add(Set *a, char c) {
    *a |= (1 << (c - 1));
}


bool Include(Set a, Set b) {
    return (b & a) == a;
}

int GlueByte(char a) {
    int newSym = 0;
    if ((a & (1 << 7)) == 0) {
        return a;
    } else if ((a & (1 << 5)) == 0) {
        newSym = (a & ~(-1 << 5));
        newSym = newSym << 6;
        int c = getchar();
        newSym |= (c & ~(-1 << 6));
        return newSym;
    } else if ((a & (1 << 4)) == 0) {
        newSym = a & ~(-1 << 4);
        int c = getchar();
        newSym = newSym << 6;
        newSym |= c & (-1 << 6);
        c = getchar();
        newSym = newSym << 6;
        newSym |= c & (-1 << 6);
        return newSym;
    } else if ((a & (-1 << 3)) == 0) {
        newSym = a & ~(-1 << 3);
        int c = getchar();
        newSym = newSym << 6;
        newSym |= c & (-1 << 6);
        c = getchar();
        newSym = newSym << 6;
        newSym |= c & (-1 << 6);
        c = getchar();
        newSym = newSym << 6;
        newSym |= c & (-1 << 6);
        return newSym;
    }


}
int main() {
    Set glas = 8187822369;  //  111101000000010000100000100100001 - гласные
    Set alf = 0;            //  ёяюэьыъщшчцхфутсрпонмлкйизжедгвба glas & alf == alf
    bool allGlas = 0;
    while (1) {           
        char c = getchar();
        if (!IsSeparated(c)) {
            int a = GlueByte(c);
            Add(&alf, Rus(a));
        } else {
            if (((glas & alf) == glas) && (alf != 0)) {
                allGlas = 1;
            }
            alf = 0;
        }
        if (c == EOF) {
            printf("%d", allGlas);
            break;
        }
    }
}