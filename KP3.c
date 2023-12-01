//запускать с -lm в конце, чтобы связать с мат библиотекой, иначе ругается
#include <stdio.h>
#include <math.h>


long double MachineEpsilon() {
    long double e = 1.0l;
    while (1.0l + e * 0.5l > 1.0l) {
        e *= 0.5l;
    }
    return e;
}

void Head() {
    printf("|x     |res                          |func                         |iter|");
    printf("\n");
    printf("|------|-----------------------------|-----------------------------|----|");
    printf("\n");
}

int main() {
    Head();
    long double e = MachineEpsilon();
    long double value;
    long double result;
    long double start = 0.0;
    long double st = 0.05;
    long double end = 1.0 + st;
    for (long double x = start; x <= end; x += st) {
		long long counter = 1;
		value = 1.0l;
		result = value;
		while ((counter < 10000) && (value >= e)) {
			value *= (logl(3.0l) * x) / counter;
			result += value;
			counter++;
		}
        long double res = expl(logl(3.0l) * x);
        printf("| %.2Lf | %.25Lf | %.25Lf | %2lld |\n", x, result, res, counter - 1);
    }
    return 0;
}
