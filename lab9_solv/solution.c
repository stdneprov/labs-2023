#include <stdio.h>
#include <math.h>

#define START_X 7
#define START_Y -4
#define USELESS_L -10


int Sign(int a) {
    if (a > 0) {
        return 1;
    } else if (a == 0) {
        return 0;
    } else {
        return -1;
    }
}

int Mod(int n, int d) {
    int result = n % d;
    if (Sign(result) * Sign(d) < 0)
        result += d;
    return result;
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

int Min(int a, int b) {
    return (a < b) ? a : b;
}


double Distance(int x1, int y1, int x2, int y2) {
    double ans;
    ans = pow(pow((x1 - x2), 2) + pow((y1 - y2), 2), 0.5);
    return ans;
}

int CheckFrstCircle(int x, int y) {
    return Distance(x, y, -10, -10) < 10.0;
}

int CheckScndCircle(int x, int y) {
    return Distance(x, y, -20, -20) < 10.0;
}

int CheckPoint(int x, int y) {
    return (CheckFrstCircle(x, y) && CheckScndCircle(x, y));
}

int main() {
    int i = START_X, j = START_Y, l = USELESS_L;
    int oldX, oldY, oldL;
    for (int k = 1; k <= 50; ++k) {
        oldX = i;
        oldY = j;
        oldL = l;
        i = Mod(Max(Mod(47 * i, 25), Min(Mod(47 * j, 30), Mod(47 * l, 30))) - (k - 1), 15);
        j = Mod(Min(Max(Mod(47 * oldX, 25), Mod(47 * oldY, 25)), Mod(47 * oldL, 30)) + (k - 1), 5);
        l = Mod(47 * oldX * oldY * oldL, 25) + Mod((k - 1), 5);
        if (CheckPoint(i, j)) {
            printf("YES %d, x = %d, y = %d, l = %d\n", k, i, j, l);
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
