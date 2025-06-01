#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>
#include <syscallDispatcher.h>
#include <registers.h>
#include <interrupts.h>

#define ZERO_EXCEPTION_ID 0
#define UNDEF_OP_CODE_EXCEPTION_ID 6 //https://wiki.osdev.org/Interrupt_Descriptor_Table

void exceptionDispatcher(int exception);

#endif