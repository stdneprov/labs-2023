#ifndef TABLE_H
#define TABLE_H

typedef struct Key {
    int num;
    char lit;
} Key;

typedef struct Value {
    char value[150];
} Value;

void Swap(Key* key1, Value* value1, Key* key2, Value* value2);
int KeyCmp(Key key1, Key key2);
void PrintTable(Key* keys, Value* values, int n);
void SelectionSort(Key* keys, Value* values, int n);
int BinarySearch(Key* keys, Value* values, int left, int right, Key key);

#endif 
