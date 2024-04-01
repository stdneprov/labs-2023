#include<stdlib.h>
#include<stdio.h>

typedef struct Node Node;

typedef struct Complex Complex;

struct Complex {
    double re;
    double im;
};

struct Node{
    Complex val;
    Node* next;
};

typedef struct List List;

struct List{
    Node* head;
    int size;
};

List* NewList();
void FreeList(List*);
void Insert(List*, Complex);
void Print(List*);
void Erase(List*, Complex);
Node* FindPrev(List*, Complex);
void SwapElements(List*, Complex b, Complex c);