//#include "Stack.h"
#include "Stack.cpp"

int main()
{
    Stack_t stk1 = {};
    StackInit(&stk1, 3);
    for (int i = 0; i < 12; i++)
        StackPush(&stk1, 12);
    for (int i =0; i < 4; i++)
        StackPop(&stk1);
    PrintStack(&stk1);
    StackDestroy(&stk1);
    return 0;
}