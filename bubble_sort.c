#include "queue.h"
#include "bubble_sort.h"

void BubbleSort(udt *q) {
    T size = udt_size(q);
    bool isInOrder = false;
    while (isInOrder == false) {
        isInOrder = true;
        T first = udt_pop(q);
        for (int i = 0; i < size - 1; i++) {
            T temp = udt_pop(q);
            if (temp < first) {
                udt_push(q, first);
                first = temp;
            } else {
                udt_push(q, temp);
                isInOrder = false;
            }
        }
        udt_push(q, first);
    }
}
