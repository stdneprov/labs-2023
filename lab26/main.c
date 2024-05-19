#include <stdio.h>
#include "list.h"
#include "swap.h"

Node* FindNode(Node* head, int key);
void InsertBeforeValue(Node** head_ref, int value, int data);

int main() {
    Node* head = NULL;
    int choice, num, key, value;
    
    do {
        printf("1. push node\n");
        printf("2. add node\n");
        printf("3. delete node\n");
        printf("4. print list\n");
        printf("5. swap\n");
        printf("6. exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("enter node data: ");
                scanf("%d", &num);
                PushFront(&head, num);
                break;
            case 2:
                if (!IsEmpty(head)) {
                    printf("enter previous node data: ");
                    scanf("%d", &value);
                    Node* found = FindNode(head, value);
                    if (found == NULL) {
                        printf("node not found\n");
                        break;
                    }
                    printf("enter node data: ");
                    scanf("%d", &num);
                    InsertAfterValue(&head, value, num);
                } else {
                    printf("the list is empty\n");
                }
                break;
            case 3:
                if (!IsEmpty(head)) {
                    printf("enter node data: ");
                    scanf("%d", &key);
                    Node* found = FindNode(head, key);
                    if (found == NULL) {
                        printf("node not found\n");
                    } else {
                        DeleteNode(&head, key);
                    }
                } else {
                    printf("the list is empty\n");
                }
                break;
            case 4:
                if (!IsEmpty(head)) {
                    printf("the list: ");
                    PrintList(head);
                } else {
                    printf("the list is empty\n");
                }
                break;
            case 5:
                if (!IsEmpty(head)) {
                    SwapIfGreater(head);
                } else {
                    printf("the list is empty\n");
                }
                break;
            case 6:
                break;
            default:
                printf("choose again\n");
        }
    } while (choice != 6);

    FreeList(&head);

    return 0;
}
