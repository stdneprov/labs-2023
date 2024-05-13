#include "table.h"
#include "sort.h"


int main() {
    FILE* d = fopen("data.txt", "r");
    FILE* k = fopen("keys.txt", "r");
    if(!d || !k)
        exit(-1);
    Table* table = CreateTable();
    if(!table) {
        Destroy(table);
        return 0;
    }

    item nr;
    while (!feof(d)) {
        float digits;
        fscanf(k, "%f", &digits);
        fscanf(d, "%s", nr.val);
        nr.val[strcspn(nr.val, "\n")] = 0;
        nr.key = digits;
        Add(table, nr);
        nr.key = 0;
    }


    fclose(d);
    fclose(k);
    if(!table) {
        exit(-1);
    }

    printf("\nTable\n");
    Print(table);
    char input[20];
    char printTable[10] = "print";
    char sortTable[15] = "sort";
    char exitMenu[10] = "exit";
    char search[10] = "search";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("====================================================================\n");
        printf("# sort - sorting table\n");
        printf("# exit - stop programm\n");
        printf("# search KEY - search element for key in sorted table\n");
        printf("# print - print table\n");
        printf("====================================================================\n");

        char command[15] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            break;
        }
        float num;
        int ind = 0;
        char forNum[20] = "";
        for (int i = 0; input[i] != '\n'; ++i) {
            if (input[i] != ' ' && input[i] !='\n' && input[i] > '9') {
                command[i] = input[i];
                input[i] = ' ';
            }
            else {
                if (input[i] != ' ' && input[i] !='\n') {
                    forNum[ind] = input[i];
                    ind++;
                }
            }
        }
        sscanf(forNum, "%f", &num);
        
        if (strcmp(command, printTable) == 0) {
            Print(table);
        } else if (strcmp(command, sortTable) == 0) {
            BubbleSort(table);
            Print(table);
        } else if (strcmp(command, search) == 0) {
            int res = Search(table, num);
            if (res == -1) {
                printf("Not found\n");
            } else {
                printf("[%f] -> (%s)\n", num, table->rows[res].val);
            }
        } else if (strcmp(command, exitMenu) == 0) {
            Destroy(table);
            break;
        } else {
            printf("-Wrong command\n");
        }
    }
}