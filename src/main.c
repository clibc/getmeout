#include <stdio.h>
#include <string.h>

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
        printf("%s\n", tokens[i]);
    }

    return 0;
}
