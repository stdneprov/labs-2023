#include <stdio.h>
#include <stdlib.h>


int main() {

    int maxn = 20;
    int matrix[maxn][maxn];

    char c = ' ';

    // прога очень чувствительна к формату ввода
    // числа в строке разделены ОДНИМ пробелом, лишних пробелов в начале и конце строк быть НЕ ДОЛЖНО
    // после последнего числа в строке идет ОДИН перенос строки
    // в конце и в начале НЕ ДОЛЖНО БЫТЬ пустых строк
    // то есть например:

    //11 12 13 14\n
    //21 22 23 24\n
    //31 32 33 34\n
    //41 42 43 44EOF

    // спасибо за понимание

    int i, j;
    i = 0;
    while (c != EOF) { 
        j = 0;
        c = ' ';
        while (c != '\n' && c != EOF) {
            scanf("%d", &matrix[i][j]);
            c = getchar();
            ++j;
        }
        ++i;
    }

    for (int k = 1; k < (i + 1) / 2 + 1; ++k) {


        int n = i-k, m = i-k;

        while (n >= k - 1) {
            
            printf("%d ", matrix[n][m]);
            --n;
        }
        ++n;
        --m;

        while (m >= k - 1) {

            printf("%d ", matrix[n][m]);
            --m;
        }
        ++m;
        ++n;

        while (n <= i - k) {

            printf("%d ", matrix[n][m]);
            ++n;
        }
        --n;
        ++m;

        while (m < i - k) {

            printf("%d ", matrix[n][m]);
            ++m;
        }
    }
    
    return 0;
}
