#include "item.h"
#include "sort.h"


int main(void) {
    FILE* c = fopen("data.txt", "r");
    FILE* k = fopen("keys.txt", "r");
    if(!c || !k)
        exit(-1);
    Table* table = CreateTable();
    if(!table) {
        Destroy(table);
        return 0;
    }

    //read data from data.txt and write to Table table 
    item nr;
    while (!feof(c)) {
        long int digits;
        fscanf(c, "%ld %s",
        &digits,
        nr.val);
        nr.val[strcspn(nr.val, "\n")] = 0;
        nr.key = digits;
        Add(table, nr);
        nr.key = 0;
    }


    fclose(c);
    fclose(k);
    if(!table) {
        exit(-1);
    }

    //menu
    printf("\nTable\n");
    Print(table);
    printf("\nIf you want to reverse table - write r\n");
    printf("If you want to reverse table - write s\n");
    printf("If you want to finist - write e or CTRL+D\n");
    printf("If you want to randomly rearrange all elements - write h\n");
    printf("If you want to binary search elements - write b and NEXT line key\n");

    //work!
    while(!feof(stdin)) {

        char k[KEY_SIZE];
        scanf("%s", k);
        if (strcmp(k, "s") == 0) {
            Sort(table);
            printf("\nTable after sort\n");
            Print(table);
        } else if (strcmp(k, "r") == 0) {
            Reverse(table);
            printf("\nTable after reverse\n");
            Print(table);
        } else if (strcmp(k, "e") == 0) {
            break;
        } else if (strcmp(k, "h") == 0) {
            Shuffle(table);
            printf("\nTable after randomly rearrange all elements\n");
            Print(table);
        } else if (strcmp(k, "b") == 0) {
            long int key_for_search = 0;
            scanf("%ld", &key_for_search);
            int r = Search(table, key_for_search);
                if(r == -1) {
                    printf("Not found\n");
                } else {
                    printf("For the first time appeared on index [%d] -> (%s)\n", r, table->rows[r].val);
                }
        } else {
            continue;
        }
    }

    Destroy(table);
}