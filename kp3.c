#include <stdio.h>

#define A 0.0
#define B 2.0
#define STEP 0.05

long double MachineEpsilon() {
    long double e = 1.0l;
    while (1.0l + e * 0.5l > 1.0l) {
        e *= 0.5l;
    }
    return e;
}

int main() {
    long double e = -MachineEpsilon();
    long double item;
    long double summa;
    int k;
    printf("  x  |             sum              |             func             | iter\n");
    for (long double i = A; i <= B + STEP; i += STEP) {
        item = -1.0l / 5.0l;
        summa = item;
        k = 0;
        while ((k < 100) && (item < e)) {
            item *= (2.0l * i) / 5.0l;
            summa += item;
            k++;
        }
        long double func = 1.0l / (2.0l * i - 5.0l);
        printf("%.2Lf | %.25Lf | %.25Lf | %d \n", i, summa, func, k);
    }
    return 0;
}