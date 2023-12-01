#include <stdio.h>

int decrement(int x){
    if (x % 2 == 0 && x != 0)
        return --x;
    else
        return x;
}

int main() {
    int number;
    int null = 0;
    while (scanf("%d", &number) == 1) {
        int dec = 0;
        int result = 0;
        while (number > 0){
            int digit = number % 10;
            number /= 10;
            dec = dec * 10 + decrement(digit);
            if (dec == 0)
                null++;
        }
        while (dec > 0) {
            int digit = dec % 10;
            dec /= 10;
            result = result * 10 + digit;
        }
        printf("%d", result);
        for (int i=0; i < null; ++i) {
            printf("0");
        }
        printf(" ");
        null = 0;
    }
    return 0;
}