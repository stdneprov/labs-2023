#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    char c;
    bool is_lower = true;
    bool is_word = false;
    int res = 0;
    while (true) {
        c = getchar();
        if (isspace(c) || c == EOF) {
            if (is_lower && is_word) {
                res++;
            }
            is_lower = true;
            is_word = false;
            if (c == EOF) {
                break;
            }
            continue;
        }
        if (islower(c)) {
            is_word = true;
        } else {
            is_lower = false;
        }
    };
    printf("%d \n", res);
    return 0;
}
