#include <stdio.h>
int main(void) {
    
    int x;
    scanf("%d", &x);
    
    if (x < 10) {
        if (x == 3) {
            printf("yes");
        }
        else {
            printf("no");
        }
    }
    else {
        if (x % 10 == 3) {
            printf("yes");
        }
        else {
            printf("no");
    
        }
    }
}
