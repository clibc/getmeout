# getmeout - Stack-oriented programming language

```
push 5
push 1
sub 
push 4
== if
        push 413
        pprint
        //exit 0
end
push -1
pprint
exit 0
```
`Output:`
```
413
-1
```

`Generated assembly code:`
```
BITS 64
segment .text
global _start
_start:
;; push
    push 5
;; push
    push 1
;; sub
    pop rax
    pop rbx
    sub rbx,rax
    push rbx
;; push
    push 4
;;isequal
    mov rbx, 1
    mov rcx, 0
    pop rax
    pop rdx
    push rdx
    push rax
    cmp rax,rdx
    cmovz rax, rbx
    push rax
;;-----if---
    pop rax
    cmp rax, 1
    jnz .JA0
;; push
    push 413
;;pprint
    pop rdi
    push rdi
    call pprint
;;-----END---
    .JA0:
;; push
    push -1
;;pprint
    pop rdi
    push rdi
    call pprint
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