#include <stdio.h>
#include <math.h>

// void BuildGraph(FILE *gnupipe, unsigned long long int m, unsigned long long int n){
//     fprintf(gnupipe, "reset\n");
//     fprintf(gnupipe, "set title \"Graph\"\n");
//     fprintf(gnupipe, "set parametric\n");
//     fprintf(gnupipe, "set size square\n");
//     fprintf(gnupipe, "set xrange [0:%Lu]\n", m);
//     fprintf(gnupipe, "set yrange [0:%Lu]\n", n);
//     fprintf(gnupipe, "plot 'bildata.txt'with linespoints\n");
// }

int main(){
    // FILE *bdt = NULL;
    // FILE *gn = NULL;

    // bdt = fopen("bildata.txt", "w");
    // gn = popen("gnuplot -persistent", "w");
    
    unsigned long long int m, n, i, j;
    int k;
    
    while (scanf("%Lu %Lu %Lu %Lu %i", &m, &n, &i, &j, &k) != EOF){
        unsigned long long int posX = i, posY = j, count = 0;
        int dir = k;
        int f = 1;

        // fprintf(bdt, "%Lu %Lu\n", posX, posY);

        while (!(posX == i && posY == j && dir == k) || f){
            f = 0;

            if (dir == 1){
                ++posX;
                ++posY;
            } else if (dir == 2){
                ++posX;
                --posY;
            } else if (dir == 3){
                --posX;
                --posY;
            } else {
                --posX;
                ++posY;
            }

            // fprintf(bdt, "%Lu %Lu\n", posX, posY);

            if (posX == m || posX == 0){
                if (posX == 0 && posY == 0){
                    printf("%Lu левый нижний\n", count);
                    break;
                } else if (posX == m && posY == 0){
                    printf("%Lu правый нижний\n", count);
                    break;
                } else if (posX == m && posY == n){
                    printf("%Lu правый верхний\n", count);
                    break;
                } else if (posX == 0 && posY == n){
                    printf("%Lu левый верхний\n", count);
                    break;
                }

                if (dir == 1){
                    dir = 4;
                } else if (dir == 4){
                    dir = 1;
                } else if (dir == 2){
                    dir = 3;
                } else{
                    dir = 2;
                }

                ++count;

            } else if (posY == n || posY == 0){
                if (dir == 1){
                    dir = 2;
                } else if (dir == 2){
                    dir = 1;
                } else if (dir == 3){
                    dir = 4;
                } else{
                    dir = 3;
                }

                ++count;
            }
        }

        if (posX == i){
            printf("%Lu\n", count);
        }
    }

    // BuildGraph(gn, m, n);

    return 0;
}