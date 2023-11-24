#include <stdio.h>
#include <math.h>

int ED(int a) {
    int m, i = 0;
    if (a > 0) {
        a = a * 10 + 1;
        m = a;
        while (m > 0) {
            m /= 10;
            i++;
        }
        a += pow(10, i);
    }
    if (a < 0) {
        a *= -1;
        a = a * 10 + 1;
        m = a;
        while (m > 0) {
            m /= 10;
            i++;
        }
        a += pow(10, i);
        a *= -1;
    }
    if (a == 0) {
        a += 101;
    }
    return a;
}

int main() {
    int a;
    while (scanf("%d", &a) == 1) {
        printf("%d\n", ED(a));
    }
    
    return 0;
}