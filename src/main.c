#include <stdio.h>
#include <string.h>

#include "stack_member.h"

int main(void)
{
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
