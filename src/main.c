#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(void)
{
    Stack *myStack;
    int returnVal = 0;

    printf("Hello debug!\n");

    myStack = newStack(sizeof(int));


    if (myStack == NULL)
    {
        returnVal = ALLOC_FAIL;
    }
    else
    {
        for (int i = 3; i < 24; i++)
        {
            if (!returnVal)
            {
                returnVal = stackPush(myStack, (void *) i);
            }
        }
        while (myStack != NULL && myStack->length > 0)
        {
            if (!returnVal && myStack != NULL)
            {
                int element = (int) stackPop(myStack);
                if (element == 0)
                {
                    returnVal = ALLOC_FAIL;
                    free(myStack);
                    myStack = NULL;
                }
                else
                {
                    printf("%i\n", element);
                }
            }
        }
    }

    deleteStack(myStack);

    return returnVal;
}