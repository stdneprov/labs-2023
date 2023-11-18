#include <stdio.h>

int CheckIncrease(long long x){
    int prev = 10;
    int curr;
    int sign = x > 0 ? 1: -1;
    x *= sign;
    while (x > 0){
        curr = x % 10;
        x /= 10;
        if (curr <= prev){
            prev = curr;
        } else{
            return 0;
        }
    }
    return 1;
}

int main(){
    long long a;
    while(scanf("%lld", &a) == 1){
        printf("%d", CheckIncrease(a));
    }
    return 0;
}