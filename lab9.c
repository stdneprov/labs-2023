#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

#define I0 29
#define J0 15
#define L0 10

int Mod(int x, int y) {
    int k = ((x % y) + y) % y; //остаток от деления //
    return k;
}

int Max(int a, int b){
    return a > b ? a : b; //поиск максимального
}

int Min(int a, int b){
    return a < b ? a : b; //поиск минимального

}

int main(){
    int i = I0, j = J0, l = L0; //начальные значения
    int flag = 0;

    for (int k = 0; k < 50; k++) { //переписываем условие
        int iNew = Mod(Min(Max(Min(i - j, i - l), j - l), i - k), 30);
        int jNew = Mod(Max(Min(Max(i - j, i - l), j - l), i - k), 30);
        int lNew = Mod(i, 30) - Mod(j, 30) + Mod(l, 30) - Mod(k, 30);


        i = iNew; //переписываем данные в переменные
        j = jNew;
        l = lNew;

        //проверка на попадание в область
        if (i >= -10 && (j >= i + 10) && (j <= -i + 10)){
            printf("YES %d\n", k);
            flag = 1;
            break;
        }


    }

    if (flag == 0){
        printf("NO\n");

    }
    return 0;
}

