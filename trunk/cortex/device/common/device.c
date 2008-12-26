#include "device.h"

int initalDevice()
{
	device_list->nextdevice = 0;
	initalBuffer();
	return 0;
}

bool doCircle()
{
	int curPRI,curINT;

	if(!eventUpdate())
		return false;

	if(get_faultmask())
		curPRI = -1;
	else if(get_primask())
		curPRI = 0;
	else if(get_basepri())
		curPRI = get_basepri();
	else if(getMode()){
		curINT = NVIC_ICSR_getINT();
		curPRI = NVIC_getPriority(curINT);
	}
	else
		curPRI = 500;

	if(curPRI <= Pending->nextINT->priority)
		return false;
	if(curPRI != 500){
		addPending(curINT,1);
		NVIC_setPend(curINT);
		NVIC_clrActive(curINT);
	}
	curINT = Pending->nextINT->INT_ID;
	delPending(curINT);
	NVIC_clrPend(curINT);
	NVIC_setActive(curINT);
	NVIC_ICSR_setINT(curINT);
	return true;
	
}

void addPending(int INTID, int exec)
{
	INTpend *pendptr,*keep;
	if(!findPending(INTID))
		return;
	if(npend){
		for(pendptr = Pending;pendptr->nextINT->nextINT !=0 && NVIC_getPriority(INTID) < pendptr->nextINT->priority;pendptr = pendptr->nextINT);
		if(NVIC_getPriority(INTID) >= pendptr->nextINT->priority)
			pendptr = pendptr->nextINT;
		keep = pendptr->nextINT;
		pendptr->nextINT = malloc(sizeof(INTpend));
		pendptr->nextINT->exec = exec;
		pendptr->nextINT->INT_ID = INTID;
		pendptr->nextINT->priority =NVIC_getPriority(INTID);
		pendptr->nextINT = keep;
	}
	else{
		Pending->nextINT = malloc(sizeof(INTpend));
		Pending->nextINT->exec = exec;
		Pending->nextINT->INT_ID = INTID;
		Pending->nextINT->priority =NVIC_getPriority(INTID);
		Pending->nextINT = 0;
	}
}

void delPending(int INTID)
{
	INTpend *pendptr,*keep;
	if(!npend)
		return;
	for(pendptr = Pending;pendptr->nextINT->nextINT !=0;pendptr = pendptr->nextINT){
		if(pendptr->nextINT->INT_ID == INTID){
			keep = pendptr->nextINT;
			pendptr->nextINT = pendptr->nextINT->nextINT;
			free(keep);
		}
	}
	if(pendptr->nextINT->INT_ID == INTID){
		keep = pendptr->nextINT;
		pendptr->nextINT = pendptr->nextINT->nextINT;
		free(keep);
	}
}

INTpend* findPending(int INTID)
{
	INTpend *pendptr;
	if(!npend)
		return 0;
	for(pendptr = Pending->nextINT;pendptr->nextINT !=0;pendptr = pendptr->nextINT)
		if(pendptr->INT_ID == INTID)
			return pendptr;
	if(pendptr->INT_ID == INTID)
		return pendptr;
	return 0;
}