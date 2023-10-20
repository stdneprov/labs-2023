#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define I_START -25
#define J_START -9
#define L_START -8

// int first_mod(int x, int y) {
//     int ans = x % y;
//     if (x < 0 & y > 0 & ans != 0) {
//         ans = y + ans;
//     }
//     if (y < 0 & x > 0 & ans != 0) {
//       ans = y+ ans;
//     }
//     return ans;
// }

int mod(int x, int y) {
    return (y + (x % y)) % y;
}

int sign(int x) {
    if (x > 0) {
        return 1;
    }
    if (x < 0) {
        return -1;
    }
    return 0;
}


int main() {
    int i = I_START;
    int j = J_START;
    int l = L_START;
    int iNew, jNew, lNew;
    for (int k = 1; k < 51; k++) {
        iNew = mod((abs(i - j) * l - abs(j - l) * i + abs(i - l) * j), 20) - k;
        jNew = mod(fmin(i, j) * fmax(j, l) * fmin(i, l), 25) + 5 * sign(i) + k;
        lNew = abs(l) * sign(i - j) - abs(i) * sign(j - l) + abs(j) * sign(i - l);
        i = iNew;
        j = jNew;
        l = lNew;
        if ((j <= (-i - 10)) & (j >= (-i - 20))) {
            printf("YES %d: (%d, %d)", k, i, j);
            return 1;
        }
    }
    printf("NO: (%d, %d)", i, j);
    return 1;
}