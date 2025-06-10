
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _syscallHandler


;exceptions.c
GLOBAL _exception0Handler
GLOBAL _exception06Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher

; Registers utils
EXTERN save_registers
EXTERN save_special_registers
EXTERN get_registers
EXTERN get_special_registers

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, [rsp + 8]       ;guardo el rip para luego mostrarlo
	;mov [ripBackup], rdi

	mov rdi, %1 ; pasaje de parametro

	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro


%macro exceptionHandler 1
	call save_special_registers	; Save current state of registers memory, which reside in stack base
	call save_registers	; Exception handler will use it later

	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState

	mov rax, userland
	mov [rsp], rax	; Set return address to userland

	iretq	

%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret

; Enable hardware interrupts
_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

_syscallHandler:

	cmp rax, id_reg_dump	; Check if the syscall needs the registers saved
	jne .continue

	; --- RECOVER RAX ---
	call save_registers	; Exception handler will use it later
	call save_special_registers	; Save current state of registers memory, which reside in stack base
	
	; Get RAX original value
	push rax	; Save sycall id
	push rbx	; Save aux registers
	push rcx
	call get_special_registers	; Get special registers array address
	
	mov rbx, [rax+8*3]	; Get user RSP address, where RAX was passed
	mov rcx, [rbx]	; Read RAX value

	; Now put it on the array containing the registers values
	call get_registers	; Get registers array address

	mov [rax], rcx ; RAX is the first element

	pop rcx	; Restore registers 
	pop rbx	; Restore registers
	pop rax

.continue:

	push rbx
	push rcx
	push rdx
	push rbp

	; Move arguments to the x86_64 ABI standard for passing parameters
	mov r9, r8
	mov r8, rcx
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, rax
	
	call syscallDispatcher

	pop rbp
	pop rdx
	pop rcx
	pop rbx
	iretq

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0


;Operation Invalid Code
_exception06Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret

section .rodata
	userland equ 0a00000h
	id_reg_dump equ 17

SECTION .bss
	aux resq 1
	ripBuffer resb 8
