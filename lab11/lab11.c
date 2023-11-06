#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

bool isSeparator(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '.' ||
           c == EOF;
}

int main(void) {
    char c;
    bool is_lower = true;
    bool is_word = false;
    int res = 0;
    while (true) {
        c = getchar();
        if (isSeparator(c)) {
            res += is_lower && is_word;
            is_lower = true;
            is_word = false;
        } else if (islower(c))
            is_word = true;
        else
            is_lower = false;

        if (c == EOF)
            break;
    };
    printf("%d \n", res);
    return 0;
}
