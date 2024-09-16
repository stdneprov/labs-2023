#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct Node {
    int id;
    char name[50];
    float salary;
    struct Node* next;
} Node;

Node* createNode(int id, char* name, float salary) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->salary = salary;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    Node* temp = head;
    do {
        printf("ID: %d, Имя: %s, Зарплата: %.2f\n", temp->id, temp->name, temp->salary);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

void insert(Node** head, int id, char* name, float salary) {
    Node* newNode = createNode(id, name, salary);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    }
    else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void deleteNode(Node** head, int id) {
    if (*head == NULL) return;

    Node* current = *head, * prev = NULL;

    if (current->id == id) {
        if (current->next == *head) {
            free(*head);
            *head = NULL;
        }
        else {
            Node* temp = *head;
            while (temp->next != *head) {
                temp = temp->next;
            }
            temp->next = current->next;
            *head = current->next;
            free(current);
        }
        return;
    }

    do {
        prev = current;
        current = current->next;
    } while (current != *head && current->id != id);

    if (current == *head) {
        printf("Элемент с ID %d не найден.\n", id);
        return;
    }

    prev->next = current->next;
    free(current);
}

int getLength(Node* head) {
    if (head == NULL) return 0;
    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    return count;
}

void reverseList(Node** head) {
    if (*head == NULL || (*head)->next == *head) return;

    Node* prev = NULL, * current = *head, * next = NULL;
    Node* last = *head;

    while (last->next != *head) {
        last = last->next;
    }

    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != *head);

    (*head)->next = prev;
    *head = prev;
}

void displayMenu() {
    printf("\nМеню:\n");
    printf("1. Печать списка\n");
    printf("2. Вставка нового элемента в список\n");
    printf("3. Удаление элемента из списка\n");
    printf("4. Подсчет длины списка\n");
    printf("5. Перестановка в обратном порядке\n");
    printf("6. Выход\n");
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Node* head = NULL;
    int choice, id;
    char name[50];
    float salary;

    do {
        displayMenu();
        printf("Введите номер операции: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printList(head);
            break;
        case 2:
            printf("Введите ID: ");
            scanf("%d", &id);
            printf("Введите имя: ");
            scanf("%s", name);
            printf("Введите зарплату: ");
            scanf("%f", &salary);
            insert(&head, id, name, salary);
            break;
        case 3:
            printf("Введите ID элемента для удаления: ");
            scanf("%d", &id);
            deleteNode(&head, id);
            break;
        case 4:
            printf("Длина списка: %d\n", getLength(head));
            break;
        case 5:
            reverseList(&head);
            printf("Список переставлен в обратном порядке.\n");
            break;
        case 6:
            printf("Выход...\n");
            break;
        default:
            printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        }
    } while (choice != 6);

    while (head != NULL) {
        deleteNode(&head, head->id);
    }

    return 0;
}
