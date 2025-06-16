#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#include <syscallDispatcher.h>

#define GENERAL_REGISTERS_COUNT 15 
#define SPECIAL_REGISTERS_COUNT 5 
#define MSG_LENGTH 8

#define HEX_BASE 16
#define HEX_64_TEMPLATE "0x0000000000000000"
#define HEX_64_TEMPLATE_OFFSET 2 // Skip first two characters
#define HEX_64_TEMPLATE_LENGHT 18

extern uint64_t get_rax();
extern uint64_t get_rbx();
extern uint64_t get_rcx();
extern uint64_t get_rdx();
extern uint64_t get_rsi();
extern uint64_t get_rdi();
extern uint64_t get_rsp();
extern uint64_t get_rbp();
extern uint64_t get_r8();
extern uint64_t get_r9();
extern uint64_t get_r10();
extern uint64_t get_r11();
extern uint64_t get_r12();
extern uint64_t get_r13();
extern uint64_t get_r14();
extern uint64_t get_r15();

extern void save_registers();
extern uint64_t* get_registers();

// Special registers, will only work for interrupts

// Returns array with the following order: RIP, CS, RFLAGS and SS
extern uint64_t* get_special_registers();
extern void save_special_registers();

/* Outputs a dump of the registers via the specified file descriptor */
void registersDump();

#endif // REGISTERS_H