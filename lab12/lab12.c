#include <stdio.h>

int Reverse(int a){
    int rem = a;
    int rev = 0;
    while (a > 0){
        rem = a % 10;
        rev = rev * 10 + rem;
        a /= 10;
    }
    return rev;
}

void Change(int b){
    int c = Reverse(b);
    if (c < 0){
        c *= -1;
    }
    while (c > 0){
        if ((c % 10) > 7){
            printf("1%d", (c % 10 % 8));
        }
        else{
            printf("0%d", (c % 10));
        }
        c /= 10;
    }
    printf("\n");
}

int main() {
    int c;
    while (scanf("%d",  &c) == 1) {
        Change(c);
    }
    return 0;
}
