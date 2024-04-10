#include "queue.h"
#include "bubble_sort.h"

void BubbleSort(udt *q) {
    int size = udt_size(q);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Swap adjacent elements if they are in the wrong order
            QueueItem *current = q->head;
            for (int k = 0; k < j; k++) {
                current = current->next;
            }
            int val1 = current->value;
            int val2 = current->next->value;
            if (val1 > val2) {
                // Swap values
                int temp = val1;
                current->value = val2;
                current->next->value = temp;
            }
        }
    }
}
