/**
 * This file declare all exceptions here.
 */
#ifndef _EXCEPTIONS
#define _EXCEPTIONS

#include <stdio.h>
#include "instruction.h"
#include "Memory.h"
#include "device/common/device.h"

#define SET_ENABLE_REGS_BASE	0xE000E100
#define CLR_ENABLE_REGS_BASE	0xE000E180
#define SET_PEND_REGS_BASE		0xE000E200
#define CLR_PEND_REGS_BASE		0xE000E280
#define PRIORITY_REGS_BASE		0xE000E400
#define ACTIVE_REGS_BASE		0xE000E300
#define ICSR					0xE000ED04	//Interrupt Control and State Register

//MemManage are listed by all instructions that perform explicit data memory access
void MemManage(void);

//BusFault are listed by all instructions that perform explicit data memory access
void BusFault(void);

//UsageFault exception can occur for a variety of reasons and are listed against instructions as appropriate
void UsageFault(void);

//SVCall exception is listed for SVC instruciton
void SVCall(void);

//DebugMonitor exception is listed for BKPT instruction
void DebugMonitor(void);

//HardFault exceptions can arise from escalation of faults listed against an instruction, but are not 
//themselves listed.
void HardFault(void);

int NVIC_getVectorTable();
int NVIC_ICSR_getINT();
void NVIC_ICSR_setINT(int Interrupt_ID);

void NVIC_setPend(int Interrupt_ID);
void NVIC_clrPend(int Interrupt_ID);
int NVIC_getPend(int Interrupt_ID);

void NVIC_setEnable(int Interrupt_ID);
void NVIC_clrEnable(int Interrupt_ID);
int NVIC_getEnable(int Interrupt_ID);

void NVIC_setActive(int Interrupt_ID);
void NVIC_clrActive(int Interrupt_ID);

int NVIC_getPriority(int Interrupt_ID);

#endif;

