#include <stdio.h>
#include <stdbool.h>

int IsNegative(int num) {
    return num < 0 ? true : false;
}

int ReverseCode(int num) {
    int ReversedNum = 0;
    int razr = 1;
    num *= -1;
    while (num != 0) {
        ReversedNum += (9 - num % 10) * razr; 
        razr *= 10;
        num /= 10;
    }
    return ReversedNum;
}

int main() {
    while(true) {
        int num;
        scanf("%d", &num);
        if (IsNegative(num)) {
            num = ReverseCode(num); //вычисление обратного кода для отриц числа
            num += 1; //добавление единицы для дополнительного кода
        }
        printf("%d\n", num);
        if (num == EOF) {
            break;
        }
    }
}
