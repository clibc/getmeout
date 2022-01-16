# getmeout - Stack-oriented programming language

```
push 10
push 0

for
    push i
    push 0
    for
        strprint "*"
    loop
    strprint "\n"
loop
exit 0
```
`Output:`
```
*
**
***
****
*****
******
*******
********
*********
**********
***********```

`Generated assembly code:`
```
BITS 64
segment .data
LPPE0 dq 0
LPPI0 dq 0
LPPE1 dq 0
LPPI1 dq 0
str0 db "*"
strLen0 equ $- str0
str1 db 10,""
strLen1 equ $- str1
segment .text
global _start
_start:
;; push
    push 10
;; push
    push 0
;; FOR ------
pop rax
pop rbx
push rbx
push rax
mov [LPPE0], rbx
mov [LPPI0], rax
.JA13:
cmp rax, rbx
jg .JA2
;;  push i
mov rax, [LPPI0]
push rax
;; push
    push 0
;; FOR ------
pop rax
pop rbx
push rbx
push rax
mov [LPPE1], rbx
mov [LPPI1], rax
.JA8:
cmp rax, rbx
jg .JA5
;;stringprint
    mov rax, 1
    mov rdi, 1
    mov rsi, str0
    mov rdx, strLen0
    syscall
;; LOOP ------
mov rax, [LPPI1]
mov rbx, [LPPE1]
inc rax
mov [LPPI1], rax 
jmp .JA8
.JA5:
;;stringprint
    mov rax, 1
    mov rdi, 1
    mov rsi, str1
    mov rdx, strLen1
    syscall
;; LOOP ------
mov rax, [LPPI0]
mov rbx, [LPPE0]
inc rax
mov [LPPI0], rax 
jmp .JA13
.JA2:
;; exit --- 
    mov rdi, 0x00
    mov rax, 60
    syscall
pop rdi
mov rax, 60
syscall


pprint:
sub     rsp, 56
mov     eax, edi
mov     r8d, 1
mov     r9d, 3435973837
neg     eax
mov     BYTE [rsp+32], 10
lea     rsi, [rsp+31]
cmovs   eax, edi
.L2:
mov     edx, eax
sub     rsi, 1
imul    rdx, r9
shr     rdx, 35
lea     ecx, [rdx+rdx*4]
add     ecx, ecx
sub     eax, ecx
add     eax, 48
mov     BYTE [rsi+1], al
mov     eax, edx
mov     edx, r8d
add     r8d, 1
test    eax, eax
jne     .L2
test    edi, edi
jns     .L3
movsx   r8, r8d
mov     eax, 32
sub     rax, r8
lea     r8d, [rdx+2]
mov     BYTE [rsp+rax], 45
.L3:
movsx   rdx, r8d
mov     eax, 33
mov     edi, 1
sub     rax, rdx
mov     edx, r8d
lea     rsi, [rsp+rax]
xor     eax, eax
mov rax, 1 ;; SYS_WRITE
syscall 
add     rsp, 56
ret
```