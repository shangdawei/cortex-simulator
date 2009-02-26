#include "vbus_win32.h"

bool win32_build_bus(char* busname, int poolsize)
{
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, 
						NULL, PAGE_READWRITE, 
						0, 
						poolsize, 
						busname);

	pBuf = (LPTSTR)MapViewOfFile(hMapFile,
                        FILE_MAP_ALL_ACCESS,
                        0,                   
                        0,                   
                        0);
	return TRUE;
}

bool win32_load_bus(char* busname)
{
	hMapFile =  OpenFileMapping(FILE_MAP_ALL_ACCESS, 
					FALSE, 
					busname);

	pBuf = (LPTSTR)MapViewOfFile(hMapFile,
					FILE_MAP_ALL_ACCESS,
					0,
					0,
					0);
	return TRUE;
}

bool win32_read_bus(int addr, char* data, int size)
{
	int i;
	for(i = addr;i<size;i++)
		data[i-addr] = pBuf[i];

	return TRUE;
}

bool win32_write_bus(int addr, char* data, int size)
{
	int i;
	/*for(i = addr;i<size;i++)
		pBuf[i] = data[i-addr];*/

	return TRUE;
}

bool win32_release_bus()
{
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);

	return TRUE;
}