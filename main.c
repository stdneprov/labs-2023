#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "stack_module.h"

int Stack_Count = 0;
int stack_num = 1;
Stack* stack_one = NULL;
Stack* stack_two = NULL;

enum Command {EXIT, CREATE, PUSH, POP, PRINT, SIZE, CONCATENATE, SORT, CLEAR, DELETE};

void Menu(Stack** stack) {
    enum Command cmd;
    int inp;
    while (1) {
        cmd = -1;

        if (Stack_Count) {
            printf("\nStack %d/%d chosen. Here's your options:\n\
1. Create one more stack\n\
2. Push new item\n\
3. Pop the last item\n\
4. Print stack (from bottom to top)\n\
5. Print stack size\n\
6. Concatenate this stack with another (another stack will be delited)\n\
7. Sort stack\n\
8. Clear stack (delete all the items)\n\
9. Delete stack\n\
0. Exit\n\n", stack_num, Stack_Count);

            scanf("%d", &inp);
        } else {
            printf("\nYou haven't created a stack yet. Wanna do it?\n\
1. Yes  0. Exit\n\n");
            
            scanf("%d", &inp);

            if (inp > 1) {
                continue;
            }
        }

        cmd = inp;

        switch (cmd) 
        {
        case CREATE:
            switch (Stack_Count) 
            {
            case 0:
                Stack_create(&stack_one);
                ++Stack_Count;
                break;
            case 1: 
                Stack_create(&stack_two);
                ++Stack_Count;
                break;
            default:
                printf("Donate 10$ to be able to create more stacks\n");
                break;
            }
            break;
    
        case PUSH:
            printf("Input the value: ");
            scanf("%d", &inp);
            Stack_push(*stack, Data_to_Stack_Item(inp));
            break;
        
        case POP:
            Stack_pop(*stack);
            break;
        case PRINT:
            Stack_print(*stack);
            break;
        case SIZE:
            printf("%ld\n", Stack_size(*stack));
            break;
        case CONCATENATE:
            if (Stack_Count > 1) {
                --Stack_Count;
                if (stack_num == 1) {
                    Stack_concatenate(stack_one, &stack_two);
                } else {
                    Stack_concatenate(stack_two, &stack_one);
                    stack_one = stack_two;
                    stack_two = NULL;
                    stack_num = 1;
                    stack = &stack_one;
                }
            } else {
                printf("You have created only one stack\n");
            }
            break;;

        case SORT:
            Stack_qsort(*stack);
            break;
        
        case CLEAR:
            Stack_clear(*stack);
            break;
        
        case DELETE:
            Stack_delete(stack);
            if (stack_num == 1) {
                stack_one = stack_two;
                stack_two = NULL;
                
            } else {
                stack_num = 1;
                stack = &stack_one;
            }
            --Stack_Count;
            break;

        case EXIT:
            stack_num = 0;
            return;
        }
    }
}

void Start() {

    stack_num = 1;

    while (1) {

        if (Stack_Count > 1) {
            printf("\nYou have created more than one stack. Which one do you wanna work with?\n\
1. First    2. Second   0. Exit\n\n");

            scanf("%d", &stack_num);
        } 

        switch (stack_num)
        {
        case 1:
            Menu(&stack_one);
            break;
        case 2:
            Menu(&stack_two);
            break;
        case 0:
            Stack_delete(&stack_one);
            Stack_delete(&stack_two);
            return;

        default:
            break;
        }
    }
}


int main() {

    Start();

    return 0;
}