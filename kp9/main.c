#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

#define MAX_LINES 100

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("enter file name as an argument\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("cannot open file\n");
        return 1;
    }

    Key keys[MAX_LINES];
    Value values[MAX_LINES];

    int n = 0;  // счётчик строк
    while (n < MAX_LINES && fscanf(fp, "%d %c", &(keys[n].num), &(keys[n].lit)) == 2) {
        if (fgets(values[n].value, sizeof(values[n].value), fp) == NULL) {
            break;
        }
        values[n].value[strcspn(values[n].value, "\n")] = '\0';
        n++;
    }

    printf("\nbefore sort:\n");
    PrintTable(keys, values, n);

    SelectionSort(keys, values, n);

    printf("\nafter sort:\n");
    PrintTable(keys, values, n);

    Key search_key;
    printf("enter a key to search: ");
    scanf("%d %c", &(search_key.num), &(search_key.lit));

    int index = BinarySearch(keys, values, 0, n - 1, search_key);
    if (index == -1)
        printf("key not found\n");
    else
        printf("%d %c\t%s\n", keys[index].num, keys[index].lit, values[index].value);

    fclose(fp);
    return 0;
}
