#include "swap.h"

int SwapIfGreater(Node* head) {
    Node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->data > current->next->data) {
            int temp = current->data;
            current->data = current->next->data;
            current->next->data = temp;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void BubbleSort(Node** head) {
    if (*head == NULL)
        return;

    int swapped;
    Node* lastNode = NULL;

    do {
        swapped = 0;
        Node* temp = *head;

        while (temp->next != lastNode) {
            if (SwapIfGreater(temp)) {
                swapped = 1;
            }
            temp = temp->next;
        }
        lastNode = temp;
    } while (swapped);
}
