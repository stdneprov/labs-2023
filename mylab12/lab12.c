#include <stdio.h>

int Abs (int a) {
    return a > 0 ? a : -a;
}

int CheckForParityOfDigitsNumber (int a) {
    int count = 0;
    while (a != 0) {
        a /= 10;
        count += 1;
    }
    if (count % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int DiffOfEveryTwoDigits (int a) {
    int answer = 0;
    int discharge = 10;
    int dischargeForDiff = 1;
    if (a < 0) {
        a *= -1;
    }
    if (CheckForParityOfDigitsNumber(a) == 1) {
        while (a != 0) {
            answer += Abs((a % 10) - ((a % 100) / 10)) * dischargeForDiff;
            dischargeForDiff *= 1000;
            answer += (a % 100) * discharge;
            discharge *= 1000;
            a /= 100;
        }
    } else {
        int buff = 0;
        buff += a % 10;
        a /= 10;
        while (a != 0) {
            answer += Abs((a % 10) - ((a % 100) / 10)) * dischargeForDiff;
            dischargeForDiff *= 1000;
            answer += (a % 100) * discharge;
            discharge *= 1000;
            a /= 100;
        }
        answer = answer * 10 + buff;
    }
    
    return answer;
}


int main(void) {
    int a;
    while (scanf("%d", &a) == 1) {
        if (a < 0) {
            printf("%d\n", -1 * DiffOfEveryTwoDigits(a));
        } else {
            printf("%d\n", DiffOfEveryTwoDigits(a));
        }
    }

    return 0;
}
