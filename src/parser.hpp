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

#endif//PARSER
