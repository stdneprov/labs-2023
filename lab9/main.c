#include <stdio.h>
#include <stdlib.h>
#define START_POS_X -1
#define START_POS_Y -1
#define START_MOTION_PARAM_L -9

// void BuildGraph(FILE *gnupipe){
//     fprintf(gnupipe, "reset\n");
//     fprintf(gnupipe, "set title \"Graph\"\n");
//     fprintf(gnupipe, "set parametric\n");
//     fprintf(gnupipe, "set size square\n");
//     fprintf(gnupipe, "set xrange [-10:50]\n");
//     fprintf(gnupipe, "set yrange [-10:50]\n");
//     fprintf(gnupipe, "plot 'data.txt'with linespoints, [t=0:2*pi] sin(t)*10+10,cos(t)*10+10, [t=0:2*pi] sin(t)*5+10,cos(t)*5+10\n");
// }

long long Max(long long a, long long b){
    return a >= b ? a : b;
}

long long Min(long long a, long long b){
    return a < b ? a : b;
}

long long Mod(long long a, long long b){
    if (b == 0){
        return 1 / 0; 
    }
    
    if (b < 0){
        a = -a;
        b = -b;
    }

    if (a >= 0){
        while (a >= b){
            a -= b;
        }
    } else {
        while (a < 0){
            a += b;
        }
    }

    return a;
}

int Sign(long long a){
    return a >= 0 ? 1 : -1;
}

int main(){
    long long i = START_POS_X, j = START_POS_Y, l = START_MOTION_PARAM_L;    
    long long prevI, prevJ, prevL;

    // FILE *data = NULL;
    // FILE *gn = NULL;

    // data = fopen("data.txt", "w");
    // gn = popen("gnuplot -persistent", "w");

    // fprintf(data, "%lld %lld\n", i, j);

    for (int k = 0; k < 50; ++k){
        prevI = i;
        prevJ = j;
        prevL = l;
        
        i = Mod(Max(prevJ - k, prevL - k), 30) + Mod(Max(prevI + prevL, prevJ + k), 20);
        j = Mod(abs(prevI - prevL) * Sign(prevJ + k) + abs(prevI - k) * (prevJ + k), 20);
        l = Mod((prevI + k) * (prevJ - k) * (prevL + k), 25);

        // fprintf(data, "%lld %lld\n", i, j);

        if ((i - 10) * (i - 10) + (j - 10) * (j - 10) <= 100 && (i - 10) * (i - 10) + (j - 10) * (j - 10) >= 25){
            
            printf("YES %d\n", k + 1);
            // BuildGraph(gn);
            return 0;
        }
    }

    printf("%s\n", "NO");
    // BuildGraph(gn);
    return 0;
}