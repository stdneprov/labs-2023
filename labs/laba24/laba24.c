#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Определение типов узлов: оператор или операнд
typedef enum { OPERATOR, OPERAND } NodeType;

// Структура узла дерева
typedef struct Node {
    NodeType type; // Тип узла
    union {
        char operator; // Оператор (+, -, *, /)
        double operand; // Операнд (число)
    } data;
    struct Node *left; // Левый ребенок
    struct Node *right; // Правый ребенок
} Node;

// Структура стека
typedef struct Stack {
    Node *node;
    struct Stack *next;
} Stack;

// Функция для добавления узла в стек
void push(Stack **stack, Node *node) {
    Stack *new_node = (Stack *)malloc(sizeof(Stack));
    new_node->node = node;
    new_node->next = *stack;
    *stack = new_node;
}

// Функция для извлечения узла из стека
Node *pop(Stack **stack) {
    if (*stack == NULL) {
        return NULL;
    }
    Stack *top = *stack;
    Node *node = top->node;
    *stack = top->next;
    free(top);
    return node;
}

// Функция для создания нового узла
Node *createNode(NodeType type, double operand, char operator) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = type;
    if (type == OPERAND) {
        node->data.operand = operand;
    } else {
        node->data.operator = operator;
    }
    node->left = node->right = NULL;
    return node;
}

// Функция для определения приоритета оператора
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Функция для преобразования выражения в дерево с использованием алгоритма сортировочной станции
Node *shuntingYard(char *expression) {
    Stack *operators = NULL;
    Stack *operands = NULL;
    for (int i = 0; i < strlen(expression); i++) {
        if (isspace(expression[i])) {
            continue;
        } else if (isdigit(expression[i]) || (expression[i] == '.')) {
            double value = 0;
            sscanf(&expression[i], "%lf", &value);
            while (isdigit(expression[i]) || (expression[i] == '.')) {
                i++;
            }
            i--;
            push(&operands, createNode(OPERAND, value, 0));
        } else if (strchr("+-*/", expression[i])) {
            while (operators != NULL && precedence(operators->node->data.operator) >= precedence(expression[i])) {
                Node *right = pop(&operands);
                Node *left = pop(&operands);
                Node *op = pop(&operators);
                op->left = left;
                op->right = right;
                push(&operands, op);
            }
            push(&operators, createNode(OPERATOR, 0, expression[i]));
        }
    }
    while (operators != NULL) {
        Node *right = pop(&operands);
        Node *left = pop(&operands);
        Node *op = pop(&operators);
        op->left = left;
        op->right = right;
        push(&operands, op);
    }
    return pop(&operands);
}

// Функция для обмена местами операндов у операций сложения и умножения
void swapOperands(Node *root) {
    if (root == NULL) {
        return;
    }
    if (root->type == OPERATOR && (root->data.operator == '+' || root->data.operator == '*')) {
        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    swapOperands(root->left);
    swapOperands(root->right);
}

// Функция для печати дерева (рекурсивно)
void printTree(Node *root, int depth) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (root->type == OPERAND) {
        printf("%.2lf\n", root->data.operand);
    } else {
        printf("%c\n", root->data.operator);
    }
    printTree(root->left, depth + 1);
}

// Функция для печати выражения в инфиксной нотации (рекурсивно)
void printExpression(Node *root) {
    if (root == NULL) {
        return;
    }
    if (root->type == OPERAND) {
        printf("%.2lf", root->data.operand);
    } else {
        printf("(");
        printExpression(root->left);
        printf(" %c ", root->data.operator);
        printExpression(root->right);
        printf(")");
    }
}

int main() {
    char expression[256];
    printf("Введите выражение: ");
    fgets(expression, 256, stdin);
    expression[strcspn(expression, "\n")] = '\0';

    Node *root = shuntingYard(expression);
    printf("Исходное дерево выражения:\n");
    printTree(root, 0);
    //printf("Исходное выражение: ");
    //printExpression(root);
    printf("\n");

    swapOperands(root);
    printf("Измененное дерево выражения:\n");
    printTree(root, 0);
    printf("Измененное выражение: ");
    printExpression(root);
    printf("\n");

    return 0;
}
