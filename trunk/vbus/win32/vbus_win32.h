#ifndef __VBUS_WIN32_H__
#define __VBUS_WIN32_H__

#include <windows.h>
#include "../vbus_structure.h"

HANDLE hMapFile;
LPCTSTR pBuf;

bool win32_build_bus(char* busname, int poolsize);
bool win32_load_bus(char* busname);
bool win32_release_bus();
bool win32_read_bus(int addr, char* data, int size);
bool win32_write_bus(int addr, char* data, int size);

#endif