#ifndef STACK_HPP
#define STACK_HPP

#include <stdlib.h>

#define INIT_STACK_ITEM_SIZE 3

#include "stack_member.h"

typedef struct
{
    void*  top;
    void*  base;
    int    item_count;
    int    max_item_count;
    size_t member_size;
}Stack;

Stack create_stack(size_t size)
{
    Stack s;
    s.base = (void*)malloc(size * INIT_STACK_ITEM_SIZE);
    s.top  = s.base;
    s.item_count = 0;
    s.max_item_count = INIT_STACK_ITEM_SIZE;
    s.member_size = size;
    return s;
}

void push(Stack* s, void* member)
{
    if(s->item_count == s->max_item_count){
        // realloc
        s->base = realloc(s->base, s->member_size * s->max_item_count * 2);
        s->top  = (char*)s->base + (s->item_count - 1) * s->member_size;
        s->max_item_count *= 2;
    }

    //push
    if(s->item_count != 0){
        s->top = (char*)s->top + s->member_size;
    }
    s->item_count += 1;
    memcpy(s->top, member, s->member_size);
}

void* pop(Stack* s)
{
    if(s->item_count == 0){ return NULL;}

    void* retval = s->top;
    s->top = (char*)s->top - s->member_size;
    s->item_count -= 1;
    
    return retval;
}

#endif //STACK_HPP
