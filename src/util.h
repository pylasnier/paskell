#ifndef UTIL_H
#define UTIL_H

#define STACK_CHUNK         8
#define NULL_PTR_REF        0x01
#define ALLOC_FAIL          0x02

int myF(void);

typedef struct
{
    unsigned length;
    unsigned elementSize;
    void **ppStack;
} Stack;

Stack *newStack(int elementSize);
void *stackPop(Stack *stack);
int stackPush(Stack *stack, void *element);
int deleteStack(Stack *stack);

#endif