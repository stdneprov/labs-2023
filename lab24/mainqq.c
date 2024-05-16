#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include <stdbool.h>



void PrintResult(Node* tree) {
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->type == SYMB) {
            printf("%c", *tree->key.symb);
        } else if (tree->type == VAR) {
            printf("%s", tree->key.symb);
        } else {
            printf("%d", tree->key.num);
        }
        return;
    } 
    if (tree->left != NULL) {
        printf("(");
        PrintResult(tree->left);
    }
    if (tree->type == SYMB) {
        printf("%c", *tree->key.symb);
    } else if (tree->type == VAR) {
        printf("%s", tree->key.symb);
    } else {
        printf("%d", tree->key.num);
    }
    if (tree->right != NULL) {
        PrintResult(tree->right);       
        printf(")");
    }
}

bool IsOperator(char a){
    return (a == '+' || a == '-' || a  == '/' || a == '*' || a == '^');
}

void DeletDividerOne(Node *tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->left != NULL && tree->right != NULL) {
        DeletDividerOne(tree->right);
        DeletDividerOne(tree->left);
        if (tree->left->type == SYMB){
            if (*tree->key.symb == '/' && tree->right->key.num == 1) {
                tree->type = SYMB;
                tree->right = tree->left->right;
                tree->key.symb = tree->left->key.symb;
                tree->key = tree->left->key;
                tree->left = tree->left->left;
            }
        }
        if (*tree->key.symb == '/' && tree->right->key.num == 1) {
            tree->type = tree->left->type;
            tree->right = NULL;
            tree->key.symb = NULL;
            tree->key = tree->left->key;
            tree->left = NULL;

        } 
    }
    DeletDividerOne(tree->right);
    DeletDividerOne(tree->left);
}

void StackToTree(Stack *stk, Node *tree) {
    while (stk->top != NULL && (tree->left == NULL || tree->right == NULL)) {
        if (tree->right == NULL) {
            if (stk->top->type == SYMB) {
                tree->right = TreeAdd(tree, StackPop(stk), stk->top->type);
                StackToTree(stk, tree->right);
            } else {
                tree->right = TreeAdd(tree, StackPop(stk), stk->top->type);
            }
        } else {
            if (stk->top->type == SYMB) {
                tree->left = TreeAdd(tree, StackPop(stk), stk->top->type);
                StackToTree(stk, tree->left);
            } else {
                tree->left = TreeAdd(tree, StackPop(stk), stk->top->type);
            }
        }
    }
}

void ReadForm(){
    Stack operators = StackInit();
    Stack values = StackInit();
    char symbol = ' ';
    while (symbol != EOF && symbol != '\n'){
        if (symbol != ' ') {
            if (IsOperator(symbol)) {
                switch (symbol) {
                    case '+':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb != '(') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, symbol, SYMB);
                        } else {
                            StackPush(&operators, symbol, SYMB);
                        }
                        break;
                    case '-':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb != '(') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, symbol, SYMB);
                        } else {
                            StackPush(&operators, symbol, SYMB);
                        }
                        break;
                    case '*':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb == '*' || *StackTop(&operators).symb == '/' || *StackTop(&operators).symb == '^') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, symbol, SYMB);
                        } else {
                            StackPush(&operators, symbol, SYMB);
                        }
                        break;
                    case '/':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb == '*' || *StackTop(&operators).symb == '/' || *StackTop(&operators).symb == '^') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, symbol, SYMB);
                        } else {
                            StackPush(&operators, symbol, SYMB);
                        }
                        break;
                    case '^':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb == '^') {
                            StackPush(&values, *StackPop(&operators).symb, SYMB);
                            if (operators.top == NULL) {
                                break;
                                }
                            }
                            StackPush(&operators, '^', SYMB);

                        } else {
                            StackPush(&operators, '^', SYMB);
                        }
                        break;

                    default:
                        break;
                }
            }else if (symbol == '(') {
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
                    buf = buf * 10 + (symbol - '0');
                    symbol = getchar();
                }
                StackPush(&values, buf, NUM);
                if (symbol == ')') {
                    while (*StackTop(&operators).symb != '(') {
                        StackPush(&values, *StackPop(&operators).symb, SYMB);
                    }
                StackPop(&operators);
                }
            } else {
                StackPush(&values, symbol, VAR);
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
    StackPrint(&values);
    Node tree;
    tree = *CreateNode(StackPop(&values), SYMB);
    StackToTree(&values, &tree);
    printf("\n");
    TreePrint(&tree, 0);
    DeletDividerOne(&tree);
    printf("\n");
    TreePrint(&tree, 0);
    PrintResult(&tree);
}

int main() {
    ReadForm();
}