#include <stdio.h>

const int maxn = 7;

int main(){
    int matrix[maxn * maxn];
    int answer[maxn * maxn];
    int indForAnswer = 0;
    int ind = 0;
    int toCorner = 0;
    int step = 1;
    int amountStep = 0;
    int stateDirection = 0; 
    /*
     0 - состояние для единоразового перехода между столбцами
     1 - состояние для перехода вниз до диагонали
     2 - состояние для перехода влево от диагонали
     3 - состояние для единоразового перехода между строками
     4 - состояние для перехода вправо до диагонали
     5 - состояние для перехода вверх от диагонали
    */
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n * n; ++i){
        scanf("%d", matrix + i);
    }
    printf("%c", '\n');
    while (1)
    {
        if (toCorner >= n){
            break;
        }
        printf("%d ", matrix[ind]);
        answer[indForAnswer] = matrix[ind];
        indForAnswer += 1;
        ind += step;
        if (stateDirection == 0){
            stateDirection = 1;
            step = n;
            toCorner += 1;
            amountStep = 0;
        }
        else if (stateDirection == 1){
            if (amountStep == toCorner){
                stateDirection = 2;
                step = -1;
                amountStep = 0;
            }
        }
        else if (stateDirection == 2){
            if (amountStep == toCorner){
                stateDirection = 3;
                step = n;
                amountStep = 0;
            }
        }
        else if (stateDirection == 3){
            stateDirection = 4;
            step = 1;
            toCorner += 1;
            amountStep = 0;
        }
        else if (stateDirection == 4){
            if (amountStep == toCorner){
                stateDirection = 5;
                step = -n;
                amountStep = 0;
            }
        }
        else if (stateDirection == 5){
            if (amountStep == toCorner){
                stateDirection = 0;
                step = 1;
                amountStep = 0;
            }
        }
        amountStep += 1;
    }
    
    return 0;
}
