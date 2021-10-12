#ifndef STACK_HPP
#define STACK_HPP

#include <stdlib.h>

#define INIT_STACK_ITEM_SIZE 32

#include "stack_member.h"

typedef struct
{
    void* top;
    void* base;
    int   item_count;
    int   max_item_count;
}Stack;

Stack create_stack()
{
    Stack s;
    s.base = (void*)malloc(sizeof(StackMember) * INIT_STACK_ITEM_SIZE);
    s.top  = s.base;
    s.item_count = 0;
    s.max_item_count = INIT_STACK_ITEM_SIZE;
    return s;
}

void push(Stack* s, StackMember* member)
{
    if(s->item_count + 1 > s->max_item_count){
        // realloc
        return;
    }

    //push
    memcpy(s->top, member, sizeof(StackMember));
    s->item_count += 1;
    s->top = (StackMember*)s->top + 1;
}

StackMember* pop(Stack* s)
{
    if(s->item_count == 0){ return NULL;}

    StackMember* retval = (StackMember*)s->top;
    s->top = (StackMember*)s->top - 1;
    s->item_count -= 1;
    
    return retval;
}

#endif //STACK_HPP
