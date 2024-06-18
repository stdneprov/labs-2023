#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double T;

typedef struct Item {
    T value;
    struct Item *next;
} Item;

typedef struct Iterator {
    Item *node;
} Iterator;

typedef struct List {
    Item *first;
    Item *last;
    Item *sentinel;
} List;

Item *CreateItem(T value, Iterator next);
void ListInit(List **l);
Iterator Last(List **l);
Iterator First(List **l);
Iterator Next(Iterator iter);
Iterator InsertAfter(List **l, T value, Iterator iter);
bool IsEqual(Iterator iter1, Iterator iter2);
bool IsTerminator(Iterator iter);
bool IsEmpty(List **l);
T Delete(List **l, Iterator iter);
T GetValue(Iterator iter);
void SetValue(Iterator iter, T value);
void Swp(T *a, T *b);
void Swap(List **l, int k);
int Count(List **l);
void Print(List **l);
void Destroy(List *l);
void ExtendToLength(List **l, T value, int k);

Item *CreateItem(T value, Iterator next) {
    Item *i = (Item *)malloc(sizeof(Item));
    i->next = next.node;
    i->value = value;
    return i;
}

void ListInit(List **l) {
    *l = (List *)malloc(sizeof(List));
    (*l)->sentinel = CreateItem(0, (Iterator){NULL});  // Sentinel node
    (*l)->first = (*l)->last = (*l)->sentinel;
}

Iterator Last(List **l) {
    return (Iterator){(*l)->last};
}

Iterator First(List **l) {
    return (Iterator){(*l)->first};
}

Iterator Next(Iterator iter) {
    return (Iterator){iter.node->next};
}

Iterator InsertAfter(List **l, T value, Iterator iter) {
    if (IsEmpty(l)) {
        (*l)->first = (*l)->last = CreateItem(value, (Iterator){(*l)->sentinel});
        (*l)->sentinel->next = (*l)->first;  // Point sentinel to the first node
        return First(l);
    } else if (IsEqual(iter, Last(l))) {
        iter.node->next = CreateItem(value, (Iterator){(*l)->sentinel});
        (*l)->last = iter.node->next;
        (*l)->sentinel->next = (*l)->last->next;
    } else {
        iter.node->next = CreateItem(value, Next(iter));
    }
    return Next(iter);
}

bool IsEqual(Iterator iter1, Iterator iter2) {
    return iter1.node == iter2.node;
}

bool IsTerminator(Iterator iter) {
    return iter.node == NULL;
}

bool IsEmpty(List **l) {
    return (*l)->first == (*l)->sentinel;
}

T Delete(List **l, Iterator iter) {
    if (IsEmpty(l) || IsTerminator(iter)) {
        return -1;
    }

    T result = GetValue(iter);

    if (IsEqual(iter, First(l))) {
        if (IsEqual(iter, Last(l))) {
            free(iter.node);
            (*l)->first = (*l)->last = (*l)->sentinel;
            (*l)->sentinel->next = NULL;
        } else {
            (*l)->first = iter.node->next;
            (*l)->sentinel->next = (*l)->first;
            free(iter.node);
        }
    } else {
        Iterator prev = First(l);
        while (Next(prev).node != iter.node) {
            prev = Next(prev);
        }
        prev.node->next = iter.node->next;
        if (IsEqual(iter, Last(l))) {
            (*l)->last = prev.node;
        }
        free(iter.node);
    }

    return result;
}

void Destroy(List *l) {
    if (!IsEmpty(&l)) {
        Iterator i = First(&l);
        while (i.node != l->sentinel) {
            Iterator next = Next(i);
            free(i.node);
            i = next;
        }
    }
    free(l->sentinel);
    free(l);
}

T GetValue(Iterator iter) {
    return iter.node->value;
}

void SetValue(Iterator iter, T value) {
    iter.node->value = value;
}

void Swp(T *a, T *b) {
    T c = *a;
    *a = *b;
    *b = c;
}

int Count(List **l) {
    int k = 0;
    if (IsEmpty(l)) {
        return 0;
    }
    for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
        k++;
        if (i.node == (*l)->sentinel) {
            break;
        }
    }
    return k;
}

void Print(List **l) {
    if (!IsEmpty(l)) {
        for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
            printf("%lf ", GetValue(i));
            if (i.node == (*l)->sentinel) {
                break;
            }
        }
        printf("\n");
    }
}

void ExtendToLength(List **l, T value, int k) {
    int currentSize = Count(l);
    if (currentSize >= k) {
        return;
    }
    for (int i = currentSize; i < k; i++) {
        InsertAfter(l, value, Last(l));
    }
}

int main() {
    List *lst;
    char input[20];
    char initList[10] = "init";
    char addList[10] = "add";
    char countList[10] = "count";
    char delLastValue[10] = "delLast";
    char delFirstValue[10] = "delFirst";
    char swapValue[15] = "swap";
    char exitMenu[10] = "exit";
    char printList[10] = "print";
    char extendList[10] = "extend";
    char command[10] = "";

    while (strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("# init  - создать список\n");
        printf("# add value - добавить значение в конец списка\n");
        printf("# delFirst - удалить первый элемент\n");
        printf("# delLast - удалить последний элемент\n");
        printf("# count - показать длину списка\n");
        printf("# print - показать список\n");
        printf("# extend k value - дополнить список до длины k значением value\n");
        printf("# exit - выйти\n");

        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            break;
        }
        sscanf(input, "%s", command);

        if (strcmp(command, initList) == 0) {
            ListInit(&lst);
        } else if (strcmp(command, addList) == 0) {
            T value;
            sscanf(input, "%*s %lf", &value);
            InsertAfter(&lst, value, Last(&lst));
        } else if (strcmp(command, delLastValue) == 0) {
            Delete(&lst, Last(&lst));
        } else if (strcmp(command, delFirstValue) == 0) {
            Delete(&lst, First(&lst));
        } else if (strcmp(command, printList) == 0) {
            Print(&lst);
        } else if (strcmp(command, countList) == 0) {
            printf("%d\n", Count(&lst));
        } else if (strcmp(command, extendList) == 0) {
            int k;
            T value;
            sscanf(input, "%*s %d %lf", &k, &value);
            ExtendToLength(&lst, value, k);
        } else if (strcmp(command, exitMenu) == 0) {
            Destroy(lst);
            break;
        } else {
            printf("-Сел как-то слон на Колобка, думммает... Вот блин)\n");
        }
    }
}
