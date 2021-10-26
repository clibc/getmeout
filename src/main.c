#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack_member.h"
#include "stack.hpp"
#include "parser.hpp"

void assert_type(StackMember*, int);

#define FILE_DESC file
#define fput(...) fprintf(FILE_DESC, __VA_ARGS__)

int main(void)
{
    FILE* FILE_DESC;
    FILE_DESC = fopen("output.asm", "w");

    char code[100] = {
        "push 43\n" 
        "push 23\n" 
        "add\n"
        "push 5\n"
        "sub\n"
    };

    Stack stack = create_stack(sizeof(StackMember));

    char** tokens = 0;
    int   token_count = 0;
    parse_code(code, &tokens, &token_count);
    
    for(int i = token_count - 1; i >= 0; --i){
        StackMember member;
        if(!strcmp(tokens[i], "push")){
            member.string_value = "push";
            member.type         = INST;
            member.i_type       = PUSH;
        }
        else if(!strcmp(tokens[i], "pop")){
            member.string_value = "pop";
            member.type         = INST;
            member.i_type       = POP;
        }
        else if(!strcmp(tokens[i], "add")){
            member.string_value = "add";
            member.type         = INST;
            member.i_type       = ADD;
        }
        else if(!strcmp(tokens[i], "sub")){
            member.string_value = "sub";
            member.type         = INST;
            member.i_type       = SUB;
        }
        else if(isdigit(*tokens[i])){
            int digit = atoi(tokens[i]);
            member.string_value    = tokens[i];
            member.type            = LITERAL;
            member.i_type          = INT;
            member.sdata.int_value = digit;
        }
        push(&stack, &member);
    }

    // second pass
    fput("segment .text\n");
    fput("global _start\n");
    fput("_start:\n");
    while(stack.item_count > 0){
        StackMember* m = pop(&stack);
        if(m->type == INST){
            if(m->i_type == PUSH){
                StackMember* arg = pop(&stack);
                assert_type(arg, LITERAL);
                fput(";; push\n");
                fput("push %i\n", arg->sdata.int_value);
            }
            else if(m->i_type == ADD){
                // add
                fput(";; add\n");
                fput("pop rax\n");
                fput("pop rbx\n");
                fput("add rax,rbx\n");
                fput("push rax\n");
            }
            else if(m->i_type == SUB){
                // sub
                fput(";; sub\n");
                fput("pop rax\n");
                fput("pop rbx\n");
                fput("sub rbx,rax\n");
                fput("push rbx\n");
            }
        }
    }

    fput("pop rdi\n");
    fput("mov rax, 60\n");
    fput("syscall\n");
    
    return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
void assert_type(StackMember* m, int expected_type)
{
    if(m->type != (TInfo)expected_type)
    {
        printf("Expected type ");
        switch(expected_type){
        case INST:
            printf("INST ");
            break;
        case LITERAL:
            printf("LITERAL ");
            break;
        default:
            printf("UNLISTED ");
            break;
        }
        printf("but got ");
        switch(m->type){
        case INST:
            printf("INST ");
            break;
        case LITERAL:
            printf("LITERAL ");
            break;
        default:
            printf("UNLISTED ");
            break;
        }
        printf("\n");
        exit(-1);
    }
}
#pragma GCC diagnostic pop
