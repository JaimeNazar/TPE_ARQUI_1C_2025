GLOBAL get_rax
GLOBAL get_rbx
GLOBAL get_rcx
GLOBAL get_rdx
GLOBAL get_rsi
GLOBAL get_rdi
GLOBAL get_rsp
GLOBAL get_rbp
GLOBAL get_r8
GLOBAL get_r9
GLOBAL get_r10
GLOBAL get_r11
GLOBAL get_r12
GLOBAL get_r13
GLOBAL get_r14
GLOBAL get_r15

GLOBAL get_registers
GLOBAL get_eip
GLOBAL get_cs
GLOBAL get_rflags
GLOBAL get_last_rsp
GLOBAL get_ss

section .text

get_rax:
	ret

get_rbx:

	push rbp
    mov rbp, rsp

	mov RAX,RBX

	mov rsp, rbp
    pop rbp	
    ret

get_rcx:

	push rbp
    mov rbp, rsp

	mov RAX,RCX

	mov rsp, rbp
    pop rbp	
    ret

get_rdx:

	push rbp
    mov rbp, rsp

	mov RAX,RDX

	mov rsp, rbp
    pop rbp	
    ret


get_rsi:

	push rbp
    mov rbp, rsp

	mov RAX,RSI

	mov rsp, rbp
    pop rbp	
    ret

get_rdi:

	push rbp
    mov rbp, rsp

	mov RAX,RDI

	mov rsp, rbp
    pop rbp	
    ret

get_rsp:

	push rbp
    mov rbp, rsp

	mov RAX,RSP

	mov rsp, rbp
    pop rbp	
    ret

get_rbp:

	push rbp
    mov rbp, rsp

	mov RAX,[RBP + 8]

	mov rsp, rbp
    pop rbp	
    ret


get_r8:

	push rbp
    mov rbp, rsp

	mov RAX,R8

	mov rsp, rbp
    pop rbp	
    ret

get_r9:

	push rbp
    mov rbp, rsp

	mov RAX,R9

	mov rsp, rbp
    pop rbp	
    ret

get_r10:

	push rbp
    mov rbp, rsp

	mov RAX,R10

	mov rsp, rbp
    pop rbp	
    ret

get_r11:

	push rbp
    mov rbp, rsp

	mov RAX,R11

	mov rsp, rbp
    pop rbp	
    ret

get_r12:

	push rbp
    mov rbp, rsp

	mov RAX,R12

	mov rsp, rbp
    pop rbp	
    ret

get_r13:

	push rbp
    mov rbp, rsp

	mov RAX,R13

	mov rsp, rbp
    pop rbp	
    ret

get_r14:

	push rbp
    mov rbp, rsp

	mov RAX,R14

	mov rsp, rbp
    pop rbp	
    ret

get_r15:

	push rbp
    mov rbp, rsp

	mov RAX,R15

	mov rsp, rbp
    pop rbp	
    ret


; Returns general purpose registers
get_registers:
	push rbp
    mov rbp, rsp

	mov [regs], rax ; General Purpose Registers
	mov [regs+8], rbx
	mov [regs+8*2], rcx
	mov [regs+8*3], rdx
	mov [regs+8*4], rsi
	mov [regs+8*5], rdi
	mov [regs+8*6], rsp
	mov [regs+8*7], rbp
	mov [regs+8*8], r8
	mov [regs+8*9], r9
	mov [regs+8*10], r10
	mov [regs+8*11], r12
	mov [regs+8*12], r13
	mov [regs+8*13], r14
	mov [regs+8*14], r15

	mov rax, regs

	mov rsp, rbp
    pop rbp	
	ret

; ------ SPECIAL REGISTERS ------
; These must be called during an interrups
get_eip:

	push rbp
    mov rbp, rsp

	mov rax, [rbp]

	mov rsp, rbp
    pop rbp	
    ret

get_cs:

	push rbp
    mov rbp, rsp

	mov rax, [rbp+8]

	mov rsp, rbp
    pop rbp	
    ret

get_rflags:

	push rbp
    mov rbp, rsp

	mov rax, [rbp+8*2]

	mov rsp, rbp
    pop rbp	
    ret

get_last_rsp:

	push rbp
    mov rbp, rsp

	mov rax, [rbp+8*3]

	mov rsp, rbp
    pop rbp	
    ret

get_ss:

	push rbp
    mov rbp, rsp

	mov rax, [rbp+8*4]

	mov rsp, rbp
    pop rbp	
    ret

section .bss
	regs resq 15
