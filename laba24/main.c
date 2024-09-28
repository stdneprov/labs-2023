#include <stdlib.h>
#include "tree.h"
#include "stack.h"



//Проверка на операцию
int IsOperation(char c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') ;
}


//Перевод в дерево
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

void Function(Node* tree) {
    if (tree == NULL) {
        return;
    }

    Function(tree->left);
    Function(tree->right);

    if (tree->type == SYMB && *tree->value.symb == '-') {
        
        union data addValue;
        addValue.symb = malloc(2 * sizeof(char));
        *addValue.symb = '+';
        addValue.symb[1] = '\0';
        Node* newAddNode = CreateNode(addValue, SYMB);

        
        union data negValue;
        negValue.symb = malloc(2 * sizeof(char));
        *negValue.symb = '-';
        negValue.symb[1] = '\0';
        Node* newNegNode = CreateNode(negValue, SYMB);

        
        newNegNode->right = tree->right;
        newAddNode->left = tree->left;
        newAddNode->right = newNegNode;

        
        tree->type = newAddNode->type;
        tree->value = newAddNode->value;
        tree->left = newAddNode->left;
        tree->right = newAddNode->right;
    }
}


//Вывод
void PrintResult(Node* tree, bool isRoot) {
    if (tree == NULL) return;
    
    if (!isRoot && (tree->left != NULL || tree->right != NULL)) printf("(");
    
    if (tree->left != NULL) PrintResult(tree->left, false);

    if (tree->type == SYMB) {
        printf("%c", *tree->value.symb);
    } else if (tree->type == VAR) {
        printf("%s", tree->value.symb);
    } else {
        printf("%d", tree->value.num);
    }

    if (tree->right != NULL) PrintResult(tree->right, false);
    
    if (!isRoot && (tree->left != NULL || tree->right != NULL)) printf(")");
    
}

//Считываем
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
    Node* tree = CreateNode(values.top->value, values.top->type);
    StackPop(&values);
    StackToTree(&values, tree);
    printf("-----------------------TREE------------------------\n");
    PrintTree(tree);

    Function(tree);
    printf("-----------------------TREE------------------------\n");
    PrintTree(tree);
    PrintResult(tree, true);
    printf("\n");
    StackFree(&values);
    TreeFree(tree);
}

int main() {
    ReadFormula();
}