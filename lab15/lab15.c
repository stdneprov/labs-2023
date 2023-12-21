#include <stdio.h>

const int maxN = 100;

void Add(int *mother, int *baby, int string, int lenBaby, int lenMother) {
    for (int i = 0; i < lenMother; ++i) {
        baby[lenBaby * lenMother + i] = mother[string * lenMother + i];
    }
}

int CheckMatch(int *mother, int *baby, int motherStr, int babyStr, int lenght) {
    for (int i = 0; i < lenght; ++i) {
        if (mother[motherStr * lenght + i] != baby[babyStr * lenght + i]) {
            return 0;
        }
    }
    return 1;
}

int CheckUniq(int *mother, int *baby, int string, int lenBaby, int lenMother) {
    for (int i = 0; i < lenBaby; ++i) {
        if (CheckMatch(mother, baby, string, i, lenMother)) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int len = 0;
    int massive[maxN * maxN];
    int *ptr = massive;
    while (scanf("%d", ptr++) != EOF) {
        if (len * len < (ptr - massive)) {
            ++len;
        }
    }
    ptr = massive;
    int ans[len * len];
    int lenBaby = 0;
    int *ansPtr = ans;
    for (int i = 0; i < len; ++i) {
        if (CheckUniq(ptr, ansPtr, i, lenBaby, len)) {
            Add(ptr, ansPtr, i, lenBaby, len);
            ++lenBaby;
        }
    }
    for (int i = 0; i < lenBaby; ++i) {
        for (int j = 0; j < len; ++j) {
            printf("%d ", ans[i * len + j]);
        }
        printf("\n");
    }
    return 0;
}
