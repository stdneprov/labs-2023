#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "tree.h"
#include <stdbool.h>

void PrintResult(Node* root) {
    // печатаем лист
    if (root->left == NULL && root->right == NULL) {
        if (root->type == SYMB) {
            printf("%c", *root->data.symb);
        } else if (root->type == VAR) {
            printf("%s", root->data.symb);
        } else {
            printf("%d", root->data.num);
        }
        return;
    } 
    // печатаем скобки
    if (root->left != NULL) {
        printf("(");
        PrintResult(root->left);
    }
    // печатаем внутри скобок
    if (root->type == SYMB) {
        printf("%c", *root->data.symb);
    } else if (root->type == VAR) {
        printf("%s", root->data.symb);
    } else {
        printf("%d", root->data.num);
    }
    if (root->right != NULL) {
        PrintResult(root->right);       
        printf(")");
    }
}

bool IsOperator(char a){
    return (a == '+' || a == '-' || a  == '/' || a == '*' || a == '^');
}

void ChangeDivision(Node *root) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL && root->right != NULL) {
        ChangeDivision(root->right);
        ChangeDivision(root->left);

        if (*root->data.symb == '/' && root->right->type == SYMB && *root->right->data.symb == '^') {
            // меняем деление на умножение
            *root->data.symb = '*';

            // меняем степень на отрицательную
            Node* exponentNode = root->right;
            Node* powerNode = exponentNode->right;

            if (powerNode->type == NUM) {
                powerNode->data.num = -powerNode->data.num;
            } else {
                // создаём два новых узла для умножения выражения на -1
                Node* newPowerNode = CreateNode((variable){.num = -1}, NUM);
                Node* multiplyNode = CreateNode((variable){.symb = "*"}, SYMB);

                multiplyNode->left = newPowerNode;
                multiplyNode->right = powerNode;
                exponentNode->right = multiplyNode;
            }
        }
    }
}

void StackToTree(Stack *stk, Node *root) {
    while (stk->top != NULL && (root->left == NULL || root->right == NULL)) {
        // дерево пустое справа
        if (root->right == NULL) {
            if (stk->top->type == SYMB) {
                // добавляем верх стека справа
                root->right = AddNode(root, StackPop(stk), stk->top->type);
                StackToTree(stk, root->right);
            } else {
                root->right = AddNode(root, StackPop(stk), stk->top->type);
            }
        // слева то же самое
        } else {
            if (stk->top->type == SYMB) {
                root->left = AddNode(root, StackPop(stk), stk->top->type);
                StackToTree(stk, root->left);
            } else {
                root->left = AddNode(root, StackPop(stk), stk->top->type);
            }
        }
    }
}
void Second(Node **tree) {
    if (tree == NULL) {
        return;
    }
        if ((*tree)->type != NUM && *(*tree)->data.symb == '/') { 
            if ((*tree)->left->type != NUM && (*tree)->right->type != NUM && *(*tree)->left->data.symb == '/' && *(*tree)->right->data.symb == '/') {
                *(*tree)->left->data.symb = '*';
                *(*tree)->right->data.symb = '*';
                Node *tmp = (Node *)malloc(sizeof(Node));
                Node *mtp = (Node *)malloc(sizeof(Node));
                tmp = (*tree)->left->right;
                mtp = (*tree)->right->right;
                (*tree)->left->right = mtp;
                (*tree)->right->right = tmp;
            } else if ((*tree)->left->type != NUM && *(*tree)->left->data.symb == '/') {
                Node *tmp = (Node *)malloc(sizeof(Node));
                Node *mtp = (Node *)malloc(sizeof(Node));
                tmp = (*tree)->left->right;
                (*tree)->left = (*tree)->left->left;
                Stack a = StackInit();
                StackPush(&a, '*', SYMB);
                mtp->data = StackPop(&a);
                mtp->type = SYMB;
                mtp->left = (*tree)->right;
                mtp->right = tmp;
                (*tree)->right = mtp;
            } else if ((*tree)->right->type != NUM && *(*tree)->right->data.symb == '/') {
                Node *tmp = (Node *)malloc(sizeof(Node));
                Node *mtp = (Node *)malloc(sizeof(Node));
                tmp = (*tree)->right->right;
                (*tree)->right = (*tree)->right->left;
                Stack a = StackInit();
                StackPush(&a, '*', SYMB);
                mtp->data = StackPop(&a);
                mtp->type = SYMB;
                mtp->left = (*tree)->left;
                mtp->right = tmp;
                (*tree)->left = mtp;
            }
        }
}

void First(Node* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->right != NULL) {
        First(tree->right);
    }
    if (tree->right != NULL) {
        First(tree->left);
    }
    Second(&tree);
}

void ReadExpr(){
    Stack operators = StackInit();
    Stack values = StackInit();
    char symbol = ' ';
    int prevSymbol = 1;  // 1 oper, 0 num, -1 var
    int ind = 0;  // отслеживает позицию в массиве var

    while (symbol != EOF && symbol != '\n'){
        if (symbol != ' ') {
            if (IsOperator(symbol) && prevSymbol != 1) {
                prevSymbol = 1;
                // пока топ стека опретаторов не равен ( и равен *, / или ^ и сам символ не равен им
                while (!StackIsEmpty(&operators) && *StackTop(&operators).symb != '(' && 
                       ((*StackTop(&operators).symb == '*' || *StackTop(&operators).symb == '/' || 
                       *StackTop(&operators).symb == '^') || (symbol != '*' && symbol != '/' && symbol != '^'))) {
                    // пушим этот топ в итоговый стек
                    StackPush(&values, *StackPop(&operators).symb, SYMB);
                }
                // пушим символ в итоговый стек
                StackPush(&operators, symbol, SYMB);
            } else if (symbol == '(') {
                StackPush(&operators, symbol, SYMB);
            } else if (symbol == ')') {
                while (*StackTop(&operators).symb != '(') {
                    StackPush(&values, *StackPop(&operators).symb, SYMB);
                }
                StackPop(&operators);
            } else {
                // и прошлый и текущий - num
                if (prevSymbol == 0 && isdigit(symbol)) {
                    values.top->value.num = values.top->value.num * 10 + (symbol - '0');
                    prevSymbol = 0;
                // прошлый - oper    
                } else if (prevSymbol == -1) {
                    ind++;
                    values.top->value.symb = realloc(values.top->value.symb, ind + 1);
                    if (values.top->value.symb == NULL) {
                        exit(-1);
                    }
                    // добавляем символ в массив var
                    values.top->value.symb[ind - 1] = symbol;
                    values.top->value.symb[ind] = '\0';
                } else {
                    if (isdigit(symbol)) {
                        StackPush(&values, (symbol - '0'), NUM);
                        prevSymbol = 0;
                    } else {
                        StackPush(&values, symbol, VAR);
                        prevSymbol = -1;
                        ind = 1;
                        values.top->value.symb = realloc(values.top->value.symb, ind + 1);
                        if (values.top->value.symb == NULL) {
                            exit(-1);
                        }
                        values.top->value.symb[ind - 1] = symbol;
                        values.top->value.symb[ind] = '\0';
                    }
                }
            }
        } 
    symbol = getchar();
    }
    while (operators.top != NULL) {
        StackPush(&values, *operators.top->value.symb, operators.top->type);
        StackPop(&operators);
    }
    printf("stack: ");
    StackPrint(&values);

    Node root;
    root = *CreateNode(StackPop(&values), SYMB);
    StackToTree(&values, &root);
    printf("\ntree before:\n");
    TreePrint(&root, 0);

    First(&root);
    printf("tree after:\n");
    TreePrint(&root, 0);

    printf("modified expression: ");
    PrintResult(&root);

    TreeFree(&root);
}

int main() {
    ReadExpr();
}