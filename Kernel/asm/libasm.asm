GLOBAL cpuVendor
GLOBAL rtc
GLOBAL get_keyboard_status
GLOBAL get_keyboard_output

; soundDriver
GLOBAL outb
GLOBAL inb

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


; uint8_t rtc(uint8_t selection)
rtc:
	push rbp
	mov rbp, rsp

	mov al, dil	; Get selection

	out 70h, al		; Pass selection

	xor rax, rax
	in al, 71h
	
	leave
	ret

; uint8_t keyboard_status()
get_keyboard_status:
	push rbp
	mov rbp, rsp

	xor rax, rax
	in al, 64h		; Read status register

	leave
	ret

; uint8_t keyboard_output()
get_keyboard_output:
	push rbp
	mov rbp, rsp

    mov rax, 0

.cicle:
	in al, 64h
    and al, 0x01
    je .cicle
    in al, 60h

	mov rsp, rbp
	pop rbp
    ret


outb:

    mov dx, di        ; DI contiene el puerto (uint16_t)
    mov al, sil       ; SIL contiene el valor (uint8_t)
    out dx, al		  ; Escribe AL en el puerto DX

	
    ret

inb:

    mov dx, di        ; DI contiene el puerto
    in al, dx
    movzx eax, al     ; Expande AL a EAX ( lo pasa de uint8_t a uint32_t llenandolo con ceros)

    ret