#include <stdlib.h>
#include "expression.h"

PExpression *evaluate(PExpression *expression)
{
    if (expression == NULL
        || expression->expressionType != Definition
        && expression->expressionType != Partial
        || !expression->pType.isBaseType)
            return expression;


    

    return expression;
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
            result->pType = function->pType.returnType;
        }
    }

    return result;
}