typedef double StackElem_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define STACK_DEBUG       //TURN DEBUG ON/OFF

enum ErrorCodes {
    FUNC_FAILED  = -1,
    FUNC_IS_OK   =  0,
};

enum ReallocMods {
    DOWN  =  0,
    UP    =  1,
};

struct Stack_t {
	StackElem_t *stack;
    ssize_t size;
    ssize_t capacity;
};

void StackInit(Stack_t *stk, ssize_t capacity);
void StackPush(Stack_t *stk, StackElem_t elem);
StackElem_t StackPop(Stack_t *stk);    //мб функция проверки пустоты стека...
StackElem_t *ReSize(Stack_t *stk, int mod);

int StackDestroy(Stack_t *stk);

void StackDump(Stack_t *stk);
void PrintStack(Stack_t *stk);
