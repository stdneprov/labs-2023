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
            if (digit + null + dec == 0)
                null++;
            else
                dec = dec * 10 + decrement(digit);
        }
        while (dec > 0) {
            int digit = dec % 10;
            dec /= 10;
            result = result * 10 + digit;
        }
        if (null == 0)
            printf("%d ", result);
        else
            printf("%d0 ", result);
        null = 0;
    }
    return 0;
}