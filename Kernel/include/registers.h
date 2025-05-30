#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

uint64_t get_rax();
uint64_t get_rbx();
uint64_t get_rcx();
uint64_t get_rdx();
uint64_t get_rsi();
uint64_t get_rdi();
uint64_t get_rsp();
uint64_t get_rbp();
uint64_t get_r8();
uint64_t get_r9();
uint64_t get_r10();
uint64_t get_r11();
uint64_t get_r12();
uint64_t get_r13();
uint64_t get_r14();
uint64_t get_r15();

uint64_t* get_registers();

// Special registers, only work for interrupts
uint64_t get_eip();
uint64_t get_cs();   // Code segment
uint64_t get_rflags();
uint64_t get_last_rsp();
uint64_t get_ss();   // Stack segment

#endif // REGISTERS_H