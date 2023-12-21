#include <stdio.h>

int main(void) {
    int a;
    while (scanf("%d", &a) == 1) {
        if (a % 2 == 0) {
            printf("%d\n", a + 1);
        } else {
            printf("%d\n", a);
        }
    }
    return 0;
}
