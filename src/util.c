#include <stdlib.h>
#include "util.h"

int myF(void)
{
    Stack *pMyStack = malloc(sizeof(Stack));
    free(pMyStack);
    pMyStack = NULL;
    return 0;
}

Stack *newStack(int elementSize)
{
    Stack *stack = malloc(sizeof(Stack));

    if (stack != NULL)
    {
        stack->elementSize = elementSize;
        stack->length = 0;

        stack->ppStack = malloc(STACK_CHUNK * stack->elementSize);
        if (stack->ppStack == NULL)
        {
            stack = NULL;
        }
    }

    return stack;
}

int stackPush(Stack *stack, void *element)
{
    if (stack == NULL)
        return NULL_PTR_REF;
      
  
    int returnVal = 0;

    if (stack->length > 0 && stack->length % STACK_CHUNK == 0)
    {
        stack->ppStack = realloc(stack->ppStack, (stack->length + STACK_CHUNK) * stack->elementSize);

        if (stack->ppStack == NULL)
        {
            returnVal = ALLOC_FAIL;
        }
    }

    if (returnVal == 0)
    {
        *(stack->ppStack + stack->length * stack->elementSize) = element;
        stack->length++;
    }

    return returnVal;
}

void *stackPop(Stack *stack)
{
    if (stack == NULL)
        return NULL;
    

    stack->length--;
    void *element = *(stack->ppStack + stack->length * stack->elementSize);

    if (stack->length > 0 && stack->length % STACK_CHUNK == 0)
    {
        stack->ppStack = realloc(stack->ppStack, stack->length * stack->elementSize);

        if (stack->ppStack == NULL)
        {
            element = NULL;
        }
    }

    return element;
}

int deleteStack(Stack *stack)
{
    if (stack != NULL)
    {
        if (stack->ppStack != NULL)
        {
            free(stack->ppStack);
        }
        free(stack);
    }

    return 0;
}