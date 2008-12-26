#include "exceptions.h"

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
	return get_MemU(PRIORITY_REGS_BASE + INT - 1, 1);
}

void NVIC_setPend(int Interrupt_ID)
{
	set_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
	addPending(Interrupt_ID,0);
}

void NVIC_clrPend(int Interrupt_ID)
{
	set_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
	delPending(Interrupt_ID);
}

int NVIC_getPend(int Interrupt_ID)
{
	if((get_MemA(SET_PEND_REGS_BASE + Interrupt_ID/32,4) & (1<< (Interrupt_ID%32))) &&
		(!(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) & (1<< (Interrupt_ID%32)))))
		return 1;
	else
		return 0;
}

void NVIC_setEnable(int Interrupt_ID)
{
	set_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_PEND_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
	if(NVIC_getPend(Interrupt_ID))
		addPending(Interrupt_ID,0);
}

void NVIC_clrEnable(int Interrupt_ID)
{
	set_MemA(CLR_ENABLE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(CLR_ENABLE_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
	set_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
	if(NVIC_getPend(Interrupt_ID))
		if(!(findPending(Interrupt_ID)->exec))
			delPending(Interrupt_ID);
}

int NVIC_getEnable(int Interrupt_ID)
{
	if((get_MemA(SET_ENABLE_REGS_BASE + Interrupt_ID/32,4) & (1<< (Interrupt_ID%32))) &&
		(!(get_MemA(CLR_ENABLE_REGS_BASE + Interrupt_ID/32,4) & (1<< (Interrupt_ID%32)))))
		return 1;
	else
		return 0;
}

void NVIC_setActive(int Interrupt_ID)
{
	set_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4) | (1<< (Interrupt_ID%32))));
}

void NVIC_clrActive(int Interrupt_ID)
{
	set_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4,
		(get_MemA(ACTIVE_REGS_BASE + Interrupt_ID/32,4) & (~(1<< (Interrupt_ID%32)))));
}