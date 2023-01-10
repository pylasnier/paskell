#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "util.h"

#define MEMORY_FAILURE  0x01

PExpression evaluate(PExpression *expression, Stack *arguments);
PExpression *pass(PExpression *function, PExpression *argument);

unsigned int parameterCount(PType pType);

typedef struct
{
    ExpressionType expressionType;
    unsigned short isBaseOperation;
    PType pType;

    union   // Expression type-dependent
    {
        struct
        {
            union   // Being base operation-dependent
            {
                Stack *subExpressions;                  // Non-base operation
                PExpression (*baseOperation)(Stack *);  // Base operation
            };
            Stack *arguments;
        };                              // Definition or partial
        unsigned int parameterIndex;    // Parameter
        PValue value;                   // Value
        struct
        {
            int errorValue;
            Stack *callStack;
        };                              // Error
    };
} PExpression;

typedef enum
{
    Definition,
    Partial,
    Parameter,
    Value,
    Error
} ExpressionType;

typedef union
{
    long longValue;
    float floatValue;
    char *strValue;
} PValue;


typedef struct
{
    unsigned short isBaseType;

    union   // Being base type-dependent
    {
        struct
        {
            PType parameterType;
            PType returnType;
        };                  // Function type
        PBaseType baseType; // Base type
    };
} PType;

typedef enum
{
    PInt,
    PFloat,
    PStr
} PBaseType;


#endif