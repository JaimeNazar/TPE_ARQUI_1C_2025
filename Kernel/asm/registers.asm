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
GLOBAL save_registers

GLOBAL get_special_registers
GLOBAL save_special_registers

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


; Returns general purpose registers array address
get_registers:
	push rbp
	mov rbp, rsp

	mov rax, regs

	mov rsp, rbp
    pop rbp	
	ret

; Saves general registers current state
save_registers:

	mov [regs], rax ; General Purpose Registers
	mov [regs+8], rbx
	mov [regs+8*2], rcx
	mov [regs+8*3], rdx
	mov [regs+8*4], rsi
	mov [regs+8*5], rdi
	mov [regs+8*6], rbp
	mov [regs+8*7], r8
	mov [regs+8*8], r9
	mov [regs+8*9], r10
	mov [regs+8*10], r12
	mov [regs+8*11], r13
	mov [regs+8*12], r14
	mov [regs+8*13], r15

	ret

; ------ SPECIAL REGISTERS ------
; These must only be called during an interrupt

; Returns special registers vector
get_special_registers:
	push rbp
    mov rbp, rsp

	mov rax, spec_regs

	mov rsp, rbp
    pop rbp	
    ret

	; Save special registers state, should be  called right after interrupt
save_special_registers:
	push rbp
    mov rbp, rsp

	push rax

	mov rax, [rbp+8*2]	; Start with offset pushed values
	mov [spec_regs], rax 	; rip

	mov rax, [rbp+8*3]
	mov [spec_regs+8], rax	; cs

	mov rax, [rbp+8*4]
	mov [spec_regs+8*2], rax	; rflags

	mov rax, [rbp+8*5]
	mov [spec_regs+8*3], rax	; last rsp

	mov rax, [rbp+8*6]
	mov [spec_regs+8*4], rax ; ss

	pop rax

	mov rsp, rbp
    pop rbp	
	ret


section .bss
	regs resq 14
	spec_regs resq 5
