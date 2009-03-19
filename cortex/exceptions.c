#include "exceptions.h"
#include "Memory.h"
#include "instruction.h"
#include "device/common/device.h"

#include <stdio.h>

//MemManage are listed by all instructions that perform explicit data memory access
void MemManage(void)
{
	//printf("Exception: MemManage\n");
	//printf("Press any key to continue, but the result is unpredictable");
	getchar();
}
	

//BusFault are listed by all instructions that perform explicit data memory access
void BusFault(void)
{
	//printf("Exception: BusFault\n");
	//printf("Press any key to continue, but the result is unpredictable");
	getchar();
}

//UsageFault exception can occur for a variety of reasons and are listed against instructions as appropriate
void UsageFault(void)
{
	//printf("Exception: UsageFault\n");
	//printf("Press any key to continue, but the result is unpredictable");
	getchar();
}

//SVCall exception is listed for SVC instruciton
void SVCall(void)
{
	//printf("Exception: SVCall\n");
	//printf("Press any key to continue, but the result is unpredictable");
	getchar();
}

//DebugMonitor exception is listed for BKPT instruction
void DebugMonitor(void)
{
	//printf("Exception: DebugMonitor\n");
	//printf("Press any key to continue, but the result is unpredictable");
	getchar();
}

//HardFault exceptions can arise from escalation of faults listed against an instruction, but are not 
//themselves listed.
void HardFault(void)
{
	//printf("Exception: HardFault\n");
	//printf("Press any key to continue, but the result is unpredictable");
	getchar();
}

void doEvent()
{
	int sp,  vector;
	int vector_table = 0;

	if(newINT == -1)
		return;

	sp = get_sp();
	set_MemA(sp - 8, 4, get_general_register($PC));
	set_MemA(sp - 4, 4, get_general_register($XPSR));
	set_MemA(sp - 32, 4, get_general_register($R0));
	set_MemA(sp - 28, 4, get_general_register($R1));
	set_MemA(sp - 24, 4, get_general_register($R2));
	set_MemA(sp - 20, 4, get_general_register($R3));
	set_MemA(sp - 16, 4, get_general_register($R12));
	set_MemA(sp - 12, 4, get_general_register($LR));
	set_sp(sp - 32);

	vector = get_MemA(vector_table + 4*newINT, 4);
	set_ipsr(newINT);
	set_pc(vector);
	if(isINT)
		set_lr(0xFFFFFFF1);
	else if((get_control() & 0x2))
		set_lr(0xFFFFFFFD);
	else
		set_lr(0xFFFFFFF9);
	set_control(0x0);
	newINT = -1;
	isINT = 1;
}

void exitEvent()
{
	int sp = get_sp() + 32;

	if(!isINT)
		return;

	if(INTover()){
		set_general_register($PC,get_MemA(sp - 8, 4));
		set_general_register($XPSR,get_MemA(sp - 4, 4));
		set_general_register($R0,get_MemA(sp - 32, 4));
		set_general_register($R1,get_MemA(sp - 28, 4));
		set_general_register($R2,get_MemA(sp - 24, 4));
		set_general_register($R3,get_MemA(sp - 20, 4));
		set_general_register($R12,get_MemA(sp - 16, 4));
		set_general_register($LR,get_MemA(sp - 12, 4));
		set_sp(sp + 32);
	}
}

int INTover()
{
/*This procedure check the PC register value to judgy the end of an Interrupt and set the processor mode 
and access level on return
*/
	switch(get_pc()){
		case 0xFFFFFFF1:// Return to handler mode
			isINT = 1;
			return 1;
		case 0xFFFFFFF9://Return to Thread mode and on return use the main stack
			isINT = 0;
			set_control(0x0);
			return 1;
		case 0xFFFFFFFD://Return to Thread mode and on return use the process stack
			isINT = 0;
			set_control(0x2);
			return 1;
	}
	return 0;
}

/*NVIC management functions
*/
int NVIC_getVectorTable()
{
/*This procedure returns Vector Table start address
*/
	return get_MemA(0xE000ED08,4);
}

int NVIC_ICSR_getINT()
{
	return (get_MemA(ICSR,4) & 0x001f);
}

void NVIC_ICSR_setINT(int Interrupt_ID)
{
	set_MemA(ICSR,4,((get_MemA(ICSR,4) & 0xffe0) | (Interrupt_ID & 0x001f)));
}

int NVIC_getPriority(int INT)
{
	return get_MemU(PRIORITY_REGS_BASE + INT -16, 1);
}

void NVIC_setPend(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	set_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
}

void NVIC_clrPend(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	set_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
}

int NVIC_getPend(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	if((get_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4) & (1<< (Interrupt_ID%32))))
		return 1;
		
	return 0;
}

void NVIC_setEnable(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	set_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
}

void NVIC_clrEnable(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	set_MemA(CLR_ENABLE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_ENABLE_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
}

int NVIC_getEnable(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	if(get_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4) & (1<< (Interrupt_ID%32)))
		return 1;

	return 0;
}

void NVIC_setActive(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	set_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
}

void NVIC_clrActive(int Interrupt_ID)
{
	Interrupt_ID -= 16;

	set_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
}