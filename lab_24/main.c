#include <stdlib.h>
#include "tree.h"
#include "stack.h"
//убрать все сомножители равные единице
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

void DeleteMulOnes(Node* tree, Node* parent, Node* preparent) {
    if (tree->type == SYMB) {
        if (*tree->value.symb == '*') {
            if (tree->left->type == NUM) {
                if (tree->left->value.num == 1) {
                    free(tree->left);
                    tree->left = tree->right->left;
                    tree->type = tree->right->type;
                    tree->value = tree->right->value;
                    tree->right = tree->right->right;
                    if (tree->type == SYMB) {
                        DeleteMulOnes(tree, parent, preparent);
                    }
                    DeleteMulOnes(parent, preparent, preparent);
                    return;
                } 
            }
            if (tree->right->type == NUM) {
                if (tree->right->value.num == 1) {
                    free(tree->right);
                    tree->type = tree->left->type;
                    tree->right = tree->left->right;
                    tree->value = tree->left->value;
                    tree->left = tree->left->left;
                    if (tree->type == SYMB) {
                        DeleteMulOnes(tree, parent, preparent);
                    }
                    DeleteMulOnes(parent, preparent, preparent);
                    return;
                } 
            }
            
        } 
        if (tree->left != NULL && tree->left->type == SYMB) {
            if (IsOperation(*tree->left->value.symb)) {
                DeleteMulOnes(tree->left, tree, preparent);
            }
        } 
        if (tree->right != NULL && tree->right->type == SYMB) {
            if (IsOperation(*tree->right->value.symb)) {
                DeleteMulOnes(tree->right, tree, preparent);
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
               if (prevSymbol == 0 && symbol <= '9' && symbol >= '1') {
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
                    if (symbol <= '9' && symbol >= '1') {
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
    //крутой вывод закоменчен((
        
    //printf("-----------------------STACK-----------------------\n");
    //StackPrint(&values);
    Node* tree = CreateNode(values.top->value, values.top->type);
    StackPop(&values);
    StackToTree(&values, tree);
    //printf("-----------------------TREE------------------------\n");
    //PrintTree(tree);
    DeleteMulOnes(tree, tree, tree);
    //printf("-------------------MODIFIED_TREE-------------------\n");
    //PrintTree(tree);
    //printf("----------------------RESULT-----------------------\n");
    PrintResult(tree);
    printf("\n");
    StackFree(&values);
    TreeFree(tree);
}

int main() {
    ReadFormula();
}