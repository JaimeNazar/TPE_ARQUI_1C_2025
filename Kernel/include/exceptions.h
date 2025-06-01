#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>
#include <syscallDispatcher.h>
#include <registers.h>
#include <interrupts.h>

#define ZERO_EXCEPTION_ID 0
#define UNDEF_OP_CODE_EXCEPTION_ID 6 //https://wiki.osdev.org/Interrupt_Descriptor_Table
#define GENERAL_REGISTERS_COUNT 15 
#define SPECIAL_REGISTERS_COUNT 5 
#define MSG_LENGTH 8

#define HEX_BASE 16
#define HEX_64_TEMPLATE "0x0000000000000000"
#define HEX_64_TEMPLATE_OFFSET 2 // Skip first two characters
#define HEX_64_TEMPLATE_LENGHT 18

void exceptionDispatcher(int exception);

#endif