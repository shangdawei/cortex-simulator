#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "../../win32/interface.h"
#include "../../memory.h"
#include "../../helper_procedures.h"

#define NINT 20

typedef struct INTpend{
	int INT_ID;
	int priority;
	int exec;
	struct INTpend *nextINT;
}INTpend;

typedef struct deviceDes{
	char dname[128];
	unsigned int memlist[128];
	void (*devDo)();
	void (*devInital)();

	struct deviceDes *nextdev;
}deviceDes;

static int INTlist[NINT];

static deviceDes *device_list;
static int ndevice;

static INTpend *Pending;//event pending queue
static int npend;

bool doCircle();
int initalDevice();
void addPending(int INTID,int exec);
void delPending(int INTID);
INTpend* findPending(int INTID);

#endif