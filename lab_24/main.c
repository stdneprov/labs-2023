#include "tree_and_stack.h"


/*
tokentype == 1 - точно число
tokentype == 2 - буква
tokentype == 0 - операция
*/


struct Tree t;
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

void PrintTask(struct Node* node) {
    if (node->object.tokentype == 0 && node->object.operation == '+') {
        int sub = Task(node->left, node->right);
        if (sub) {
            node->object.operation = '*';
        }
    }    
}

void Recursive(struct Node* node) {
    if (node->object.tokentype == 1 || node->object.tokentype == 2 || node->object.tokentype == 0) {
        PrintTask(node);
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
    InitStack(&s_main);
    InitStack(&s_op);

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
                PushBack(&s_main, number);
            }
            while(s_op.size > 0) {
                PushBack(&s_main, Pop(&s_op));
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
                    PushBack(&s_main, var);
                }
                //если операция
                if ((symbol < 48 && symbol >= 42) || symbol == 94) {
                    //если в стеке операций ничего нет - просто добавляем
                    if (s_op.size == 0) {
                        act.operation = symbol;
                        act.tokentype = 0;
                        PushBack(&s_op, act);
                    } else { //если там что-то есть
                        //пока у операции больший приоритет и она не ( - перекладываем в стэк чисел
                        while (s_op.size > 0 && PriorityOfOperation(Peak(&s_op).operation) >= PriorityOfOperation(symbol) && Peak(&s_op).operation != 40) {
                            PushBack(&s_main, Pop(&s_op));
                        }
                        //далее просто добавляем
                        act.operation = symbol;
                        act.tokentype = 0;
                        PushBack(&s_op, act);
                    }
                }
                //если пришла (
                if (symbol == 40) {
                    act.operation = symbol;
                    act.tokentype = 0;
                    PushBack(&s_op, act);
                }
                //если пришла )
                if (symbol == 41) {
                    las_bkt = true;
                    //перекладываем все операции внутри скобок
                    while (Peak(&s_op).operation != 40) {
                        PushBack(&s_main, Pop(&s_op));
                    }
                    //удаляем (
                    Pop(&s_op);
                }
            } else {
                //если число
                if (symbol >= 48 && symbol <= 57) {
                    number.value *= 10;
                    number.value += (symbol - 48);
                }
                //если операция
                if ((symbol < 48 && symbol >= 42) || symbol == 94) {
                    PushBack(&s_main, number);
                    num = false;
                    if (s_op.size == 0) {
                        act.operation = symbol;
                        act.tokentype = 0;
                        PushBack(&s_op, act);
                    } else {
                        while (s_op.size > 0 && PriorityOfOperation(Peak(&s_op).operation) >= PriorityOfOperation(symbol) && Peak(&s_op).operation != 40) {
                            PushBack(&s_main, Pop(&s_op));
                        }
                        act.operation = symbol;
                        act.tokentype = 0;
                        PushBack(&s_op, act);
                    }
                }
                //тоже самое с ()
                if (symbol == 40) {
                    PushBack(&s_main,number);
                    num = false;
                    act.operation = symbol;
                    act.tokentype = 0;
                    PushBack(&s_op, act);
                }
                if (symbol == 41) {
                    PushBack(&s_main,number);
                    num = false;
                    las_bkt = true;
                    while (Peak(&s_op).operation != 40) {
                        PushBack(&s_main, Pop(&s_op));
                    }
                    Pop(&s_op);
                }
            }
        }
    }
    //пока в стэке чисел и переменных что-то есть
    if (s_main.size > 0) {
        printf("Output stack: ");
        PrintStack(&s_main);


        
        InitTree(&t);
        
        //добавляем в дерево стэк
        Insert(&t,&s_main);
        
        printf("Tree: ");
        PrintTree(t.root);
        printf("\n");


        // print_Task(t.root);
        Recursive(t.root);
              
        printf("\n");
        if (error != 1) {
            printf("Tree after Task: ");
            PrintTree(t.root);
        } else {
            printf("No identical elements found");
        }
        
        //освобождаем все  
        FreeTree(&t);
    }
    free(s_main.nodes);
    free(s_op.nodes);
}