#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "util.h"

PExpression *evaluate(PExpression *definition);
PExpression *pass(PExpression *function, PExpression *argument);

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
    };
} PExpression;

typedef enum
{
    Definition,
    Partial,
    Parameter,
    Value
} ExpressionType;

typedef union
{
    long longValue;
    float floatValue;
    char charValue;
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
    PChar
} PBaseType;


#endif