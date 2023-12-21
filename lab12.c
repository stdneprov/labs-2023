
#include <stdio.h>
#include <stdlib.h>
//выбрать цифры равные модулю разности двух предыдущих


int main() {
    long long a;
    while (scanf("%lld", &a) == 1) {
        
        int a3 = a % 10;
        a = a / 10;
        int a2 = a % 10;
        a = a / 10;
        int a1 = a % 10;
        while (a != 0) {
            if (a3 == a1 - a2 || a3 == a2 - a1) { //цифры, равные модулю разности двух предыдущих
                printf("%d ", a3);
            }
            a = a / 10;
            a3 = a2;
            a2 = a1;
            a1 = a % 10;
        }
        
        printf("\n"); 
    }


}