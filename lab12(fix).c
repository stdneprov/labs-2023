#include <stdio.h>
#include <stdbool.h>

int IsNegative(int num) {
    return num < 0 ? true : false;
}

int ReverseCode(int num) {
    int reversedNum = 0;
    int razr = 1;
    num *= -1;
    while (num != 0) {
        reversedNum += (9 - num % 10) * razr; 
        razr *= 10;
        num /= 10;
    }
    return reversedNum;
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
