#include <stdio.h>


int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int max, min;
    int summator = 1, summatorMax = 0, summatorMin = 0;
    for (int i = 0; i < n; i++) {
        summator = 1;
        for (int j = 0; j < n; j++){
            summator *= matrix[i][j];
        }
        if ((summator == summatorMax) && (summator == summatorMin)){
            max = i;
            min = i;
        }
        else if (summator > summatorMax){
            summatorMax = summator;
            max = i;
        }
        else if ((summator < summatorMin) && (summator < summatorMax)){
            summatorMin = summator;
            min = i;
        }
        
    }
    printf("\n");
    int change_max[n];
    for (int a = 0; a < n; a++){
        change_max[a] = matrix[max][a];
        matrix[max][a] = matrix[min][a];
    }
    for (int b = 0; b < n; b++){
        matrix[min][b] = change_max[b];
    }  
    for(int ii = 0; ii < n; ii++){
        for(int jj = 0; jj < n; jj++){
            printf("%d ", matrix[ii][jj]);
        }
        printf("\n");
    }
    
}
