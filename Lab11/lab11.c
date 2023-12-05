#include  <stdio.h>

int main() {
    char c;
    int first = 1; 
    while ((c = getchar()) != EOF) {
        if (first) {
            putchar(' ');
            first = 0;
        }
        else if (c == '\n') {
            putchar(' ');
            first = 1;
        }
        putchar(c);
    }
    putchar(' ');
    return 0;
}
