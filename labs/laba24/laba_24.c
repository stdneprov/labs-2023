#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef enum {
    VAR, CONST, OP
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        double value;
        char varName[50];
        char op;
    };
    struct Node* left;
    struct Node* right;
} Node;

Node* CreateNode(NodeType type) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void FreeTree(Node* root) {
    if (root != NULL) {
        FreeTree(root->left);
        FreeTree(root->right);
        free(root);
    }
}

typedef struct {
    Node* nodes[100];
    int size;
} NodeStack;

void PushNode(NodeStack* stack, Node* node) {
    stack->nodes[stack->size++] = node;
}

Node* PopNode(NodeStack* stack) {
    return stack->nodes[--stack->size];
}

Node* PeekNode(NodeStack* stack) {
    return stack->nodes[stack->size - 1];
}

typedef struct {
    char ops[100];
    int size;
} CharStack;

void PushChar(CharStack* stack, char op) {
    stack->ops[stack->size++] = op;
}

char PopChar(CharStack* stack) {
    return stack->ops[--stack->size];
}

char PeekChar(CharStack* stack) {
    return stack->ops[stack->size - 1];
}

int Precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

Node* BuildExpressionTree(const char* expr) {
    NodeStack nodeStack = { .size = 0 };
    CharStack opStack = { .size = 0 };
    int i = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || (expr[i] == '.' && isdigit(expr[i + 1]))) {
            char number[50];
            int j = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                number[j++] = expr[i++];
            }
            number[j] = '\0';
            Node* node = CreateNode(CONST);
            node->value = atof(number);
            PushNode(&nodeStack, node);
        }
        else if (isalpha(expr[i])) {
            char var[50];
            int j = 0;
            while (isalnum(expr[i])) {
                var[j++] = expr[i++];
            }
            var[j] = '\0';
            Node* node = CreateNode(VAR);
            strcpy(node->varName, var);
            PushNode(&nodeStack, node);
        }
        else if (expr[i] == '(') {
            PushChar(&opStack, expr[i]);
            i++;
        }
        else if (expr[i] == ')') {
            while (opStack.size > 0 && PeekChar(&opStack) != '(') {
                char op = PopChar(&opStack);
                Node* node = CreateNode(OP);
                node->op = op;
                node->right = PopNode(&nodeStack);
                node->left = PopNode(&nodeStack);
                PushNode(&nodeStack, node);
            }
            PopChar(&opStack);
            i++;
        }
        else if (IsOperator(expr[i])) {
            while (opStack.size > 0 && Precedence(PeekChar(&opStack)) >= Precedence(expr[i])) {
                char op = PopChar(&opStack);
                Node* node = CreateNode(OP);
                node->op = op;
                node->right = PopNode(&nodeStack);
                node->left = PopNode(&nodeStack);
                PushNode(&nodeStack, node);
            }
            PushChar(&opStack, expr[i]);
            i++;
        }
        else {
            fprintf(stderr, "Недопустимый символ в выражении: %c\n", expr[i]);
            exit(EXIT_FAILURE);
        }
    }

    while (opStack.size > 0) {
        char op = PopChar(&opStack);
        Node* node = CreateNode(OP);
        node->op = op;
        node->right = PopNode(&nodeStack);
        node->left = PopNode(&nodeStack);
        PushNode(&nodeStack, node);
    }

    return PopNode(&nodeStack);
}

Node* TransformTree(Node* root) {
    if (root == NULL) return NULL;

    root->left = TransformTree(root->left);
    root->right = TransformTree(root->right);


    if (root->type == OP) {
        if (root->op == '+' || root->op == '*') {
            Node* temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
    }

    return root;
}

void PrintExpressionTree(Node* root) {
    if (root == NULL) return;

    if (root->type == CONST) {
        printf("%lf", root->value);
    }
    else if (root->type == VAR) {
        printf("%s", root->varName);
    }
    else if (root->type == OP) {
        printf("(");
        PrintExpressionTree(root->left);
        printf(" %c ", root->op);
        PrintExpressionTree(root->right);
        printf(")");
    }
}

int main() {
    char expression[100];

    printf("Введите выражение: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        fprintf(stderr, "Ошибка считывания входных данных.\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    Node* tree = BuildExpressionTree(expression);
    tree = TransformTree(tree);

    printf("Преобразованное выражение: ");
    PrintExpressionTree(tree);
    printf("\n");

    FreeTree(tree);
    return 0;
}
