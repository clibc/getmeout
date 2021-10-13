#ifndef STACK_MEM
#define STACK_MEM

typedef enum
{
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV
}Instruction;

typedef enum
{
    INT,
    FlOAT,
    STRING
}Literal;

typedef enum
{
    INST,
    LITERAL
}StackMemberType;

typedef struct
{
    char*           string_value;
    StackMemberType type;

    Instruction i_type;
    Literal     l_type;

    union{
        int int_value;
        float float_value;
        char* string_value;
    }sdata;
}StackMember;

#endif //STACK_MEM
