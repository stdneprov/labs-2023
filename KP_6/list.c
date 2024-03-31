#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitList (struct List* l) {

    l->head = NULL;
    l->size = 0;

}

void PushBack (struct List* l, char* second_name, char* initials, char gender, int russian, int english, int mathematics, char group) {

    if (l->head == NULL) {

        l->head = (struct Node*)malloc(sizeof (struct Node));
        if (l->head == NULL) {
            exit(-1);
        }
        l->head->second_name = second_name;
        l->head->initials = initials;
        l->head->gender = gender;
        l->head->russian = russian;
        l->head->english = english;
        l->head->mathematics = mathematics;
        l->head->group = group;
        l->head->next = l->head;

    } else {

        ListIterator it = begin(l);
        while(next(it) != begin(l)) {

            it = next(it);

        }

        it->next = (struct Node*)malloc(sizeof(struct Node));
        if (it->next == NULL) {
            exit(-1);
        } 
        it->next->second_name = second_name;
        it->next->initials = initials;
        it->next->gender = gender;
        it->next->russian = russian;
        it->next->english = english;
        it->next->mathematics = mathematics;
        it->next->group = group;
        it->next->next = begin(l);

    }

    ++(l->size);

}

void Pop(struct List* l) {

    if (l->size == 0) {

        return;

    }
    if (l->size == 1) {

        free(l->head->second_name);
        free(l->head->initials);
        free(l->head);
        InitList(l);
        return;

    }
    ListIterator it = begin(l);
    it = plus(it, l->size - 2);
    free(it->next->second_name);
    free(it->next->initials);
    free(it->next);
    l->size--;

}

void Print(struct List* l) {

    if (l->size == 0) {

        printf("List is empty\n");
        return;

    }

    ListIterator it = begin(l);
    for (int i = 0; i < l->size; i++) {

        printf("%s %s %c %d %d %d %c\n",it->second_name, it->initials, it->gender, it->russian, it->english, it->mathematics, it->group);
        it = next(it);

    }

}

void FreeList(struct List* l) {

    int s = l->size;

    for (int i = 0; i < s; i++) {

        Pop(l);

    }

}

unsigned Size(const struct List* l) {

    return l->size;

}

void Func (struct List* l) {
    ListIterator it = begin(l);
    for (int i = 0; i < l->size; i++) {
        if ((it->gender == 'f') && it->group == 'p') {
            int count_five = 0;
            if (it->russian == 5) {
                count_five++;
            }
            if (it->english == 5) {
                count_five++;
            }
            if (it->mathematics == 5) {
                count_five++;
            }
            if (count_five == 1) {
                printf("%s %s %c %d %d %d %c\n",it->second_name, it->initials, it->gender, it->russian, it->english, it->mathematics, it->group);
            }
            
        }
            

        it = next(it);

    }

}

ListIterator begin(struct List* l) {

    if (!l || !l->head) {

        return NULL;

    }

    return l->head;

}

ListIterator next(ListIterator it) {

    return it->next;

}

ListIterator plus(ListIterator it, unsigned x) {

    for (int i = 0; i < x; i++) {

        it = it->next;

    }

    return it;

}

ListIterator end(struct List* l) {

    return NULL;

}
