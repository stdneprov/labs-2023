#include "table.h"
#include "sort.h"

// ключ: целое + литера
// сортировка: линейный выбор с подсчетом

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

    item temp;
    while (!feof(d)) {
        fscanf(k, "%s", temp.key);
        fscanf(d, "%s", temp.val);
        Add(table, temp);
    }

    printf("\n--------------------------------Table--------------------------------\n");
    Print(table);
    char input[20];
    char printTable[10] = "print";
    char sortTable[15] = "sort";
    char exitMenu[10] = "exit";
    char search[10] = "search";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("---------------------------------------------------------------------\n");
        printf("$ sort - sorting table\n");
        printf("$ exit - stop programm\n");
        printf("$ search KEY - search element for key in sorted table\n");
        printf("$ print - print table\n");
        printf("---------------------------------------------------------------------\n");

        char command[15] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            break;
        }

        int ind = 0;
        char forNum[20] = "";
        int firstChecked = 0;
        for (int i = 0; input[i] != '\n'; ++i) {
            if (input[i] != ' ' && input[i] !='\n' && firstChecked == 0) {
                command[i] = input[i];
                input[i] = ' ';
            }
            else {
                firstChecked = 1;
                if (input[i] != ' ' && input[i] !='\n') {
                    forNum[ind] = input[i];
                    ind++;
                }
            }
        }

        if (strcmp(command, printTable) == 0) {
            printf("--------------------------------Table--------------------------------\n");
            Print(table);
        } else if (strcmp(command, sortTable) == 0) {
            LinearWithCounting(table);
            printf("--------------------------------Table--------------------------------\n");
            Print(table);
        } else if (strcmp(command, search) == 0) {
            int res = Search(table, forNum);
            if (res == -1) {
                printf("Not found\n");
            } else {
                printf("%s",table->rows[res].val);
            }
        } else if (strcmp(command, exitMenu) == 0) {
            Destroy(table);
            break;
        } else {
            printf("-Wrong command\n");
        }
    }
}