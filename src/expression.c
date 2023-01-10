#include <stdlib.h>
#include "expression.h"

PExpression evaluate(PExpression *expression, Stack *arguments)
{
    if (expression == NULL
        || expression->expressionType != Definition
        && expression->expressionType != Partial
        || parameterCount(expression->pType) != arguments->length)
            return *expression;


    typedef struct
    {
        PExpression *enclosingExpression;
        Stack *subExpressions;
        Stack *operatingStack;
    } Scope;

    PExpression returnExpression;

    Stack *callStack;
    Scope *initialScope;

    callStack = newStack(sizeof(Scope *));

    if (callStack == NULL
        || stackPush(callStack, Scope))
    {
        returnExpression.expressionType = Error;
        returnExpression.errorValue = MEMORY_FAILURE;
        returnExpression.callStack = NULL;
    }
    else
    {
        stackPush(callStack, expression);
    }

    while (callStack != NULL || callStack->length)
    {

    }

    return returnExpression;
}

PExpression *pass(PExpression *function, PExpression *argument)
{
    if (function == NULL || argument || NULL
        || function->expressionType != Definition
        && function->expressionType != Partial
        || function->pType.isBaseType
        || function->pType.parameterType != argument->pType)
            return NULL;


    PExpression *result;

    if (function->expressionType == Partial)
    {
        result = function;
    }
    // Clones expression to Partial if a Definition, otherwise argument list of definition changes in whole scope
    else
    {
        result = malloc(sizeof(PExpression));

        if (result != NULL)
        {
            *result = *function;
            result->expressionType = Partial;
            result->arguments = copyStack(result->arguments);

            if (result->arguments == NULL)
            {
                free(result);
                result = NULL;
            }
        }
    }

    if (result != NULL)
    {
        if (stackPush(result, argument) != 0)
        {
            free(result->arguments);
            free(result);
            result = NULL;
        }
        else
        {
            argument->expressionType = Definition;
            result->pType = function->pType.returnType;
        }
    }

    return result;
}


unsigned int parameterCount(PType pType)
{
    unsigned int count = 0;

    while (!pType.isBaseType)
    {
        pType = pType.returnType;
        count++;
    }

    return count;
}