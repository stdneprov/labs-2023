#include "base.h"
#include "tree.h"
int main(void) {
    Stack* mainStack = InitStack();
    Stack* buffStack = InitStack();
    Token inp;
    while ((inp = GetToken()).val.letter != '\n') {
        if (inp.type == VAR) {
            AddCharToStack(mainStack, inp.val.letter, inp.sign);
        } else if (inp.type == OPERATOR) {
            if (inp.val.letter == '(') {
                AddCharToStack(buffStack, inp.val.letter, inp.sign);
            } else if (inp.val.letter == ')') {
                while (buffStack->size > 0 &&
                       StackTop(buffStack)->val.letter != '(') {
                    AddCharToStack(mainStack, StackPop(buffStack).val.letter,
                                   inp.sign);
                }
                StackPop(buffStack);
            } else {
                while (buffStack->size > 0 &&
                       GetPriority(inp.val.letter) <
                           GetPriority(StackTop(buffStack)->val.letter)) {
                    AddCharToStack(mainStack, StackPop(buffStack).val.letter,
                                   inp.sign);
                }
                AddCharToStack(buffStack, inp.val.letter, inp.sign);
            }
        } else {
            AddIntToStack(mainStack, inp.val.num);
        }
    }
    while (buffStack->size > 0) {
        if (StackTop(buffStack)->val.letter == '(') {
            StackPop(buffStack);
        } else {
            AddCharToStack(mainStack, StackPop(buffStack).val.letter, 1);
        }
    }

    Tree tree = InitTree();
    StackToTree(mainStack, &tree);
    VariantTree(&tree);
    VariantTreeVar(&tree);
    PrintInLine(tree);
    printf("\n");
}
