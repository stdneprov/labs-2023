#include <stdio.h>

int Reverse(int x) {
    int ans = 0;
    while (x > 0) {
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    return ans;
}


int IncrEven(int x) {
    int ans = 0;
    int sign = x > 0 ? 1 : -1;
    x = x * sign;
    while (x > 0) {
        ans *= 10;
        if ((x % 10) % 2 == 0) {
            ans += x % 10 + 1;
        } else {
            ans += x % 10;
        }
        x /= 10;
    }
    return Reverse(ans) * sign;
}

int main(void) {
    int a;
    while (scanf("%d", &a) == 1) {
        printf("%d\n", IncrEven(a));
    }
}