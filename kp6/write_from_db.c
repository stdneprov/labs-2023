#include "db.h"
#include <string.h>


int main(int argc, char *argv[]) {
    CommandsVARKT arr[100];
    if (!strcmp(argv[1], "base.db")) {
        if (argc == 3) {
            ReadFromCsv(arr, 2, "table.csv");
            WriteToBinaryFile(arr, 2, "base.db");
        } else if (argc == 4) {
            CommandsVARKT arr1[100];
            long long int j = 0;
            if (!strcmp(argv[3], "--passed")){
                ReadFromCsv(arr, 2, "table.csv");
                for (int i = 0; i < 2; i++) {
                    if (arr[i].passedProject == 1) {
                        arr1[j] = arr[i];
                        j++;
                    }
                }
                WriteToBinaryFile(arr1, j, "base.db");

            }
        }
        
    } else if (!strcmp(argv[1], "table.csv")) {
        if (argc == 3) {
            ReadFromBinaryFile(arr, 2, "base.db");
            WriteToCsv(arr, 2, "table.csv");
        } else if (argc == 4) {
            CommandsVARKT arr1[100];
            long long int j = 0;
            if (!strcmp(argv[3], "--passed")){
                ReadFromBinaryFile(arr, 2, "base.db");
                for (int i = 0; i < 2; i++) {
                    if (arr[i].passedProject == 1) {
                        arr1[j] = arr[i];
                        j++;
                    }
                }
                WriteToCsv(arr1, j, "table.csv");

            }
        }
        
    }
}