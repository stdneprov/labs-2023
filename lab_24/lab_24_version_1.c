#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Token{
    unsigned value;
    char operation;
    unsigned tokentype;
};

struct Stack{
    struct Token* nodes;
    unsigned capacity; //зарезервированная память
    unsigned size; //размер
};

void initStack(struct Stack* q){
    q->capacity = 2; //выделяем под 2 элемента
    q->size = 0;
    q->nodes = (struct Token*)malloc(sizeof (struct Token)*q->capacity);
};

void push_back(struct Stack* q, struct Token element){
    //если лишнего места уже нет, то его нужно добавить
    if(q->size == q->capacity){
        q->capacity *= 2;
        q->nodes = (struct Token*)realloc(q->nodes, sizeof(struct Token) * q->capacity ); //повышаем резерв
    }
    q->nodes[q->size++] = element;
}

struct Token pop(struct Stack* q){
    if(!q->size){
        struct Token tok;
        return tok;
    }
    return q->nodes[--q->size];
}

struct Node{
    struct Token object;
    struct Node* right;
    struct Node* left;
};

struct Tree {
    struct Node* root;
};

//вершина
struct Token peak(struct Stack* q) {
    return q->nodes[q->size - 1];
}

//приоритет операций
int priority_of_operation(char a) {
    if (a == '+' || a == '-') {
        return 0;
    }
    if (a == '*' || a == '/') {
        return 1;
    }
    return 2;
}

void Print_Stack(struct Stack* s) {
    for (int i = 0; i < s->size; i++) {
        //если операция
        if (s->nodes[i].tokentype == 0) {
            printf("%c ", s->nodes[i].operation);
        } else if (s->nodes[i].tokentype == 1) { //если число
            printf("%u ",s->nodes[i].value);
        } else printf("%c ",s->nodes[i].operation); //если операция
    }
    printf("\n");
}

void initTree(struct Tree* t) {
    t->root = NULL;
}

struct Node* subInsert(struct Node* node, struct Stack* s){
    
    if (node == NULL) {
            node = (struct Node*)malloc(sizeof(struct Node));
            node->object = pop(s);
            node->left = NULL;
            node->right = NULL;
            if (node->object.tokentype == 1 || node->object.tokentype == 2) {
                return node;
            }
    }
    if (!node->right || (node->right && node->right->object.tokentype == 0)) {
            node->right = subInsert(node->right, s);
    }
    if (!node->left || (node->left && node->left->object.tokentype == 0)) {
            node->left = subInsert(node->left, s);
    }
    return node;
}

void insert(struct Tree* t, struct Stack* s) {
    if (!t->root){
        t->root = (struct Node*)malloc(sizeof(struct Node));
        t->root->object = pop(s);
        t->root->right=NULL;
        t->root->left=NULL;
    }
    //если что-то есть
    if (s->size > 0) {
        t->root = subInsert(t->root, s);
    }
}

//выводы
void printElement(struct Token element) {
    if (element.tokentype == 0) {
        printf("%c",element.operation);
    }
    else if (element.tokentype == 1 ) {
        printf("%u",element.value);
    } else printf("%c",element.operation);
}

void printTree(struct Node* node) {
    if(!node->left && !node->right) {
        printElement(node->object);
        return;
    }
    if(node->left) {
        printTree(node->left);
    }
    printElement(node->object);
    if(node->right) {
        printTree(node->right);
    }
    
}

//чистим память
void sub_freeTree(struct Tree* t,struct Node* node) {
    if(!node->left && !node->right) {
        free(node);
        return;
    }
    if(node->left) {
        sub_freeTree(t,node->left);
    }
    if(node->right) {
        sub_freeTree(t,node->right);
    }
    free(node);
}
void freeTree(struct Tree* t) {
    if (t->root->left) {
        sub_freeTree(t,t->root->left);
    }
    if (t->root->right) {
        sub_freeTree(t,t->root->right);
    }
    free(t->root);
}
struct Tree t;

// int compare(struct Node *one, struct Node *two) {
//     int fatal = 0;
//     while (one && two) {
//         if (one->object.tokentype != two->object.tokentype) {
//             fatal = 1;
//             break;
//         } else if (one->object.operation != two->object.operation) {
//             fatal = 1;
//             break;
//         } else if (one->object.value != two->object.value) {
//             fatal = 1;
//             break;
//         } else {
//             one = one->left;
//             two = two->left;
//         }
//     }
//     while (one && two) {
//         if (one->object.tokentype != two->object.tokentype) {
//             fatal = 1;
//             break;
//         } else if (one->object.operation != two->object.operation) {
//             fatal = 1;
//             break;
//         } else if (one->object.value != two->object.value) {
//             fatal = 1;
//             break;
//         } else {
//             one = one->right;
//             two = two->right;
//         }
//     }
//     if (fatal == 0) {
//         return 1;
//     } else {
//         return 0;
//     }
    
    
// }
int error = 1;
int Task(struct Node* node1, struct Node* node2){
    if ((node1->object.tokentype == 0 && node2->object.tokentype == 0) && (node1->object.
    operation == '*' && node2->object.operation == '*')) {
        int one = 0;
        int two = 10; 
        int three = 110;
        int four = 1110;
        struct Node* one_m;
        struct Node* two_m;
        struct Node* three_m;
        struct Node* four_m;    
        if (node1->left->object.tokentype == 2) {
            one = node1->left->object.operation;
        } else if (node1->left->object.tokentype == 1) {
            one = node1->left->object.value;
        } else {
            one_m = t.root->left->left;
        }

        if (node1->right->object.tokentype == 2) {
            two = node1->right->object.operation;
        } else if (node1->right->object.tokentype == 1) {
            two = node1->right->object.value;
        } else {
            two_m = t.root->left->right;
        }

        if (node2->left->object.tokentype == 2) {
            three = node2->left->object.operation;
        } else if (node2->left->object.tokentype == 1) {
            three = node2->left->object.value;
        } else {
            three_m = t.root->right->left;
        }

        if (node2->right->object.tokentype == 2) {
            four = node2->right->object.operation;
        } else if (node2->right->object.tokentype == 1) {
            four = node2->right->object.value;
        } else {
            four_m = t.root->right->right;
        }




        //замена
        int povtor = 0;
        int second = 0;


        if (one == three) {
            // printf("YES");
            povtor = one;
            second = two;
            if (node1->left->object.tokentype == 2) {
                node1->object.tokentype = 2;
                node1->object.operation = povtor;
            } else if (node1->left->object.tokentype == 1){
                node1->object.tokentype = 1;
                node1->object.value = povtor;
            }
            node1->left = NULL;
            if (node1->right->object.tokentype == 2) {
                node2->left->object.tokentype = 2;
                node2->left->object.operation = second;
            } else if (node1->right->object.tokentype == 1){
                node2->left->object.tokentype = 1;
                node2->left->object.value = second;
            } else {

                node2->left = two_m;

            }
            node1->right = NULL;
            node2->object.operation = '+';
            error = 0;
            return 1;
        } else if (one == four) {
            // printf("YES");
            povtor = one;
            second = two;
            if (node1->left->object.tokentype == 2) {
                node1->object.tokentype = 2;
                node1->object.operation = povtor;
            } else if (node1->left->object.tokentype == 1){
                node1->object.tokentype = 1;
                node1->object.value = povtor;
            }
           

            node1->left = NULL;
            // if (node2->left->object.tokentype == 2) {
            //     node2->right->object.tokentype = 2;
            //     node2->right->object.operation = node2->left->object.operation;
            // } else if (node2->left->object.tokentype == 1) {
            //     node2->right->object.tokentype = 1;
            //     node2->right->object.value = node2->left->object.value;
            // } else {
            //         node2->right = three_m;
            // }

            if (node1->right->object.tokentype == 2) {
                node2->right->object.tokentype = 2;
                node2->right->object.operation = second;
            } else if (node1->right->object.tokentype == 1){
                node2->right->object.tokentype = 1;
                node2->right->object.value = second;
            } else {
                node2->right = two_m;
            }
            node1->right = NULL;
            node2->object.operation = '+';
            error = 0;
            return 1;
        } else if (two == four) {
            // printf("YES");
            povtor = two;
            second = one;
            if (node1->right->object.tokentype == 2) {
                node1->object.tokentype = 2;
                node1->object.operation = povtor;
            } else if (node1->right->object.tokentype == 1){
                node1->object.tokentype = 1;
                node1->object.value = povtor;
            }

            node1->right = NULL;


            if (node1->left->object.tokentype == 2) {
                
                node2->right->object.tokentype = 2;
                node2->right->object.operation = second;
            } else if (node1->left->object.tokentype == 1){
                
                node2->right->object.tokentype = 1;
                node2->right->object.value = second;
            } else {
                // printf("WIN");
                node2->right = one_m;
            }
            node1->left = NULL;
            node2->object.operation = '+';
            error = 0;
            return 1;

        } else if (two == three) {
            // printf("YES\n");
            povtor = two;
            second = one;
            if (node1->right->object.tokentype == 2) {
                node1->object.tokentype = 2;
                node1->object.operation = povtor;
            } else if (node1->right->object.tokentype == 1){
                node1->object.tokentype = 1;
                node1->object.value = povtor;
            }
            node1->right = NULL;
            if (node1->left->object.tokentype == 2) {
                node2->left->object.tokentype = 2;
                node2->left->object.operation = second;
            } else if (node1->left->object.tokentype == 1){
                node2->left->object.tokentype = 1;
                node2->left->object.value = second;
            } else {
                node2->left = one_m;
            }
            node1->left = NULL;
            node2->object.operation = '+';
            error = 0;
            return 1;
        } else {
            
            error = 1;
            return 0;
        }
    } else {
        return 0;
    }
}

/*
tokentype == 1 - точно число
tokentype == 2 - буква
tokentype == 0 - операция
*/

void print_Task(struct Node* node) {
    if (node->object.tokentype == 0 && node->object.operation == '+') {
        int sub = Task(node->left, node->right);
        if (sub) {
            node->object.operation = '*';
        }
    }    
}

void Recursive(struct Node* node) {
    if (node->object.tokentype == 1 || node->object.tokentype == 2 || node->object.tokentype == 0) {
        print_Task(node);
    }
    if (node->left) {
        Recursive(node->left);
    }
    if (node->right) {
        Recursive(node->right);
    }
    // if (node->left->object.tokentype == 1 || node->left->object.tokentype == 2 || node->left->object.tokentype == 0) {
    //     printf("YES");
    //     Recursive(node->left);
    // }
    // if (node->right->object.tokentype == 1 || node->right->object.tokentype == 2 || node->right->object.tokentype == 0) {
    //     Recursive(node->right);
    //     printf("YES");
    // }
    
    
    
}

int main(){
    //для чисел
    struct Stack s_main;
    //для операций
    struct Stack s_op;
    initStack(&s_main);
    initStack(&s_op);

    //символ на считывание
    char symbol;

    //проверка на число
    bool num = false;

    struct Token number;
    struct Token act;
    struct Token var;
    
    //пока ввод не закончился
    bool checker = true;

    //скобка
    bool las_bkt = false;

    while (checker) {
        symbol = getchar();
        //если ласт
        if (symbol == EOF || symbol == '\n') {
            checker = false;
            if (num) {
                push_back(&s_main, number);
            }
            while(s_op.size > 0) {
                push_back(&s_main,pop(&s_op));
            }
        }
        //если не ласт
        else {
            if (!num) {
                //если число
                if (symbol >= 48 && symbol <= 57) {
                    num = true;
                    number.tokentype = 1;
                    number.value = symbol - 48;
                }
                //если буква
                if (symbol >= 97 && symbol <= 122) {
                    var.tokentype = 2;
                    var.operation = symbol;
                    push_back(&s_main, var);
                }
                //если операция
                if ((symbol < 48 && symbol >= 42) || symbol == 94) {
                    //если в стеке операций ничего нет - просто добавляем
                    if (s_op.size == 0) {
                        act.operation = symbol;
                        act.tokentype = 0;
                        push_back(&s_op, act);
                    } else { //если там что-то есть
                        //пока у операции больший приоритет и она не ( - перекладываем в стэк чисел
                        while (s_op.size > 0 && priority_of_operation(peak(&s_op).operation) >= priority_of_operation(symbol) && peak(&s_op).operation != 40) {
                            push_back(&s_main, pop(&s_op));
                        }
                        //далее просто добавляем
                        act.operation = symbol;
                        act.tokentype = 0;
                        push_back(&s_op, act);
                    }
                }
                //если пришла (
                if (symbol == 40) {
                    act.operation = symbol;
                    act.tokentype = 0;
                    push_back(&s_op, act);
                }
                //если пришла )
                if (symbol == 41) {
                    las_bkt = true;
                    //перекладываем все операции внутри скобок
                    while (peak(&s_op).operation != 40) {
                        push_back(&s_main,pop(&s_op));
                    }
                    //удаляем (
                    pop(&s_op);
                }
            } else {
                //если число
                if (symbol >= 48 && symbol <= 57) {
                    number.value *= 10;
                    number.value += (symbol - 48);
                }
                //если операция
                if ((symbol < 48 && symbol >= 42) || symbol == 94) {
                    push_back(&s_main, number);
                    num = false;
                    if (s_op.size == 0) {
                        act.operation = symbol;
                        act.tokentype = 0;
                        push_back(&s_op, act);
                    } else {
                        while (s_op.size > 0 && priority_of_operation(peak(&s_op).operation) >= priority_of_operation(symbol) && peak(&s_op).operation != 40) {
                            push_back(&s_main, pop(&s_op));
                        }
                        act.operation = symbol;
                        act.tokentype = 0;
                        push_back(&s_op, act);
                    }
                }
                //тоже самое с ()
                if (symbol == 40) {
                    push_back(&s_main,number);
                    num = false;
                    act.operation = symbol;
                    act.tokentype = 0;
                    push_back(&s_op, act);
                }
                if (symbol == 41) {
                    push_back(&s_main,number);
                    num = false;
                    las_bkt = true;
                    while (peak(&s_op).operation != 40) {
                        push_back(&s_main,pop(&s_op));
                    }
                    pop(&s_op);
                }
            }
        }
    }
    //пока в стэке чисел и переменных что-то есть
    if (s_main.size > 0) {
        printf("Output stack: ");
        Print_Stack(&s_main);


        
        initTree(&t);
        
        //добавляем в дерево стэк
        insert(&t,&s_main);
        
        printf("Tree: ");
        printTree(t.root);
        printf("\n");


        // print_Task(t.root);
        Recursive(t.root);
              
        printf("\n");
        if (error != 1) {
            printf("Tree after Task: ");
            printTree(t.root);
        } else {
            printf("No identical elements found");
        }
        
        //освобождаем все  
        freeTree(&t);
    }
    free(s_main.nodes);
    free(s_op.nodes);
}