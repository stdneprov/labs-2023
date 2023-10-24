#include <stdio.h>
#include <math.h>
#define START_X 7
#define START_Y -4
#define USELESS_L -10


int Sign(int a){
    if (a > 0){
        return 1;
    }
    else if(a == 0){
        return 0;
    }
    else{
        return -1;
    }
}

int Mod(int n, int d){
    int result = n % d;
    if (Sign(result) * Sign(d) < 0)
        result += d;
    return result;
}

int Max(int a, int b){
    if (a > b)
        return a;
    else
        return b;
}

int Min(int a, int b){
    if (a < b)
        return a;
    else
        return b;
}


double Distance(int x1, int y1, int x2, int y2)
{
    double ans;
    ans = pow(pow((x1 - x2), 2) + pow((y1 - y2), 2), 0.5);
    return ans;
}

int Check_frst_circle(int x, int y)
{
    if (Distance(x, y, -10, -10) < 10.0)
        return 1;
    else
        return 0;
}

int Check_scnd_circle(int x, int y)
{
    if (Distance(x, y, -20, -20) < 10.0)
        return 1;
    else
        return 0;
}

int Check_point(int x, int y){
    if (Check_frst_circle(x, y) && Check_scnd_circle(x, y))
        return 1;
    else
        return 0;
}

int main()
{
    int i = START_X, j = START_Y, l = USELESS_L;
    int old_x, old_y, old_l;
    for (int k = 1; k <= 50; ++k){
        old_x = i;
        old_y = j;
        old_l = l;
        i = Mod(Max(Mod(47 * i, 25), Min(Mod(47 * j, 30), Mod(47 * l, 30))) - (k - 1), 15);
        j = Mod(Min(Max(Mod(47 * old_x, 25), Mod(47 * old_y, 25)), Mod(47 * old_l, 30)) + (k - 1), 5);
        l = Mod(47 * old_x * old_y * old_l, 25) + Mod((k - 1), 5);
        if (Check_point(i, j)){
            printf("Yes time = %d, x = %d, y = %d, l = %d\n", k, i, j, l);
            return 0;
        }
    }
    printf("No\n");
    return 0;

}