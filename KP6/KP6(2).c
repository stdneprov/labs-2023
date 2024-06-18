#include "s.h"
#include <string.h>

int main(int arg, char* argv[]){
    Table muf;
    double k;
    if (arg != 2){
        fprintf(stderr, "Wrong args");
        return 1;
    }
    FILE* in = fopen(argv[1], "rb");
    //printf("%lf\n", k);
    if (in == NULL){
        fprintf(stderr, "Wrong %s", argv[1]);
        return 2;
    }
    if (ferror(in) != 0) {
        fprintf(stderr, "Wrong in");
        return 3;
    }
    scanf("%lf", &k);
    printf("%lf\n", k);
    fseek(in, 0, SEEK_SET);
    while(fread(&muf, sizeof(Table), 1, in) == 1){       
        if (muf.gruppa == k) {
            printf("%d %s %d %s %s %s\n", muf.gruppa, muf.day, muf.number, muf.para, muf.room, muf.week);
        }
    }
    fclose(in);
    return 0;
}