GLOBAL syscall_wizard

section .text

; uint64_t syscall_wizard(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx)
syscall_wizard:
	push rbp
	mov rbp, rsp

    ; Move argmuents to match syscall calling standard
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov rcx, r8
    mov r8, r9
    int 80h     

	mov rsp, rbp
	pop rbp
	ret

