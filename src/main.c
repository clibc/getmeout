#include <stdio.h>
#include <string.h>

#include "stack_member.h"
#include "stack.hpp"

int main(void)
{
    char str1[10]  = {"push"};
    StackMember sm1 = {str1, INST, {PUSH}};
    char str2[10]  = {"pop"};
    StackMember sm2 = {str2, INST, {POP}};
    char str3[10]  = {"sub"};
    StackMember sm3 = {str3, INST, {SUB}};
    
    Stack s = create_stack();
    push(&s, &sm1);
    push(&s, &sm2);
    push(&s, &sm3);
    push(&s, &sm3);
    StackMember* popped = pop(&s);
    push(&s, &sm1);

    char parse_string[50] = "push 5 push 6 add return";
    char* delim = " ";

    StackMember stack[15];

    char* parsed_tokens[30];

    int first_iteration = 0;
    int i = 0;
    for(;;){
        char* p;
        if(!first_iteration){
            p = strtok(parse_string, delim);
            first_iteration = 1;
        }
        else { p = strtok(NULL, delim); }

        if(p != NULL){
            parsed_tokens[i++] = p;
        }
        else break;
    }

    for(int j = 0; j < i; ++j){
        printf("%s\n", parsed_tokens[j]);
    }
    
    (void)parsed_tokens;
    (void)stack;
    return 0;
}
