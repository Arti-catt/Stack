typedef double StackElem_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define GONDON(condition, text) if (!(condition)) {     \
                                    fprintf(stderr, "File: %s:%d, Function: %s. %s\n",   \
                                        __FILE__, __LINE__, __FUNCTION__, text);   \
                                    abort();    \
                                }

#define VOID -777

enum ErrorCodes {
    FUNC_FAILED   = -1,
    FUNC_IS_OK  =  0,
};

struct Stack_t {
    StackElem_t *stack;
    size_t size;
    size_t capacity;

    //TODO: DEBUG parametres
};

int StackInit(Stack_t *stk, size_t capacity);
int StackPush(Stack_t *stk, StackElem_t elem);
StackElem_t StackPop(Stack_t *stk, int *err);     //мб функция проверки пустоты стека...
int StackDestroy(Stack_t *stk);

int PrintStack_t(Stack_t *stk);

int main()
{
    Stack_t stk1 = {};
    StackInit(&stk1, 4);
    StackPush(&stk1, 10);
    StackPush(&stk1, 20.5);
    StackPush(&stk1, 0);
    int err = 0;
    double back = StackPop(&stk1, &err);

    PrintStack_t(&stk1);
    return 0;
}

int StackInit(Stack_t *stk, size_t capacity)
{
    GONDON(stk, "You have a (nil) pointer here, stupid boy");
    StackElem_t *array = (StackElem_t *) calloc(capacity, sizeof(StackElem_t));
    GONDON(array, "The first <calloc> gondon");

    stk->stack = array;
    stk->capacity = capacity;
    stk->size = 0;

    return FUNC_IS_OK;
}

int StackPush(Stack_t *stk, StackElem_t elem)
{
    GONDON(stk, "You have a (nil) pointer here, nuhai bebry");
    if (stk->size < stk->capacity) {
        stk->stack[stk->size++] = elem;
        return FUNC_IS_OK;
    }

    stk->capacity *= 2;
    stk->stack = (StackElem_t *) realloc(stk->stack, stk->capacity * sizeof(StackElem_t));
    GONDON(stk, "You have a (nil) pointer here, stupid boy");
    GONDON(stk->size < stk->capacity, "Size >= capacity after <realloc>. Eto fiasko, bratan")
    stk->stack[stk->size++] = elem;
    return FUNC_IS_OK;
}

StackElem_t StackPop(Stack_t *stk, int *err)
{
    GONDON(stk, "You have a (nil) pointer here, nuhai bebry");

    if (stk->size == 0) {
        *err = FUNC_FAILED;
        return FUNC_FAILED;
    }

    return stk->stack[--stk->size];
}

int StackDestroy(Stack_t *stk)
{
    for (size_t i = 0; i < stk->size; i++)
        stk->stack[i] = VOID;
    free(stk->stack);
    *stk = {};
    return FUNC_IS_OK;
}

int PrintStack_t(Stack_t *stk)
{
    printf("Struct Stack_t[%p] {\n", stk->stack);
    printf("Capacity = %zu, size = %zu\n}\n", stk->capacity, stk->size);
    printf("Print Stack:\n~~~~~~~~~~~~~~~~~~~~\n");
    StackElem_t print_elem = 0;
    for (size_t i = 0; i < stk->capacity; i++) {
        print_elem = (i < stk->size) ? stk->stack[i] : VOID;
        printf("* [%zu] %lg\n", i, print_elem);
    }
    printf("~~~~~~~~~~~~~~~~~~~~\nEnd of print.\n");
    return FUNC_IS_OK;
}