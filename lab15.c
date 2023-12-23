#include <stdio.h> 

int main() { 
    int n; 
    scanf("%d",&n); 
    if (n > 7) { 
        printf("Размер матрицы не соответствует условиям задачи\n"); 
    } 
    else { 
        int mat[n][n], i, j; 
        for (i = 0; i < n; i++) { 
            for (j = 0; j < n; j++) { 
                scanf("%d",&mat[i][j]);  
            } 
        } 

        int sum, z, d; 
        for (i=0; i < n; i++) { 
            sum=mat[i][i]; 
            j = i; 
            int s = i,p = j; 
            while ((s - 1) >= 0 && (p + 1) < n) {
                s -= 1;
                p += 1;
                sum += mat[s][p];
            } 
            s = i;p = j; 
            while ((s + 1) < n && (p - 1) >= 0) {
                s += 1;
                p -= 1;
                sum += mat[s][p];} 
                if (sum != 0) {
                    mat[i][j] = sum;
                } 
        } 

        for (z = 0; z < n; z++){ 
            for (d = 0; d < n; d++) { 
                printf("%d ",mat[z][d]); 
            } 
            printf("\n"); 
        } 
    }
    return 0;
}