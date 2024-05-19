#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include <stdbool.h>

void PrintResult(Node* root) {
    // печатаем лист
    if (root->left == NULL && root->right == NULL) {
        printf("%d", root->data.num);
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

void ReadExpr(){
    Stack operators = StackInit();
    Stack values = StackInit();
    char symbol = ' ';
    while (symbol != EOF && symbol != '\n'){
        if (symbol != ' ') {
            if (IsOperator(symbol)) {
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
            } else if (symbol >= '0' && symbol <= '9') {
                int buf = 0;
                while (1) {
                    if (symbol == ' ' || symbol == '\n' || symbol == ')') {
                        break;
                    }
                    // делаем из чара инт
                    buf = buf * 10 + (symbol - '0');
                    symbol = getchar();
                }
                // и пушим его в итоговый стек
                StackPush(&values, buf, NUM);
                if (symbol == ')') {
                    while (*StackTop(&operators).symb != '(') {
                        StackPush(&values, *StackPop(&operators).symb, SYMB);
                    }
                StackPop(&operators);
                }
            }
        } 
    if (symbol == '\n') {
        break;
    }
    symbol = getchar();
    }
    while (operators.top != NULL) {
        StackPush(&values, *operators.top->value.symb, SYMB);
        StackPop(&operators);
    }
    printf("stack: ");
    StackPrint(&values);

    Node root;
    root = *CreateNode(StackPop(&values), SYMB);
    StackToTree(&values, &root);
    printf("\ntree before:\n");
    TreePrint(&root, 0);

    ChangeDivision(&root);
    printf("tree after:\n");
    TreePrint(&root, 0);

    printf("modified expression: ");
    PrintResult(&root);
}

int main() {
    ReadExpr();
}