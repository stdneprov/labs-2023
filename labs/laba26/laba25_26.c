#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int top;
    int capacity;
    int* array;
} Stack;

Stack* Create(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int Empty(Stack* stack) {
    return stack->top == -1;
}

void Push(Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int Pop(Stack* stack) {
    return stack->array[stack->top--];
}

int Peek(Stack* stack) {
    return stack->array[stack->top];
}

void Merge(int* array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            array[k++] = L[i++];
        }
        else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) {
        array[k++] = L[i++];
    }
    while (j < n2) {
        array[k++] = R[j++];
    }

    free(L);
    free(R);
}

void MergeSort(int* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(array, left, mid);
        MergeSort(array, mid + 1, right);
        Merge(array, left, mid, right);
    }
}

void Sort(Stack* stack) {
    MergeSort(stack->array, 0, stack->top);
}

Stack* MergeStacks(Stack* s1, Stack* s2) {
    Sort(s1);
    Sort(s2);

    int mergedCapacity = s1->capacity + s2->capacity;
    Stack* MergedStack = Create(mergedCapacity);

    int i = 0, j = 0;

    while (i <= s1->top && j <= s2->top) {
        if (s1->array[i] >= s2->array[j]) {
            Push(MergedStack, s1->array[i++]);
        }
        else {
            Push(MergedStack, s2->array[j++]);
        }
    }

    while (i <= s1->top) {
        Push(MergedStack, s1->array[i++]);
    }
    while (j <= s2->top) {
        Push(MergedStack, s2->array[j++]);
    }

    return MergedStack;
}

void PrintStack(Stack* stack) {
    while (!Empty(stack)) {
        printf("%d ", Pop(stack));
    }
    printf("\n");
}

int main() {
    int n1, n2, item;

    printf("Введите размер первого стека: ");
    scanf("%d", &n1);
    printf("Введите размер второго стека: ");
    scanf("%d", &n2);

    Stack* stack1 = Create(n1);
    Stack* stack2 = Create(n2);

    printf("Введите элементы первого стека:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &item);
        Push(stack1, item);
    }

    printf("Введите элементы второго стека:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &item);
        Push(stack2, item);
    }

    Stack* MergedStack = MergeStacks(stack1, stack2);

    printf("Результирующий стек после слияния:\n");
    PrintStack(MergedStack);

    free(stack1->array);
    free(stack1);
    free(stack2->array);
    free(stack2);
    free(MergedStack->array);
    free(MergedStack);

    return 0;
}
