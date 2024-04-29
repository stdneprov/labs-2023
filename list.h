#ifndef __LIST__
#define __LIST__
#define POOL_SIZE 100
#include <stdbool.h>

typedef int T;

typedef struct Item { //обьявляем элемент
    T data;
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct Iterator { //обертка для адреса
    Item *node;
} Iterator;

typedef struct List { //лин список
    Item* last;
    int size;
    Item* first;
    Item data[POOL_SIZE + 1];
} List;


List * ListInit(); //создать 
bool IsEqual(Iterator iter1, Iterator iter2); //Равны
bool IsTerminator(List *l, Iterator iter); //последний итератор
bool IsEmpty(List *l); //пустой список
T GetValue(Iterator iter); //получить значение по итератору
void SetValue(Iterator iter, T value); //установить значение по итератору
Iterator Last(List *l); //возвращает итератор последнего элемента списка
Iterator First(List *l); //возвращает итератор первого эл-та списка
Iterator Next(Iterator* iter); //возвращает итератор следующего элемента 
Iterator Previous(Iterator* iter); //предыдущего элемента
void Add(List *l, T value); //добавить
Iterator InsertAfter(List *l, T value, Iterator iter); //
Iterator InsertBefore(List *l, T value, Iterator iter);
void InsertSort(List* l, T value);
void Destroy(List *l); //удалить
void Print(List *l); 

void PrintTest(List *l);
#endif