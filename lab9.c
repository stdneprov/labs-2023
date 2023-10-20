#include <stdio.h>
#include <stdlib.h>

#define i0 12
#define j0 4
#define l0 3
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define mod_fixed(a, b) (((a) >= 0) ? (a % b) : (b + (a % b)))

int main() {
    int i = i0, j = j0, l = l0;
    int flag = -1;
    int i_new, j_new;
    for(int k = 0; k <= 50; k++) {
        if(i + j <= -10 && i + j >= -20) {
            flag = k;
            break;
        }
        i_new = mod_fixed((i * j/(abs(l) + 1)) + (j * l/(abs(i) + 1)) + (i * l/(abs(j) + 1)), 30);
        j_new = mod_fixed(i * max(j, l), 20) + mod_fixed(j * max(i, l), 30) - k;
        l = mod_fixed(max(max(i*j, i*l), j*l), 30) + 20;
        i = i_new;
        j = j_new;
    }
    if (flag == -1) {
        printf("Miss, i = %d, j = %d, l = %d\n", i, j, l);
    }
    else {
        printf("Getting into the area at step %d, i = %d, j = %d, l = %d\n", flag, i, j, l);
    }
}