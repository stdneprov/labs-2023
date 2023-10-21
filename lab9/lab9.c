#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int Mod (int a, int b){
    return ((a % b) + b) % b;
}

int main() {
    int i0 = 13, j0 = -9, l0 = 4;
    for (int k = 0; k <= 51; k++) {
        i0 = Mod((i0 + j0), 30) / (Mod(abs(l0), 20) + 1) + (Mod((i0 + l0), 30)) / (Mod(abs(j0), 5) + 1);
        j0 = Mod(fmax(k * i0, (k + 1) * j0), 25) - abs(j0 - l0) / 10;
        l0 = abs(j0 - l0) / 10 + fmin(Mod((i0 + l0), 20), Mod(j0 * k, 20)) - 10;
        if (k == 51){
            printf("NO\n");
            break;
        } else if (((i0 + 10) * (i0 + 10) + (j0 + 10) * (j0 + 10) <= 100) && ((i0 + 20) * (i0 + 20) + (j0 + 20) * (j0 + 20) <= 100)){
            printf("YES %d\n", k);
            break;
        }
    }
    return 0;
}
