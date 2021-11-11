#ifndef STACK_MEM
#define STACK_MEM

typedef enum {
    INST,
    LITERAL,
    STATEMENT,

    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    PPRINT,
    EXIT,

    OP_EQ,
    ST_IF,
    ST_END,

    INT,
    FlOAT,
    STRING,
} TInfo;

typedef struct {
    char* string_value;
    TInfo type;

    TInfo i_type;
    TInfo l_type;

    union {
        int int_value;
        float float_value;
        char* string_value;
    } sdata;
} StackMember;

#endif  // STACK_MEM
