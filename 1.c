#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100

typedef struct {
    char value[50];
} Value;

void heapify(float* keys, Value* values, int n, int i) {
     int largest = i;
     int left = 2 * i + 1;
     int right = 2 * i + 2;

    if (left < n && keys[left] > keys[largest])
        largest = left;

    if (right < n && keys[right] > keys[largest])
        largest = right;

    if (largest != i) {
        float temp1 = keys[i];
        keys[i] = keys[largest];
        keys[largest] = temp1;

        Value temp = values[i];
        values[i] = values[largest];
        values[largest] = temp;

        heapify(keys, values, n, largest);
    
    }
}

void HeapSort(float* keys, Value* values, int n) {
     for (int i = n / 2 - 1; i >= 0; i--)
        heapify(keys,values, n, i);

     for (int i = n - 1; i > 0; i--) {
        float temp = keys[0];
        keys[0] = keys[i];
        keys[i] = temp;

        Value temp2 = values[0];
        values[0] = values[i];
        values[i] = temp2;
        
        heapify(keys, values, i, 0);
     }
}

int binarySearch(float* keys, Value* values, int left, int right, float key) {
     while (left <= right) {
        int mid = left + (right - left) / 2;
        if (keys[mid] == key)
            return mid;
        else if (keys[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
     }
     return -1;
}

void PrintTable(float* keys, Value* values, int n) {
    for(int i = 0; i < n; i++) {
        printf("%f %s\n", keys[i], values[i].value);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    float keys [MAX_ENTRIES];
    Value values [MAX_ENTRIES];
    int n = 0;
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (n < MAX_ENTRIES && fscanf(file, "%f %s", &keys[n], values[n].value) == 2) {
        n++;
    }

    PrintTable(keys, values, n);
    printf("\n");
    HeapSort(keys, values, n);
    PrintTable(keys, values, n);

    float searchKey;
    printf("Enter a key to search for: ");
    scanf("%f", &searchKey);

    int index = binarySearch(keys, values, 0, n - 1, searchKey);
    if (index == -1)
        printf("Key not found\n");
    else
        printf("Key found %f, value: %s\n", keys[index], values[index].value);

    fclose(file);
    return 0;
}