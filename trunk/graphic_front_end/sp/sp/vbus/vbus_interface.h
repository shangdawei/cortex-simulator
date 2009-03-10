#ifndef __VBUS_INTERFACE_H__
#define __VBUS_INTERFACE_H__

#include "win32/vbus_win32.h"

void vb_nread(int vaddr, char * data, int d_size);
char vb_read(int addr);

void vb_nwrite(int vaddr, char* data, int d_size);
void vb_write(int addr, char data);

bool vb_load(char* busname);

#endif