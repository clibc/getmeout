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
    DUP,
    PPRINT,
    STRPRINT,
    EXIT,

    OP_EQ,
    OP_GT,
    OP_LT,
    OP_GTE,
    OP_LTE,

    ST_IF,
    ST_ELSE,
    ST_END,

    ST_FOR,
    ST_LOOP,

    VAR_FORINDEX,

    INT,
    FlOAT,
    STRING,
} TInfo;

typedef struct {
    int index;
    int start;
    int end;
} LoopInfo;

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

    unsigned int defined_address;
    unsigned int jump_address;
    unsigned int loop_index_mem_ref;
    unsigned int string_id_value;
} StackMember;

#endif  // STACK_MEM
