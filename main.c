#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"

// метод Шелла
// (7 div 2) % 6 + 1 = 4 - кольцевой двунаправленный
// 7 % 15 + 1 = 8 - дополнить список копиями заданного значения до указанной длины k

enum Command {EXIT, PUSH, INSERT, POP, REMOVE, SORT, FIND, SIZE, PRINT, CLEAR};

int CommandRead() {
    int cmd;

    printf("\n\
1. Push back item\n\
2. Insert item\n\
3. Pop back item\n\
4. Remove item\n\
5. Sort table\n\
6. Find by key\n\
7. Print table size\n\
8. Print table\n\
9. Clear table (delete all the items)\n\
0. Exit\n\
\n");

    scanf("%d", &cmd);
    putchar('\n');
    if (cmd < 0 || cmd > 9) {
        return -1;
    } else {
        return cmd;
    }
}

KeyType* KeyIn() {
    KeyType* key = (KeyType*)malloc(sizeof("abcdef"));
    scanf("%s", key);
    key[6] = 0;
    return key;
}

KeyType* fKeyIn(FILE* file_in) {
    KeyType* key = (KeyType*)malloc(sizeof("abcdef"));
    fscanf(file_in, "%s", key);
    key[6] = 0;
    return key;
}

void CommandExecute(int inp, Table** table) {
    enum Command cmd = inp;
    int idx, param;
    ValueType val;
    KeyType* key;

    switch (cmd)
    {
        case EXIT:
            TableDelete(table);
            exit(0);
            break;

        case PUSH:
            printf("Enter data in format <key> <value>\n");
            key = KeyIn();
            scanf("%d", &val);
            TablePushBack(*table, ToDataType(key, val));
            free(key);
            break;

        case INSERT:
            printf("Enter data in format <key> <value>\n");
            key = KeyIn();
            scanf("%d", &val);
            printf("\nEnter index\n");
            scanf("%d", &idx);
            TableInsert(*table, idx, ToDataType(key, val));
            free(key);
            break;

        case POP:
            TablePopBack(*table);
            break;

        case REMOVE:
            printf("Enter index\n");
            scanf("%d", &idx);
            TableRemove(*table, idx);
            break;

        case SIZE:
            printf("Table size is %ld\n", TableSize(*table));
            break;
        
        case PRINT:
            TablePrint(*table);
            break;

        case CLEAR:
            TableClear(*table);
            break;

        case SORT:
            printf("Enter sort parameter\n");
            scanf("%d", &param);
            TableShellSort(*table, param);
            break;

        case FIND:
            printf("Enter key\n");
            key = KeyIn();
            DataType* lb = TableLowerBound(*table, key);
            printf("+----+--------+--------+\n|%4ld|", lb-(*table)->begin);
            DataTypePrint(lb);
            printf("|\n+----+--------+--------+\n|%4ld|", 1+lb-(*table)->begin);
            DataTypePrint(&(lb[1]));
            printf("|\n+----+--------+--------+\n");
            free(key);
            break;
    }
}

int main() {
    Table* table;
    TableCreate(&table);

    FILE *file_in = fopen("table.txt", "r");
    KeyType* key;
    ValueType val;
    while (!feof(file_in)) {
        key = fKeyIn(file_in);
        fscanf(file_in, "%d", &val);
        TablePushBack(table, ToDataType(key, val));
        free(key);
    }
    fclose(file_in);

    int cmd;


    while (1) {
        cmd = CommandRead();
        if (cmd != -1) {
            CommandExecute(cmd, &table);
        }
    }

    return 0;
}