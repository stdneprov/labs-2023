#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    char c;
    bool is_lower = true;
    bool is_word = false;
    int res = 0;
    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (is_lower && is_word) {
                res++;
            }
            is_lower = true;
            is_word = false;
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
