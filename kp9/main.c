#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record Record;
typedef struct String String;
typedef struct Strings Strings;
struct String {
    char text[100];
};
struct Record {
    int key;
    char *text;
};

struct Strings {
    String data[100];
};

Record *newRecord(int n) {
    Record *r = (Record *)malloc(sizeof(Record) * n);
    for (int i = 0; i < n; i++) {
        r[i].key = i;
        r[i].text = (char *)malloc(sizeof(char) * 100);
    }
    return r;
}

int compare_records(const void *a, const void *b) {
    Record *record_a = (Record *)a;
    Record *record_b = (Record *)b;
    return strcmp(record_a->text, record_b->text);
}

void merge(Record records[], int left, int middle, int right) {
    int i = left;
    int j = middle;
    int k = 0;

    Record *temp = newRecord(right - left + 1);

    while (i < middle && j < right) {
        if (compare_records(&records[i], &records[j]) <= 0) {
            temp[k++] = records[i++];
        } else {
            temp[k++] = records[j++];
        }
    }

    while (i < middle) {
        temp[k++] = records[i++];
    }

    while (j < right) {
        temp[k++] = records[j++];
    }
    if (left == 0 && right == 0) {
        printf("Вывод: ");
    }
    for (i = 0; i < right - left; ++i) {
        records[i + left] = temp[i];
    }
}

void merge_sort(Record *records, int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int middle = (left + right) / 2;

    merge_sort(records, left, middle);
    merge_sort(records, middle, right);

    merge(records, left, middle, right);
}

int binarySearch(Record *table, char key, int n) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (table[mid].text[0] == key) {
            return mid;
        }
        if (table[mid].text[0] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void printTable(Record table[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Key: %d, Text: %s\n", table[i].key, table[i].text);
    }
}
Strings toString(char *poem, int *size) {
    Strings s;
    int i = 0;
    int j = 0;
    int k = 0;
    while (poem[i] != '\0') {
        if (poem[i] == '\n') {
            s.data[j].text[k] = '\0';
            k = 0;
            j++;
        } else {
            s.data[j].text[k] = poem[i];
            k++;
        }
        i++;
    }
    *size = j;
    return s;
}
void Clean(Record *table) { free(table); }
int main() {
    char poemdry[] = {"Two roads diverged in a yellow wood,\n"
                      "And sorry I could not travel both\n"
                      "And be one traveler, long I stood\n"
                      "And looked down one as far as I could\n"
                      "To where it bent in the undergrowth;\n"
                      "Then took the other, as just as fair,\n"
                      "And having perhaps the better claim,\n"
                      "Because it was grassy and wanted wear;\n"
                      "Though as for that the passing there\n"
                      "Had worn them really about the same,\n"
                      "And both that morning equally lay\n"};
    int n;
    Strings poem = toString(poemdry, &n);

    Record *table = newRecord(n);

    for (int i = 0; i < n; i++) {
        table[i].key = i;
        table[i].text = poem.data[i].text;
    }
    merge_sort(table, 0, n);
    printf("Sorted table by the first letter of each line:\n");
    printTable(table, n);

    char keyToFind =
        'T'; // Example key to search for (first letter of the first line)
    int index = binarySearch(table, keyToFind, n);
    if (index != -1) {
        printf("Record found: Key: %d Text: %s \n", table[index].key,
               table[index].text);
    } else {
        printf("Record with key %c not found. \n", keyToFind);
    }
    Clean(table, n);
    return 0;
}
