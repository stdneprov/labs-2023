#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

// Структура элемента списка
typedef struct list_node ListNode;

// Список
typedef struct list List;

// Итератор, который содержит в себе ссылку на элемент списка и на сам список
typedef struct List_iterator {
    ListNode* current; 
    const List* list; 
} ListIterator;

// Создание списка
List* ListCreate(void);

// Размер списка
int32_t ListSize(const List* const list);

// Вставка элеменета в начало списка и возвращение итератора на него
ListIterator ListInsertFront(List* const list, double val);

// Вставка элеменета в конец списка и возвращение итератора на него
ListIterator ListInsertBack(List* const list, double val);

// Вставка элеменета после итератора и возвращение итератора на него
ListIterator ListInsertAfter(List* const list, const ListIterator iterator, double val);

// Удаление элемента из начала списка
void ListRemoveFront(List* const list);

// Удаление элемента из конца списка
void ListRemoveBack(List* const list);

// Удаление элемента после итератора
void ListRemoveAfter(List* const list, const ListIterator iterator);

// Очищение списка (он становится таким же, как и при инициализации
void ListClear(List* const list);

// Унитожение списка (его очищение + освобождение памяти)
void ListDestroy(List** const list);

// Итератор первого занятого элемента списка
ListIterator ListBegin(const List* const list);

// Итератор последнего занятого элемента списка
ListIterator ListLast(const List* const list);

// Печать всего списка
void ListPrint(const List* const list);

// Значение итератора
double ListIteratorData(const ListIterator iterator);

// Сдвиг итератора вперёд
void ListIteratorIncrement(ListIterator* const iterator);

// Сдвиг итератора назад
void ListIteratorDecrement(ListIterator* const iterator);

// Проверка итераторов на равенство
bool ListIteratorEqual(const ListIterator lhs, const ListIterator rhs);

// Нестандартное действие вариант 10: добавить к экземпляров последнего элемента в начало списка  
void CopyLastToFront(List* list, const int32_t k);

