#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack_member.h"
#include "stack.hpp"
#include "parser.hpp"
#include "file.hpp"

void assert_type(StackMember*, int);
void embed_pprint();

int main(int argc, char** argv)
{
    char *code;
    if(argc == 1){
        printf("Provide a source file\n");
        exit(-1);
    }
    else if (argc == 2){
        // load file
        code = load_file(argv[1]);
        //printf("%s\n", file_content);
    }
    else {
        printf("Unrecognized agruments\n");
        exit(-1);
    }
    
    init_file();
    
    Stack stack = create_stack(sizeof(StackMember));

    char** tokens = 0;
    int   token_count = 0;
    parse_code(code, &tokens, &token_count);
    get_tokens(&stack, tokens, token_count);

    // compile code
    fput("BITS 64\n");
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
            if(m->i_type == EXIT){
                StackMember* arg = pop(&stack);
                assert_type(arg, LITERAL);
                fput(";; exit --- \n");
                fput("mov rdi, 0x%02X\n", arg->sdata.int_value);
                fput("mov rax, 60\n");
                fput("syscall\n");
            }
            else if(m->i_type == ADD){
                fput(";; add\n");
                fput("pop rax\n");
                fput("pop rbx\n");
                fput("add rax,rbx\n");
                fput("push rax\n");
            }
            else if(m->i_type == SUB){
                fput(";; sub\n");
                fput("pop rax\n");
                fput("pop rbx\n");
                fput("sub rbx,rax\n");
                fput("push rbx\n");
            }
            else if(m->i_type == PPRINT){
                fput(";;pprint\n");
                fput("pop rdi\n");
                fput("call pprint\n");
            }
            else if(m->i_type == MUL){
                fput(";;mul\n");
                fput("pop rax\n");
                fput("pop rbx\n");
                fput("mul rbx\n");
                fput("push rax\n");
            }
            else if(m->i_type == DIV){
                fput(";;div\n");
                fput("pop rbx\n");
                fput("pop rax\n");
                fput("div rbx\n");
                fput("push rax\n");
            }
        }
    }

    fput("pop rdi\n");
    fput("mov rax, 60\n");
    fput("syscall\n");

    embed_pprint();

    close_file();
    compile_file();

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
            printf("UNDEFINED ");
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
            printf("UNDEFINED ");
            break;
        }
        printf("\n");
        exit(-1);
    }
}
#pragma GCC diagnostic pop

void embed_pprint()
{
    /* fput("pprint:\n"); */
    /* fput("sub rsp, 56\n"); */
    /* fput("mov r9d, 3435973837\n"); */
    /* fput("lea rax, [rsp+48]\n"); */
    /* fput("mov BYTE [rsp+47], 10\n"); */
    /* fput("lea rdx, [rsp+46]\n"); */
    /* fput("mov QWORD[rsp+8], rax\n"); */
    /* fput("lea r10d, [rax]\n"); */

    /* fput(".L2:\n"); */
    /* fput("mov eax, edi\n"); */
    /* fput("mov ecx, edi\n"); */
    /* fput("mov r8d, r10d\n"); */
    /* fput("imul rax, r9\n"); */
    /* fput("sub r8d, edx\n"); */
    /* fput("sub rdx, 1\n"); */
    /* fput("shr rax, 35\n"); */
    /* fput("lea esi, [rax+rax*4]\n"); */
    /* fput("add esi, esi\n"); */
    /* fput("sub ecx, esi\n"); */
    /* fput("add ecx, 48\n"); */
    /* fput("mov BYTE [rdx+1], cl\n"); */
    /* fput("mov ecx, edi\n"); */
    /* fput("mov edi, eax\n"); */
    /* fput("cmp ecx, 9\n"); */
    /* fput("ja .L2\n"); */
    /* fput("movsx rdx, r8d\n"); */
    /* fput("mov eax, 32\n"); */
    /* fput("mov edi, 1\n"); */
    /* fput("sub rax, rdx\n"); */
    /* fput("mov edx, r8d\n"); */
    /* fput("lea rsi, [rsp+16+rax]\n"); */
    /* fput("xor eax, eax\n"); */
    /* fput("mov rax, 1 ;; SYS_WRITE\n"); */
    /* fput("syscall \n"); */
    /* fput("add rsp, 56\n"); */
    /* fput("ret\n"); */

    fput("pprint:\n");
    fput("sub     rsp, 56\n");
    fput("mov     eax, edi\n");
    fput("mov     r8d, 1\n");
    fput("mov     r9d, 3435973837\n");
    fput("neg     eax\n");
    fput("mov     BYTE [rsp+32], 10\n");
    fput("lea     rsi, [rsp+31]\n");
    fput("cmovs   eax, edi\n");
    fput(".L2:\n");
    fput("mov     edx, eax\n");
    fput("sub     rsi, 1\n");
    fput("imul    rdx, r9\n");
    fput("shr     rdx, 35\n");
    fput("lea     ecx, [rdx+rdx*4]\n");
    fput("add     ecx, ecx\n");
    fput("sub     eax, ecx\n");
    fput("add     eax, 48\n");
    fput("mov     BYTE [rsi+1], al\n");
    fput("mov     eax, edx\n");
    fput("mov     edx, r8d\n");
    fput("add     r8d, 1\n");
    fput("test    eax, eax\n");
    fput("jne     .L2\n");
    fput("test    edi, edi\n");
    fput("jns     .L3\n");
    fput("movsx   r8, r8d\n");
    fput("mov     eax, 32\n");
    fput("sub     rax, r8\n");
    fput("lea     r8d, [rdx+2]\n");
    fput("mov     BYTE [rsp+rax], 45\n");
    fput(".L3:\n");
    fput("movsx   rdx, r8d\n");
    fput("mov     eax, 33\n");
    fput("mov     edi, 1\n");
    fput("sub     rax, rdx\n");
    fput("mov     edx, r8d\n");
    fput("lea     rsi, [rsp+rax]\n");
    fput("xor     eax, eax\n");
    fput("mov rax, 1 ;; SYS_WRITE\n");
    fput("syscall \n");
    fput("add     rsp, 56\n");
    fput("ret\n");
}
