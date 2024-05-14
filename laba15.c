#include <stdio.h>

const int maxn = 7;

int main(){
    int matrix[maxn * maxn];
    int answerMatrix[maxn * maxn];
    int n;
    int shift = 13;
    scanf("%d", &n);
    for (int i = 0; i < n * n; ++i){
        scanf("%d", matrix + i);
    }
    for (int i = 0; i < n * n; ++i){
        answerMatrix[(i + shift) % (n * n)] = matrix[i];
    }
    printf("%c", '\n');
    for (int i = 0; i < n * n; ++i){
        printf("%d ", answerMatrix[i]);
        if ((i + 1) % n == 0){
            printf("%c", '\n');
        }
    }
    return 0;
}
