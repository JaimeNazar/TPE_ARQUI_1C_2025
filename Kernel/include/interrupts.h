 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <stdint.h>

#define GENERAL_REGISTERS_COUNT 15 
#define SPECIAL_REGISTERS_COUNT 5 
#define MSG_LENGTH 8

#define HEX_BASE 16
#define HEX_64_TEMPLATE "0x0000000000000000"
#define HEX_64_TEMPLATE_OFFSET 2 // Skip first two characters
#define HEX_64_TEMPLATE_LENGHT 18

void interruptsDumpRegisters();

// --- From asm file ---
void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);
void _syscallHandler(void);

void _exception0Handler(void);
void _exception06Handler(void);

void _cli(void);

void _sti(void);

void _hlt(void);

void picMasterMask(uint8_t mask);

void picSlaveMask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */
