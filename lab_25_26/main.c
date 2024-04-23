#include <stdio.h>
#include <stdbool.h>
#include "list.h"
// сортировка пузырьком
void ReadData(List *nums) {
    char symbol = ' ';
    int valContinue = 0;
    int buff = 0;
    int minus = 1;
    while (symbol != EOF && symbol != '\n') {
        if (symbol != ' ' && symbol != '-') {
            if (valContinue == 1) {
                if (symbol != '0') {
                    buff = Last(nums).node->data;
                    buff = buff * 10 + (symbol - '0') * minus;
                    Last(nums).node->data = buff;
                    valContinue = 1;
                } else {
                    buff = Last(nums).node->data;
                    buff = buff * 10;
                    Last(nums).node->data = buff;
                    valContinue = 1;
                }
            } else {
                Add(nums, (symbol - '0') * minus);
                valContinue = 1;
            }
        } else if (symbol == '-') {
            minus = -1;
        } else {
            valContinue = 0;
            minus = 1;
        }
        symbol = getchar();
    }
}

void Task(List* nums) {
    int buff;
    for (Iterator j = First(nums); !IsTerminator(Next(j)); j = Next(j)) {
        if (j.node->data > Next(j).node->data) {
            buff = j.node->data;
            SetValue(j, Next(j).node->data);
            SetValue(Next(j), buff);
        }
    }
}

int main() {
    List nums;
    ListInit(&nums);
    ReadData(&nums);
    int buff;
    printf("-----------------после преобразования-----------------\n");
    Task(&nums);
    Print(&nums);
    printf("-------------------после сортировки-------------------\n");
    for (Iterator i = First(&nums); !IsTerminator(i); i = Next(i)) {
        for (Iterator j = First(&nums); !IsTerminator(Next(j)); j = Next(j)) {
            if (j.node->data > Next(j).node->data) {
                buff = j.node->data;
                SetValue(j, Next(j).node->data);
                SetValue(Next(j), buff);
            }
        }
    }
    Print(&nums);
    
}