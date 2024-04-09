#ifndef Stack_h
#define Stack_h
#include <stdio.h>
#include <stdlib.h>

// Структура элемента стека
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура стека
typedef struct {
    Node* top;
} Stack;

// Инициализация стека
void Init(Stack* stack) {
    stack->top = NULL;
}

// Проверка, пуст ли стек
int IsEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Добавление элемента в стек
void Push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка: память для нового узла не выделена\n");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Удаление элемента из стека
int Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        printf("Ошибка: стек пуст\n");
        return -1;
    }
    Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Получение верхнего элемента стека без его удаления
int StackTop(Stack* stack) {
    if (IsEmpty(stack)) {
        return 0;
    }
    return stack->top->data;
}

// Функция для вывода содержимого стека
void StackPrint(Stack *stk) {
    if (IsEmpty(stk)) {
        printf("Стек пуст\n");
    }
    printf("Элементы стека: ");
    for (Node *i = stk->top; i != NULL; i = i->next) {
        printf("%d", i->data);
        if (i->next != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void BubbleSort(Stack *stack) {
    Stack tempStack;
    
    while (!IsEmpty(stack)) {
        int current = Pop(stack);

        // Переносим элементы из временного стека обратно в основной стек,
        // если они больше текущего элемента
        while (!IsEmpty(&tempStack) && StackTop(&tempStack) < current) {
            Push(stack, Pop(&tempStack));
        }

        Push(&tempStack, current);
    }

    // Переносим элементы из временного стека обратно в основной стек
    while (!IsEmpty(&tempStack)) {
        Push(stack, Pop(&tempStack));
    }

    Pop(stack);

}

#endif