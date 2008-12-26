#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "../../win32/interface.h"
#include "../../memory.h"

#define NINT 20

typedef struct{
	int memory_addr;
	int device_addr;
	int addr_length;
}MemTran;

typedef struct INTpend{
	int INT_ID;
	int priority;
	int exec;
	struct INTpend *nextINT;
}INTpend;

typedef struct DeviceDes{
	int device_ID;
	MemTran *memtran_table;

	struct DeviceDes *nextdevice;
}DeviceDes;

static int INTlist[NINT];

static DeviceDes *device_list;
static int ndevice;

static INTpend *Pending;//event pending queue
static int npend;

bool doCircle();
int initalDevice();
void addPending(int INTID,int exec);
void delPending(int INTID);
INTpend* findPending(int INTID);

#endif