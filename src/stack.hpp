#ifndef STACK_HPP
#define STACK_HPP

#include "stack_member.h"

typedef struct
{
    void* top;
    void* base;
    int   item_count;
}Stack;

void Push(Stack* s, StackMember member)
{
}

StackMember Pop(Stack* s)
{
}

#endif //STACK_HPP
