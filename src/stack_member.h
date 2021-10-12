#ifndef STACK_MEM
#define STACK_MEM

typedef enum
{
    PUSH,
    POP,
    ADD,
    SUB
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
    StackMemberType mtype;

    union{
        Instruction i_type;
        Literal     l_type;
    }subtype;
}StackMember;

#endif //STACK_MEM
