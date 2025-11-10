section .data
    msg db 'Hello, World', 10    ; 10 is newline character

section .text
    global main

main:
    ; write system call
    mov rax, 1                  ; sys_write
    mov rdi, 1                  ; stdout
    mov rsi, msg                ; pointer to message
    mov rdx, 13                 ; message length (12 chars + newline)
    syscall

    ; exit system call
    mov rax, 60                 ; sys_exit
    mov rdi, 0                  ; exit status 0
    syscall
