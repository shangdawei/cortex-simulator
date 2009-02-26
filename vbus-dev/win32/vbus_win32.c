#include "vbus_win32.h"

bool win32_build_bus(char* busname, int poolsize)
{
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, 
						NULL, PAGE_READWRITE, 
						0, 
						poolsize, 
						busname);

	if(hMapFile == NULL){
		printf("fault: Can't build bus !!!\n");
		return FALSE;
	}

	pBuf = (char*)MapViewOfFile(hMapFile,
                        FILE_MAP_ALL_ACCESS,
                        0,                   
                        0,                   
                        0);

	if(pBuf == NULL){
		printf("fault: Can't map view of file !!!\n");
		return FALSE;
	}

	return TRUE;
}

bool win32_load_bus(char* busname)
{
	hMapFile =  OpenFileMapping(FILE_MAP_ALL_ACCESS, 
					FALSE, 
					busname);

	if(hMapFile == NULL){
		printf("fault: Can't load bus !!!\n");
		return FALSE;
	}

	pBuf = (char*)MapViewOfFile(hMapFile,
					FILE_MAP_ALL_ACCESS,
					0,
					0,
					0);

	if(pBuf == NULL){
		printf("fault: Can't map view of file !!!\n");
		return FALSE;
	}
	return TRUE;
}

void win32_read_bus(int addr, char* data, int size)
{
	int i;
	for(i = addr;i<size;i++)
		data[i-addr] = pBuf[i];
}

void win32_write_bus(int addr, char* data, int size)
{
	int i;
	for(i = addr;i<size;i++)
		pBuf[i] = data[i-addr];
}

void win32_release_bus()
{
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
}