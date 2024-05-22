#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "funcs.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printfError("Неправильное количество аргументов.", 1);
    }

    FILE* src = fileOpen(argv, 1, "rb");
    User f;
    int needSubs = atoi(argv[2]);

    while((fread(&f, sizeof(User), 1, src))) {
        checkErr(src);
        if (f.subs > needSubs) {
            printf("%s %s %d %d %d %d\n", f.username, f.status, f.day, f.month, f.year, f.subs);
        }
    }
    // checkErr(src);
    // int avgRating = ratings / count;
    // int aboveAvg = 0;
    // int trad = 0;
    // int cgi = 0;
    // fseek(src, 0, SEEK_SET);
  
    // while(fread(&f, sizeof(User), 1, src)) {
    //     checkErr(src);
    //     if (f.rating > avgRating) {
    //         aboveAvg++;
    //         if (strcmp(f.technique, "Traditional") == 0) { 
    //             trad++;
    //         } else if (strcmp(f.technique, "CGI") == 0) { 
    //             cgi++;
    //         }
    //     }
    // }
    // checkErr(src);
    // int tradPercent = (trad * 100) / aboveAvg;
    // int cgiPercent = (cgi * 100) / aboveAvg;
    // printf("Average IMDb rating of series is %d\n", avgRating);
    // printf("There are %d animated shows with ratings above average\n", aboveAvg);
    // printf("%d%% of them have traditional technique, and %d%% of them were made using CGI technology\n", tradPercent, cgiPercent);
    fclose(src);
    return 0;
}
