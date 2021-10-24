#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack_member.h"
#include "stack.hpp"
#include "parser.hpp"

int main(void)
{
    char code[100] = {
        "push 43\n" 
        "push 23\n" 
        "add\n"
        "push 5\n"
        "sub\n"
    };

    Stack stack = create_stack();

    char** tokens = 0;
    int   token_count = 0;
    parse_code(code, &tokens, &token_count);

    for(int i = 0; i < token_count; ++i){
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

    while(stack.item_count > 0){
        StackMember* m = pop(&stack);
        
        
        
    }

    return 0;
}
