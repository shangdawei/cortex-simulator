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

