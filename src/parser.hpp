#ifndef PARSER
#define PARSER

#define MAX_TOKENS 20

void parse_code(char* code, char*** tokens, int* token_count)
{
    char** tkns = malloc(sizeof(char*) * MAX_TOKENS);

    char word_delim[] = " \t\r\n\v\f";
    int t_count = 0;
    int first_iteration = 1;
    for(;;){
        char* token;
        if(first_iteration) {
            token = strtok(code, word_delim);
            first_iteration = 0;
        }
        else token = strtok(NULL, word_delim);

        if(token == NULL) break; // end of tokens
        
        tkns[t_count] = token;
        t_count += 1;
    }

    *tokens = tkns;
    *token_count = t_count;
}

void get_tokens(Stack* stack, char** tokens, int token_count)
{
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
        else if(!strcmp(tokens[i], "pprint")){
            member.string_value = "pprint";
            member.type         = INST;
            member.i_type       = PPRINT;
        }
        else if(isdigit(*tokens[i])){
            int digit = atoi(tokens[i]);
            member.string_value    = tokens[i];
            member.type            = LITERAL;
            member.i_type          = INT;
            member.sdata.int_value = digit;
        }
        else if(!strcmp(tokens[i], "mul")){
            member.string_value = "mul";
            member.type         = INST;
            member.i_type       = MUL;
        }
        else if(!strcmp(tokens[i], "div")){
            member.string_value = "div";
            member.type         = INST;
            member.i_type       = DIV;
        }
        else{
            printf("Unknown token '%s'\n", tokens[i]);
            exit(-1);
        }
        push(stack, &member);
    }

}

#endif//PARSER
