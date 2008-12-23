#ifndef __DEVICE_H__
#define __DEVICE_H__

typedef struct{
	int memory_addr;
	int device_addr;
	int addr_length;
}MemTran;

typedef struct{
	char device_name[30];
	int device_ID;
	int interrupt;

	MemTran *memtran_table;

	int (*readPERI)(int, int);
	void (*writePERI)(int, int, int);
}DevieDes;

//BOOL registerDevice();
//BOOL deleteDevice();



#endif