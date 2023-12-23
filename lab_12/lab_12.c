#include <stdio.h>
#include <stdbool.h>

int main(){
    long long a;
    while (scanf("%lld", &a)){

        long long ans = 0;
        int sign = a > 0 ? 1 : -1;
        a *= sign;
        long long power = 1;
        while (a >= 10){
            ans += (a % 10) * power;
            power *= 10;
            a /= 10;
        }
        ans = ans * 10 + a;
        if (sign == 1){
            printf("%lld\n", ans);
        }
        else{
            printf("-%lld\n", ans);
        }
    }

}

