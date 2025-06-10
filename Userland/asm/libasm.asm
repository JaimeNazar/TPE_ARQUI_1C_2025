GLOBAL syscall_wizard
GLOBAL syscall_register_dump
GLOBAL test_Invalid_OpCode
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

; Special function to avoid modifying registers
syscall_register_dump:
	push rbp
	mov rbp, rsp

    push rax    ; Save rax

    mov rax, id_reg_dump
    int 80h;

    pop rax

	mov rsp, rbp
	pop rbp
    ret

test_Invalid_OpCode:
    ud2
    ret

section .rodata
    id_reg_dump equ 17