#ifndef __STACK__
#define __STACK__

typedef int T;

typedef struct Stack {
    T* array;
    int index;
    int maxLen;
} Stack;

Stack* InitStack();
int IsEmpty(Stack* stack);
void Push(Stack* stack, T value);
T Pop(Stack* stack);
T LookLast(Stack* stack);
int Size(Stack* stack);
void DelStack(Stack** stack);
void Reverse(Stack** stack);
void Concatenation(Stack** stack1, Stack** stack2);
void PrintStack(Stack* stack);

#endif