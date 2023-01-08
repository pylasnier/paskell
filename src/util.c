#include <stdlib.h>
#include <string.h>
#include "util.h"

Stack *newStack(size_t elementSize)
{
    Stack *stack = malloc(sizeof(Stack));

    if (stack != NULL)
    {
        stack->elementSize = elementSize;
        stack->length = 0;

        stack->ppStack = malloc(STACK_CHUNK * stack->elementSize);
        if (stack->ppStack == NULL)
        {
            free(stack);
            stack = NULL;
        }
    }

    return stack;
}

Stack *copyStack(Stack *stack)
{
    Stack *newStack = malloc(sizeof(Stack));

    if (stack != NULL)
    {
        newStack->elementSize = stack->elementSize;
        newStack->length = stack->length;

        newStack->ppStack = malloc(((newStack->length - 1) / STACK_CHUNK + 1) * STACK_CHUNK * newStack->elementSize);

        if (newStack->ppStack == NULL)
        {
            free(newStack);
            newStack = NULL;
        }
        else
        {
            memcpy(newStack->ppStack, stack->ppStack, newStack->length * newStack->elementSize);
        }
    }

    return newStack;
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