#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_LEN 1024
#define MAX_RECORDS 1000

void printArrays(int *keys, char values[][MAX_LEN], int n, const char *message) {
    printf("%s:\n", message);
    for (int i = 0; i < n; i++) {
        printf("%d %s\n", keys[i], values[i]);
    }
    printf("\n");
}

int binarySearch(int *keys, int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (keys[mid] == target)
            return mid;
        else if (keys[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;  // если элемент не найден
}


void buildTournamentTree(int *tree, int *keys, int size) {
    for (int i = 0; i < size; i++) {
        tree[size - 1 + i] = i;
    }
    
    for (int i = size - 2; i >= 0; i--) {
        int left = tree[2 * i + 1];
        int right = tree[2 * i + 2];
        tree[i] = (keys[left] < keys[right]) ? left : right;
    }
}


void tournamentSort(int *keys, char values[][MAX_LEN], int size) {
    int *tree = (int *)malloc(2 * size * sizeof(int));
    int *tempKeys = (int *)malloc(size * sizeof(int));
    char tempValues[MAX_RECORDS][MAX_LEN];
    
    buildTournamentTree(tree, keys, size);
    
    for (int i = 0; i < size; i++) {
        int minIndex = tree[0];
        tempKeys[i] = keys[minIndex];
        strcpy(tempValues[i], values[minIndex]);
        keys[minIndex] = INT_MAX;
        
        buildTournamentTree(tree, keys, size);
    }

    memcpy(keys, tempKeys, size * sizeof(int));
    memcpy(values, tempValues, size * MAX_LEN);

    free(tree);
    free(tempKeys);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int keys[MAX_RECORDS];
    char values[MAX_RECORDS][MAX_LEN];
    int n = 0;

    while (n < MAX_RECORDS && fscanf(fp, "%d ", &keys[n]) != EOF) {
        fgets(values[n], MAX_LEN, fp);
        values[n][strcspn(values[n], "\n")] = '\0'; // Remove newline character
        n++;
    }
    fclose(fp);

    printArrays(keys, values, n, "Before sort");
    tournamentSort(keys, values, n);
    printArrays(keys, values, n, "After sort");

    
    int userKey;
    printf("Enter key to search: ");
    scanf("%d", &userKey);
    int foundIndex = binarySearch(keys, n, userKey);
    if (foundIndex != -1) {
        printf("Found: %d %s\n", keys[foundIndex], values[foundIndex]);
    } else {
        printf("Key not found.\n");
    }

    return EXIT_SUCCESS;
}

