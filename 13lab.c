#include <stdio.h>
#include <wctype.h>
#include <wchar.h>

#define VOWELS L"аеиоуыэюя"

typedef long long Set;

void AddInMass(Set* m, wchar_t c) {
    if (iswupper(c)) {
        c = towlower(c);
    }
    if (wcschr(VOWELS, c) != NULL) {
        *m |= 1llu << (c - L'а');
    }
}

int IsSeparator(wchar_t c) {
    return (c == L' ') || (c == L',') || (c == L'\n') || (c == L'\t') || (c == WEOF);
}

int main() {
    int end = 0;
    Set m = 0;
    while (1) {
        wchar_t c = getwchar();
        if (c == WEOF) {
            break;
        }
        if (!IsSeparator(c)) {
            Set prevm = m;
            AddInMass(&m, c);
            if ((m & prevm) != 0) {
                printf("YES");
                end = 1;
                break;
            }
        } else {
            m = 0;
        }
    }
    if (end == 0) {
        printf("NO");
    }
    return 0;
}