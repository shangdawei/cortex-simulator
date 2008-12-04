/**
 *
 * The functions described in this file are not part of the pseudo-code specification. They are helper
 * procedures and functions used by pseudo-code to perform useful architecture-specific jobs. Each has a brief
 * description and a pseudo-code prototype. Some have had a pseudo-code definition added.
 *
 */
#include "helper_procedures.h"
#include "exceptions.h"

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
	set_pc(value);
}

void BreakPoint()
{
//This procedure causes a debug breakpoint to occur.
	DebugMonitor();
}

void BXWritePC(int value) {
/*
	This procedure writes a value to the PC with the correct semantics for such writes by interworking 
	instructions. That is, with BX-like interworking behavior in all circumstances.
*/
	set_pc(value);
}

void CallSupervisor()
{
//In the M profile, this procedure causes an SVCall exception.
	SVCall();
}

void ClearEventRegister()
{
//This procedure clears the event register on the current processor.

}

void ClearExclusiveMonitors()
{
//This procedure clears the monitors used by the load/store exclusive instructions.
}



bool ConditionPassed(short cond)
{
/*This function performs the condition test for an instruction, based on:
• the two Thumb conditional branch encodings (encodings T1 andT3 of the B instruction)
• the current values of the xPSR.IT[7:0] bits for other Thumb instructions.
  refered to the datasheet Page 96
*/
	switch(cond){
		case 0:  if(get_flag_z())
					 return true;
				 else
					 return false;
		case 1:  if(!get_flag_z())
					 return true;
				 else
					 return false;
		case 2:  if(get_flag_c())
					 return true;
				 else
					 return false;
		case 3:  if(!get_flag_c())
					 return true;
				 else
					 return false;
		case 4:  if(get_flag_n())
					 return true;
				 else
					 return false;
		case 5:  if(!get_flag_n())
					 return true;
				 else
					 return false;
		case 6:  if(get_flag_v())
					 return true;
				 else
					 return false;
		case 7:  if(!get_flag_v())
					 return true;
				 else
					 return false;
		case 8:  if(get_flag_c() && (!get_flag_z()))
					 return true;
				 else
					 return false;
		case 9:  if((!get_flag_c()) || get_flag_z())
					 return true;
				 else
					 return false;
		case 10: if(get_flag_n() == get_flag_v())
					 return true;
				 else
					 return false;
		case 11: if(get_flag_n() != get_flag_v())
					 return true;
				 else
					 return false;
		case 12: if( (!get_flag_z()) && (get_flag_n()==get_flag_v()))
					 return true;
				 else
					 return false;
		case 13: if(get_flag_z() || (get_flag_n() != get_flag_v()))
					 return true;
				 else 
					 return false;
		case 14: if(InITBlock())
					 return true;//can only be used with IT instructions,but havn't been implemented
				 else
					 return false;
		case 15: return true;
		default: return false;



	}


	return true;
}

bool CurrentModeIsPrivileged()
{
// ?
	return true;
}

void DataMemoryBarrier(char option)
{
//This procedure produces a Data Memory Barrier.
}

void DataSynchronizationBarrier(char option)
{
//This procedure produces a Data Synchronization Barrier.
}

void DecodeImmShift()
{
/*
These functions perform the standard 2-bit type, 5-bit amount and 2-bit type decodes for immediate and 
register shifts respectively.
*/
}

void DecodeRegShift()
{
/*
These functions perform the standard 2-bit type, 5-bit amount and 2-bit type decodes for immediate and 
register shifts respectively.
*/
}

bool EventRegistered()
{
/*
This function returns TRUE if the event register on the current processor is set and FALSE if it is clear. The 
event register is set as a result of any of the following events:
• an IRQ interrupt, unless masked by the CPSR I-bit
• an FIQ interrupt, unless masked by the CPSR F-bit
• an Imprecise Data abort, unless masked by the CPSR A-bit
• a Debug Entry request, if Debug is enabled
• an event sent by any processor in the multi-processor system as a result of that processor executing a 
Hint_SendEvent()
• an exception return
• implementation-specific reasons, that might be IMPLEMENTATION DEFINED but also might occur 
arbitrarily.
The state of the event register is UNKNOWN at Reset.
*/
	return true;
}

void EncodingSpecificOperations()
{
/*
This procedure invokes the encoding-specific pseudo-code for an instruction encoding and checks the 
’should be’ bits of the encoding, as described in Instruction encoding diagrams and pseudo-code on 
page AppxA-2.
*/
}

bool ExclusiveMonitorsPass(int address, int size)
{
/*
This function determines whether a store exclusive instruction is successful. A store exclusive is successful 
if it still has possession of the exclusive monitors.
*/
	return true;
}

int ExecutionPriority()
{
// ??
	return 0;
}

void Hint_Debug(char option)
{
//This procedure supplies a hint to the debug system.
	printf("Hint_Debug: 0x%x \n", option);
}

void Hint_PreloadData(int address)
{
//This procedure performs a preload data hint.
	printf("Hint_PreloadData: 0x%x \n", address);
}

void Hint_PreloadInstr(int address)
{
//This procedure performs a preload instructions hint.
	printf("Hint_PreloadInstr: 0x%x \n", address);
}

void Hint_SendEvent()
{
//This procedure performs a send event hint.
	printf("Hint_SendEvent \n");
}

void Hint_Yield()
{
//This procedure performs a Yield hint.
	printf("Hint_Yield \n");
}

bool InITBlock()
{
//This function returns TRUE if execution is currently in an IT block and FALSE otherwise.
	if(get_epsr() & 0x0600fc00){
		return true;
	}
	else
		return false;
}

void InstructionSynchronizationBarrier(char option)
{
//This procedure produces an Instruction Synchronization Barrier.
}

bool IntegerZeroDivideTrappingEnabled()
{
/*
This function returns TRUE if the trapping of divisions by zero in the integer division instructions SDIV 
and UDIV is enabled, and FALSE otherwise.
In the M profile, this is controlled by the DIV_0_TRP bit in the Configuration Control register. TRUE is 
returned if the bit is 1 and FALSE if it is 0.
*/
	return true;
}

bool LastInITBlock()
{
//This function returns TRUE if the current instruction is the last instruction in an IT block, and FALSE otherwise.
	short it=get_epsr();
	if((it&0x06000c00)==0x00000800)
		return true ;
	else 
		return false;


}

void LoadWritePC(int value)
{
//This procedure writes a value to the PC with BX-like interworking behavior for writes by load instructions.
	set_pc(value);
}

void RaiseCoprocessorException()
{
//This procedure raises a UsageFault exception for a rejected coprocessor instruction.
	UsageFault();
}

void RaiseIntegerZeroDivide()
{/*
This procedure raises the appropriate exception for a division by zero in the integer division instructions
SDIV and UDIV.
In the M profile, this is a UsageFault exception.
*/
	UsageFault();
}

void SetExclusiveMonitors(int address, int size)
{
//This procedure sets the exclusive monitors for a load exclusive instruction.
}

void StartITBlock(int firstcond, int mask)
{
//This procedure starts an IT block with specified first condition and mask values.
	set_epsr(((firstcond<<12)&0xf000)|((mask<<8)&0xc00)|((mask<<25)&0x6000000)|(get_epsr()&0x1000000));


}

int ThisInstr()
{
/*
This function returns the currently-executing instruction. It is only used on 32-bit instruction encodings at 
present. 
*/
	return get_MemA(get_pc(), 4);
}

void WaitForEvent()
{
/*
This procedure causes the processor to suspend execution until any processor in the multiprocessor system 
executes a SEV instruction, or any of the following occurs for the processor itself:
• an event signalled by another processor using the SEV (Send Event) instruction
• any exception entering the Pending state if the SEVONPEND bit is set in the System Control register.
• an asynchronous exception at a priroity that pre-empts any currently active exceptions
• a Debug Event with debug enabled
• implementation-specific reasons, that might be IMPLEMENTATION DEFINED but also might occur 
arbitrarily
• Reset.
If the Event Register is set, Wait For Event clears it and returns immediately.
It is IMPLEMENTATION DEFINED whether or not restarting execution after the period of suspension causes a 
ClearEventRegister() to occur.
*/
}

void WaitForInterrupt()
{
/*
This procedure causes the processor to suspend execution until any of the following occurs for that 
processor:
• an asynchronous exception at a priroity that pre-empts any currently active exceptions
• a Debug Event with debug enabled
• implementation-specific reasons, that might be IMPLEMENTATION DEFINED but also might occur 
arbitrarily
• reset.
*/
}