// перенести первый блок нулей из младших разрядов в середину десятичной записи числа
#include <stdio.h>

int MoveNulls(int a);
int RemoveZeros(int zeroCount, int afterZerosCount, int a);
int ALength(int a);
int AddZerosInTheMiddle(int a, int aLength, int zeroCount);
long long NumPow(int number, int power);

int main() {
    int a;
    while (scanf("%d", &a) == 1) 
        printf("%d\n", MoveNulls(a));
    return 0;
}

int MoveNulls(int a) {
    int sign = a < 0 ? -1 : 1;
    a *= sign;
    int aCopy = a;
    // считаю нули и количество цифр после нуля
    int zeroCount = 0;
    int afterZerosCount = 0;
    while (aCopy != 0) {
        if ((aCopy % 100) != 0) {
            afterZerosCount++;
            aCopy /= 10;
        } else {
            int curNum = aCopy % 10;
            while (curNum == 0) {
                zeroCount++;
                aCopy /= 10;
                curNum = aCopy % 10;
            }
            break;
        }
    }
    // убираю блок нулей из числа
    a = RemoveZeros(zeroCount, afterZerosCount, a);
    
    aCopy = a;
    int aLength = ALength(a);
    // делю число пополам и соединяю уже с нулями в середине
    a = AddZerosInTheMiddle(a, aLength, zeroCount);

    return a * sign;
}

int RemoveZeros(int zeroCount, int afterZerosCount, int a) {
    int secondPart = a % NumPow(10, afterZerosCount);
    int firstPart = a / NumPow(10, afterZerosCount + zeroCount) * NumPow(10, afterZerosCount);
    return firstPart + secondPart;
}

int ALength(int a) {
    int aLength = 0;
    while (a != 0) {
        aLength++;
        a /= 10;
    }
    return aLength;
}

int AddZerosInTheMiddle(int a, int aLength, int zeroCount) {
    int secondHalf = a % NumPow(10, aLength / 2);
    int firstHalf = a / NumPow(10, aLength / 2) * NumPow(10, aLength / 2 + zeroCount);
    return firstHalf + secondHalf;
}

long long NumPow(int number, int power){
    long long curNum = number;
    if (power == 0)
        return 1;
    else {
        for (int i = 1; i < power; i++)
            curNum *= number;
        return curNum;
    }  
}
