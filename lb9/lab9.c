#include <stdio.h>
#include <stdlib.h>

int Max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int Min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int Hit(int x, int y){
    x -= 10;
    y -= 10;
    if (x * x + y * y <= 100 && x * x + y * y >= 25){
        return 1;
    }
    return 0;
}

int Sign(int x){
    if (x > 0){
        return 1;
    } else if(x == 0){
        return 0;
    } else {
        return -1;
    }
}

int Mod(int a, int n){
    return ((a % n) + n) % n;
}

int main(void){
    int i = 18, j = -9,l = 5, text = 0;
    for (int k = 1; k < 51; k++) {
        int lastI = i, lastJ = j;
        i = Mod(lastI * Max(lastJ, l), 30) + Mod(lastJ * Min(lastI, l), 20) + k;
        j = Min(lastI, Max(lastJ, Min(l, Max(lastI - l, lastJ - l))));
        l = Sign(k - 10) * abs(lastI - lastJ + l - k);

        if (Hit(i, j) == 1){
            text = k;
            break;
        }
    }
    
    if (text > 0){
        printf("YES %d\n", text);
    } else{
        printf("NO");
    }
    return 0;
}
