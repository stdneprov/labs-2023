#include <stdio.h>
#define LENGHT 10.0
#define HEIGHT 5.0
#define SQ(a) ((a) * (a))

int Sign(int a) {
    return a == 0 ? 0 : a > 0 ? 1 : -1;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int Abs(int a) {
    return a < 0 ? -a : a;
}

int Mod(int a, int b) {
    return ((a % b) >= 0 ? a % b : b + (a % b));
}

int InEllipse(int i, int j) {
    return (SQ(i-20) / SQ(LENGHT) + SQ(j) / SQ(HEIGHT)) <= 1;
}

int main() {
    int flag = 0;
    int i = -24;
    int j = 4;
    int l = -3;
    for (int k = 0; k <= 50; k++) {
        int nextI = Mod(Abs((i + k) * (j + 2 * k) * (l + 3 * k)), 35);
        int nextJ = Sign(Max(i, j)) * Min(Mod((i + k), 20), Mod((j + l), 20));
        int nextL = i / 3 - Abs(i - k) * Sign(l - j);
        if (InEllipse(nextI, nextJ) == 1) {
            flag = 1;
            printf("YES %d %d %d %d\n", k, nextI, nextJ, nextL);
            break;
        }
        i = nextI;
        j = nextJ;
        l = nextL;
    }
    if (flag == 0) printf("NO");
    return 0;
}
