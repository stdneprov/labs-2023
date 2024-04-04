#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* second_name;
    char* initials;
    char gender;
    int russian;
    int english;
    int mathematics;
    char group;
    struct Node* next;

};

struct List {

    struct Node* head;
    unsigned size;

};

//List
void InitList (struct List* l);
void PushBack (struct List* l, char* second_name, char* initials, char gender, int russian, int english, int mathematics, char group);
void Print (struct List* l);
unsigned Size (const struct List* l);
void Pop(struct List* l);
void FreeList (struct List* l);
void Func(struct List* l);

//ListIterator
typedef struct Node* ListIterator;
ListIterator begin(struct List* l);
ListIterator next(ListIterator it);
ListIterator plus(ListIterator it, unsigned x);
ListIterator end(struct  List* l);


