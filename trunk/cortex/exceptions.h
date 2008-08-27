/**
 * This file declare all exceptions here.
 */
#ifndef _EXCEPTIONS
#define _EXCEPTIONS

#include <stdio.h>
#include "instruction.h"

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

#endif;

