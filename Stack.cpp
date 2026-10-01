typedef double StackElem_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define STACK_DEBUG       //TURN DEBUG ON/OFF

#ifdef STACK_DEBUG
#define DEBUG_STACK_DUMP(parametres) StackDump(parametres);
#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__);
#else
#define ON_DEBUG(...)
#define DEBUG_STACK_DUMP(...)
#define DEBUG_PRINT(...)
#endif

#define OTL_PAR __FILE__, __LINE__, __FUNCTION__
#define GONDON(condition, text) if (!(condition)) {     \
                                    fprintf(stderr, "File: %s:%d, Function: %s. %s\n",   \
                                        OTL_PAR, text);   \
                                    exit(true);    \
                                }
#define PRINTERR(text) fprintf(stderr, "File: %s:%d, Function: %s\n%s\n",     \
                            file, line, function, text);

#define STACK_OK Stack_ok(stk, OTL_PAR);

#define VOID -777

enum ErrorCodes {
    FUNC_FAILED  = -1,
    FUNC_IS_OK   =  0,
};

struct Stack_t {
	StackElem_t *stack;
    ssize_t size;
    ssize_t capacity;
};

void StackInit(Stack_t *stk, ssize_t capacity);
void StackPush(Stack_t *stk, StackElem_t elem);
StackElem_t StackPop(Stack_t *stk);    //мб функция проверки пустоты стека...
int StackDestroy(Stack_t *stk);

void StackDump(Stack_t *stk);
void PrintStack(Stack_t *stk);

void Stack_ok(Stack_t *stk,
            const char *file, int line, const char *function);

int main()
{
    Stack_t stk1 = {};

    StackInit(&stk1, 15);
    for (int i = 0 ; i < 2; i++)
        StackPush(&stk1, -1);
    StackPop(&stk1);

    PrintStack(&stk1);
    StackDestroy(&stk1);
    return 0;
}

void Stack_ok(Stack_t *stk,
            const char *file, int line, const char *function)
{
    bool stack_not_OK = false;

    if (stk->stack == NULL) {
        PRINTERR("ERROR: pointer on stack in struct <Stack_t> is NULL")
        stack_not_OK = true;
    }
    if (stk->size < 0) {
        PRINTERR("ERROR: size < 0 in struct <Stack_t>")
        stack_not_OK = true;
    }
    if (stk->capacity < 0) {
        PRINTERR("ERROR: capacity < 0 in struct <Stack_t>")
        stack_not_OK = true;
    }
    if (stk->size > stk->capacity) {
        PRINTERR("ERROR: size > capacity in struct <Stack_t>")
        stack_not_OK = true;
    }
    if (stack_not_OK) {
        DEBUG_PRINT("\n------DEBUG PRINT------\n\n")
        DEBUG_STACK_DUMP(stk)
        exit(true);
    }
}

void StackInit(Stack_t *stk, ssize_t capacity)
{
    GONDON(stk, "Struct <Stack_t> ISN'T CREATED")
    StackElem_t *array = (StackElem_t *) calloc(capacity, sizeof(StackElem_t));

    stk->stack = array;
    stk->capacity = capacity;
    stk->size = 0;

    STACK_OK
}

void StackPush(Stack_t *stk, StackElem_t elem)
{
    STACK_OK
    if (stk->size < stk->capacity) {
        stk->stack[stk->size++] = elem;
        STACK_OK
        return;
    }

    stk->capacity *= 2;
    StackElem_t * pre_stack = NULL;
    GONDON(pre_stack = (StackElem_t *) realloc(stk->stack, stk->capacity * sizeof(StackElem_t)), "You have a (nil) pointer here, stupid boy");
    stk->stack = pre_stack;

    GONDON(stk->size < stk->capacity, "Size >= capacity after <realloc>. Eto fiasko, bratan")
    stk->stack[stk->size++] = elem;

    STACK_OK
}

StackElem_t StackPop(Stack_t *stk)
{
    STACK_OK
    GONDON(stk->size > 0, "Can't pop because you are pidr")

    StackElem_t sin_popa = stk->stack[--stk->size];
    stk->stack[stk->size] = VOID;

    STACK_OK
    return sin_popa;
}

int StackDestroy(Stack_t *stk)
{
    STACK_OK

    for (ssize_t i = 0; i < stk->size; i++)
        stk->stack[i] = VOID;
    free(stk->stack);
    *stk = {};

    return FUNC_IS_OK;
}

void StackDump(Stack_t *stk)
{
    GONDON(stk, "I can't print, pon?")
    fprintf(stderr, "Struct Stack_t[%p] {\n", stk->stack);
    fprintf(stderr, "Capacity = %zu, size = %zu\n}\n", stk->capacity, stk->size);
    if (stk->size <= 0)
        fprintf(stderr, "STACK HAVE NO MORE 0 ELEMENTS\n");

    fprintf(stderr, "Print Stack:\n~~~~~~~~~~~~~~~~~~~~\n");
    for (ssize_t i = 0; i < stk->capacity; i++) {
        if (i < stk->size)
            fprintf(stderr, " * [%zd]\t%lg\n", i, stk->stack[i]);
        else
            fprintf(stderr, "   [%zd]\t%d\n", i, VOID);
    }
    fprintf(stderr, "~~~~~~~~~~~~~~~~~~~~\nEnd of print.\n");
}

void PrintStack(Stack_t *stk)
{
    STACK_OK

    for (ssize_t i = 0; i < stk->size; i++)
        printf("%lg\t", stk->stack[i]);
    printf("\n");
}