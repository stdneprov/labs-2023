#include <stdio.h>
#include <math.h>

int Min(int a, int b){
    return a > b ? a : b;
}

int Max(int a, int b){
    return a < b ? a : b;
}

int Mod(int a, int b){
    return (a % b + b) % b;
}

int main(){
    int i = -22, j = 14, l = -14, k = 0, next_I, next_J;
    while (k <= 51){
        if (k == 51){
            printf("NO");
            break;
        }
        if ((i + j <= -10) && (i + j >= -20)){
            printf("YES %d\n", k);
            break;
        }
        next_I = i;
        next_J = j;
        i = Mod((next_I * Min(next_J,l) + next_J * Min(next_I,l) + k * k), 20);
        j = Mod(((Mod(next_I,10) - k) * (Mod(next_J,10) + k) * (Mod(l, 10) - k)),25);
        l = Max((Mod(Min(next_I + next_J,next_J + l), 25)), Mod(Max(next_I + l, next_J + k), 20)) + 10;
        k++;
    }
    return 0;
}