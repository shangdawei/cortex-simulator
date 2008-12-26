#include "interface.h"

bool initalBuffer()
{
/*This function create and configure a buffer for communication between simulator and peripherals.
The buffer structure
	0 : register signs whether there's interruption
	1-241 : Event registers to record which interruption takes place during the last instruction period
	others : data communication
*/
	hMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 0, PERISIZE, MEMID);
	ibufferr = (LPBYTE)MapViewOfFile(hMemMap, FILE_MAP_READ, 0, 0, 0);
	ibufferw = (LPBYTE)MapViewOfFile(hMemMap, FILE_MAP_WRITE, 0, 0, 0);
	return true;
}

bool eventUpdate(int *EXC_ID)
{
/*This function is to :
1.Find out whether an interrupt happens
2.Updates NVIC register
3.Updates pending Queue
*/
	int i;

	if(!ibufferr[0])
		return false;

	for(i = 1; i < NINT + 1; i++){
		if(!ibufferr[INTlist[i]] && (!NVIC_getPend(INTlist[i]))){
			if(NVIC_getEnable(INTlist[i]))
				addPending(INTlist[i],0);
			NVIC_setPend(INTlist[i]);
		}
		ibufferw[INTlist[i]] = 0;
	}
	ibufferw[0] = 0;
	return true;
}