#ifndef __VBUS_WIN32_H__
#define __VBUS_WIN32_H__

#include <windows.h>

static HANDLE hMapFile;
static char* pBuf;

bool win32_build_bus(char* busname, int poolsize);
bool win32_load_bus(char* busname);
void win32_release_bus();
void win32_read_bus(int addr, char* data, int size);
void win32_write_bus(int addr, char* data, int size);

#endif