#include <stdio.h>      /* Standard Library of Input and Output */
#include "table.h"
#include <string.h>

Table* Unity(Table* less, Table* pivot, Table* greater) {
    Table* result = less;

    if (less != NULL) {
        while (less->next != NULL) {
            less = less->next;
        }
        less->next = pivot;
    } else {
        result = pivot;
    }

    pivot->next = greater;
    return result;
}

Table* HoaraSort(Table* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Table* pivot = head;
    Table* lessHead = NULL;
    Table* lessTail = NULL;
    Table* greaterHead = NULL;
    Table* greaterTail = NULL;
    Table* current = head->next;

    while (current != NULL) {
        Table* next = current->next;
        current->next = NULL;
        if (current->key < pivot->key) {
            if (lessHead == NULL) {
                lessHead = lessTail = current;
            } else {
                lessTail->next = current;
                lessTail = current;
            }
        } else {
            if (greaterHead == NULL) {
                greaterHead = greaterTail = current;
            } else {
                greaterTail->next = current;
                greaterTail = current;
            }
        }
        current = next;
    }

    lessHead = HoaraSort(lessHead);
    greaterHead = HoaraSort(greaterHead);

    return Unity(lessHead, pivot, greaterHead);
}

void TableSort(Table** table) {
    if (table == NULL || *table == NULL) {
        return;
    }

    *table = HoaraSort(*table);

    Table* current = *table;
    while (current->next != NULL) {
        current = current->next;
    }
    (*table)->last = current;
}
