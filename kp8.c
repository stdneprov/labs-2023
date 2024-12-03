#include <stdio.h>
#include <stdlib.h>

typedef struct Complex {
    double real;
    double imag;
} Complex;

typedef struct Node {
    Complex data;
    struct Node* next;
} Node;

typedef struct {
    Node* head; // Указатель на барьерный элемент
} List;

// Создание барьерного элемента
Node* createBarrier() {
    Node* barrier = (Node*)malloc(sizeof(Node));
    if (barrier == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    barrier->next = barrier; 
    return barrier;
}

// Инициализация списка
List createList() {
    List list;
    list.head = createBarrier();
    return list;
}

// Вставка элемента в начало списка
void insertFront(List* list, Complex data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = list->head->next;
    list->head->next = newNode;
}

// Удаление последних k элементов из списка
void removeLastKElements(List* list, int k) {
    Node* current = list->head;
    int count = 0;

    // Считаем количество элементов в списке
    while (current->next != list->head) {
        count++;
        current = current->next;
    }

    // Если элементов меньше или равно k, не изменяем список
    if (count < k) return;

    // Находим узел перед началом последних k элементов
    current = list->head;
    for (int i = 0; i < count - k; i++) {
        current = current->next;
    }

    // Освобождение памяти
    Node* temp;
    while (current->next != list->head) {
        temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

// Вывод списка
void printList(List list) {
    Node* current = list.head->next;
    while (current != list.head) {
        printf("%.2f + %.2fi -> ", current->data.real, current->data.imag);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    List myList = createList();
    insertFront(&myList, (Complex){1.0, 5.0});
    insertFront(&myList, (Complex){2.0, 4.0});
    insertFront(&myList, (Complex){3.0, 3.0});
    insertFront(&myList, (Complex){4.0, 2.0});
    insertFront(&myList, (Complex){5.0, 1.0});

    printf("Original List:\n");
    printList(myList);

    // Удалить последние 3 элемента
    removeLastKElements(&myList, 3);
    printf("List after removing last 3 elements:\n");
    printList(myList);

    return 0;
}


