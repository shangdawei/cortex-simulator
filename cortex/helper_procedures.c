/**
 *
 * The functions described in this file are not part of the pseudo-code specification. They are helper
 * procedures and functions used by pseudo-code to perform useful architecture-specific jobs. Each has a brief
 * description and a pseudo-code prototype. Some have had a pseudo-code definition added.
 *
 */
#include "helper_procedures.h"

void ALUWritePC(int value)
{
/*
This procedure writes a value to the PC with the correct semantics for such a write by the ADD
(register) and MOV (register) data-processing instructions.
*/
	set_pc(value);
}

int ArchVersion()
{
//This function returns the major version number of the architecture.
	return 2;
}

bool Bad_Reg(int n)
{
//This function performs the check for the register numbers 13 and 15 that are disallowed for many Thumb register specifiers.
	return (n == 13 || n == 15);
}

/* 
Cortex-M3 处理器内核有一个配置管脚 BIGEND，能够使用它来选择小端格式或大端格式。
Thumb 指令 SETEND 可以设置存储器格式，但 Cortex-M3 处理器不支持该指令。	
	——摘自 蓝色书
*/
bool BigEndian()
{
/*	
This function returns TRUE if load/store operations are currently big-endian, and FALSE if they are 
little-endian.
*/
	return false;
}

void BranchWritePC(int value)
{
//This procedure writes a value to the PC with the correct semantics for such writes by simple branches - that is, just a change to the PC in all circumstances.
}

void BXWritePC(int value) {
/*
	This procedure writes a value to the PC with the correct semantics for such writes by interworking 
	instructions. That is, with BX-like interworking behavior in all circumstances.
*/
	set_pc(value);
}

bool InITBlock()
{
//This function returns TRUE if execution is currently in an IT block and FALSE otherwise.
}

bool LastInITBlock()
{
//This function returns TRUE if the current instruction is the last instruction in an IT block, and FALSE otherwise.
}

void LoadWritePC(int value)
{
//This procedure writes a value to the PC with BX-like interworking behavior for writes by load instructions.
	set_pc(value);
}
bool IntegerZeroDivideTrappingEnabled()
{
/*
This function returns TRUE if the trapping of divisions by zero in the integer division instructions SDIV
and UDIV is enabled, and FALSE otherwise.
In the M profile, this is controlled by the DIV_0_TRP(P452) bit in the Configuration Control register. TRUE is
returned if the bit is 1 and FALSE if it is 0.
*/
	return true;
}

void RaiseIntegerZeroDivide()
{/*
This procedure raises the appropriate exception for a division by zero in the integer division instructions
SDIV and UDIV.
In the M profile, this is a UsageFault exception.
*/
	printf("Usage fault exception: a division by zero in the integer division instructions!\n");
}

int ThisInstr()
{
/*
This function returns the currently-executing instruction. It is only used on 32-bit instruction encodings at 
present. 
*/
	return get_MemA(get_pc(), 4);
}