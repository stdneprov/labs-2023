#include <stdio.h>
#include "list.h"

int main() {
    List list = CreateList();
    Iterator iter = Start(&list);
    int choice;
    float value;

    do {
        printf("1. add element\n");
        printf("2. delete element\n");
        printf("3. print list\n");
        printf("4. print list length\n");
        printf("5. clear list if value exists\n");
        printf("6. insert after\n");
        printf("7. exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("enter value to add: ");
                scanf("%f", &value);
                Push(&iter, value);
                break;
            case 2:
                printf("enter value to delete: ");
                scanf("%f", &value);
                DeleteNode(&iter, value);
                break;
            case 3:
                PrintList(&list);
                break;
            case 4:
                printf("list length: %d\n", ListLength(&list));
                break;
            case 5:
                printf("enter value to check: ");
                scanf("%f", &value);
                ClearListIfExists(&list, value);
                break;
            case 6:
                {
                    printf("enter value to insert: ");
                    scanf("%f", &value);
                    float afterValue;
                    printf("enter value after which to insert: ");
                    scanf("%f", &afterValue);
                    Iterator it = Start(&list);
                    int found = 0;
                    do {
                        if (it.node->data == afterValue) {
                            InsertAfter(&it, value);
                            found = 1;
                            break;
                        }
                        it = Next(it);
                    } while (it.node != list.head);
                    if (!found) {
                        printf("value not found\n");
                    }
                }
                break;
            case 7:
                FreeList(&list);
                break;
            default:
                printf("invalid choice\n");
        }
    } while (choice != 7);
    return 0;
}