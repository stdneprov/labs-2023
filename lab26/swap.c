#include "swap.h"

void SwapIfGreater(Node* head) {
    Node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->data > current->next->data) {
            int temp = current->data;
            current->data = current->next->data;
            current->next->data = temp;
            printf("swapped\n");
            return;
        }
        current = current->next;
    }
    printf("nothing to swap\n");
}
