#include <stdlib.h>
#include "tree.h"
#include "stack.h"
char oper = 42; 
int IsOperation(char c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') ;
}

void StackToTree(Stack* stk, Node* curNode) {
    while (stk->top != NULL && (curNode->left == NULL || curNode->right == NULL)) {
        if (curNode->right == NULL) {
            if (stk->top->type == SYMB) {
                curNode->right = AddNode(StackPop(stk), stk->top->type);
                StackToTree(stk, curNode->right);
            } else {
                curNode->right = AddNode(StackPop(stk), stk->top->type);
            }
        } else {
            if (stk->top->type == SYMB) {
                curNode->left = AddNode(StackPop(stk), stk->top->type);
                StackToTree(stk, curNode->left);
            } else {
                curNode->left = AddNode(StackPop(stk), stk->top->type);
            }
        }
    }
}

void ReplaceMultSum(Node** tree) {
    if ((*tree)->type == SYMB) {
        ReplaceMultSum(&((*tree)->left));
        ReplaceMultSum(&((*tree)->right));
        if (*((*tree)->value.symb) == '*') {
            if ((*tree)->right->type == NUM) {
                int n = (*tree)->right->value.num;
                if (n == 0){
                    free((*tree)->left);
                    free((*tree)->right);
                    (*tree)->left = NULL;
                    (*tree)->right = NULL;
                    (*tree)->type = NUM;
                    (*tree)->value.num = 0;
                } else if (n == 1) {
                    (*tree)->type = (*tree)->left->type;
                    (*tree)->value = (*tree)->left->value;
                    free((*tree)->left);
                    free((*tree)->right);
                    (*tree)->left = NULL;
                    (*tree)->right = NULL;
                } else if (n == 2) {
                    (*tree)->right->type = (*tree)->left->type;
                    (*tree)->right->value = (*tree)->left->value;
                    *((*tree)->value.symb) = '+';
                } else if (n > 2) {
                    *((*tree)->value.symb) = '+';
                    type t = (*tree)->left->type;
                    union data v = (*tree)->left->value;
                    free((*tree)->left);
                    (*tree)->right->type = t;
                    (*tree)->right->value = v;
                    Node* node = *tree;
                    for(int i = 0; i < n - 2; i++) {
                        Node* new = CreateNode((*tree)->value, SYMB);
                        node->left = new;
                        Node* val = CreateNode(v, t);
                        new->right = val;
                        if (i == n - 3) {
                            Node* val2 = CreateNode(v, t);
                            new->left = val2;
                        } else {
                            node = new;
                        }
                    }
                }   
            }
        }
    } 
}

void PrintResult(Node* tree) {
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->type == SYMB) {
            printf("%c", *tree->value.symb);
        } else if (tree->type == VAR) {
            printf("%s", tree->value.symb);
        } else {
            printf("%d", tree->value.num);
        }
        return;
    } 
    if (tree->left != NULL) {
        printf("(");
        PrintResult(tree->left);
    }
    if (tree->type == SYMB) {
        printf("%c", *tree->value.symb);
    } else if (tree->type == VAR) {
        printf("%s", tree->value.symb);
    } else {
        printf("%d", tree->value.num);
    }
    if (tree->right != NULL) {
        PrintResult(tree->right);       
        printf(")");
    }
}

void ReadFormula() {
    Stack operations = StackInit();
    Stack values = StackInit();
    char symbol = ' ';
    int prevSymbol = 1;
    int ind = 0;
    while (symbol != EOF && symbol != '\n') {   
        if (symbol != ' ') {
            if (IsOperation(symbol) && prevSymbol != 1) {
                prevSymbol = 1;
                switch (symbol)
                {
                case '+':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb != '(') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '+', SYMB);
                    } else {
                        StackPush(&operations, '+', SYMB);
                    }
                    break;
                case '-':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb != '(') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '-', SYMB);

                    } else {
                        StackPush(&operations, '-', SYMB);
                    }
                    break;
                case '*':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb == '*' || *operations.top->value.symb == '/' || *operations.top->value.symb == '^') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '*', SYMB);

                    } else {
                        StackPush(&operations, '*', SYMB);
                    }
                    break;
                case '/':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb == '*' || *operations.top->value.symb == '/' || *operations.top->value.symb == '^') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '/', SYMB);
                    } else {
                        StackPush(&operations, '/', SYMB);
                    }
                    break;
                case '^':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb == '^') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '^', SYMB);
                    } else {
                        StackPush(&operations, '^', SYMB);
                    }
                    break;

                default:
                    break;
                }
            } else if (symbol == '(') {
                StackPush(&operations, symbol, SYMB);
            } else if (symbol == ')') {
                while (*operations.top->value.symb != '(')
                {
                    StackPush(&values, *operations.top->value.symb, operations.top->type);
                    StackPop(&operations);
                }
                StackPop(&operations);
            } else {// если число
               if (prevSymbol == 0 && symbol <= '9' && symbol >= '0') {
                    if (symbol != '0') {
                        values.top->value.num = values.top->value.num * 10 + (symbol - '0');
                        prevSymbol = 0;
                    } else {
                        values.top->value.num = values.top->value.num * 10;
                        prevSymbol = 0;
                    }
                } else if (prevSymbol == -1) {
                    char *buff;
                    values.top->value.symb = realloc(values.top->value.symb, sizeof(values.top->value.symb) + sizeof(char));
                    ind++;
                    values.top->value.symb[ind] = symbol;
                } else {
                    if (symbol <= '9' && symbol >= '0') {
                        StackPush(&values, (symbol - '0'), NUM);
                        prevSymbol = 0;
                    } else {
                        StackPush(&values, symbol, VAR);
                        prevSymbol = -1;
                        ind = 0;
                    }
                }

            }
        }
    symbol = getchar();
    }
    while (StackIsEmpty(&operations) != true) {
        StackPush(&values, *operations.top->value.symb, operations.top->type);
        StackPop(&operations);
    }

    printf("-----------------------STACK-----------------------\n");
    StackPrint(&values);
    Node* tree = CreateNode(values.top->value, values.top->type);
    StackPop(&values);
    StackToTree(&values, tree);
    printf("-----------------------TREE------------------------\n");
    PrintTree(tree);
    ReplaceMultSum(&tree);
    printf("-------------------MODIFIED_TREE-------------------\n");
    PrintTree(tree);
    printf("----------------------RESULT-----------------------\n");
    PrintResult(tree);
    printf("\n");
    StackFree(&values);
    TreeFree(tree);
}

int main() {
    ReadFormula();
}