#include <stdio.h>
#include <stdlib.h>

// Структура узла списка
struct Node {
    int data;
    struct Node* next;
};

// Функция для создания нового узла
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Функция для добавления нового узла в конец списка
void append(struct Node** head_ref, int data) {
    struct Node* new_node = newNode(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = *head_ref;
    } else {
        struct Node* last = *head_ref;
        while (last->next != *head_ref) {
            last = last->next;
        }
        last->next = new_node;
        new_node->next = *head_ref;
    }
}

// Функция для удаления узла по значению
void deleteNode(struct Node** head_ref, int key) {
    if (*head_ref == NULL) {
        return;
    }
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;
    while (temp->data != key) {
        if (temp->next == *head_ref) {
            printf("Узел с ключом %d не найден\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp == *head_ref && temp->next == *head_ref) {
        *head_ref = NULL;
        free(temp);
        return;
    }
    if (temp == *head_ref) {
        prev = (*head_ref);
        while (prev->next != *head_ref) {
            prev = prev->next;
        }
        *head_ref = (*head_ref)->next;
        prev->next = *head_ref;
        free(temp);
    } else if (temp->next == *head_ref) {
        prev->next = *head_ref;
        free(temp);
    } else {
        prev->next = temp->next;
        free(temp);
    }
}

// Функция для подсчета длины списка
int countNodes(struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    int count = 0;
    struct Node* current = head;
    do {
        count++;
        current = current->next;
    } while (current != head);
    return count;
}

// Функция для отображения элементов списка
void display(struct Node* head) {
    struct Node* current = head;
    if (head != NULL) {
        do {
            printf("%d ", current->data);
            current = current->next;
        } while (current != head);
    }
    printf("\n");
}

// Функция для циклического сдвига элементов вперёд
void shiftForward(struct Node** head_ref) {
    if (*head_ref == NULL) {
        return;
    }
    *head_ref = (*head_ref)->next;
}

int main() {
    struct Node* head = NULL;
    int choice, value, key;

    do {
        printf("\n----- Меню -----\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Вывести список\n");
        printf("4. Подсчитать длину списка\n");
        printf("5. Циклический сдвиг элементов списка на один элемент вперед\n");
        printf("6. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Введите значение для добавления: ");
                scanf("%d", &value);
                append(&head, value);
                printf("Элемент успешно добавлен\n");
                break;
            case 2:
                if (head == NULL) {
                    printf("Список пуст\n");
                } else {
                    printf("Введите значение для удаления: ");
                    scanf("%d", &key);
                    deleteNode(&head, key);
                }
                break;
            case 3:
                if (head == NULL) {
                    printf("Список пуст\n");
                } else {
                    printf("Элементы списка: ");
                    display(head);
                }
                break;
            case 4:
                printf("Длина списка: %d\n", countNodes(head));
                break;
            case 5:
                shiftForward(&head);
                printf("Список после сдвига: ");
                display(head);
                break;
            case 6:
                printf("Выход из программы\n");
                break;
            default:
                printf("Некорректный выбор\n");
        }
    } while (choice != 6);

    return 0;
}
