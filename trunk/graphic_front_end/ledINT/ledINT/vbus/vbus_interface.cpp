#include "stdafx.h"
#include "vbus_interface.h"

void vb_nread(int vaddr, char* data, int d_size)
{
	win32_read_bus(vaddr, data, d_size);
}

char vb_read(int addr)
{
	char data;
	win32_read_bus(addr, &data, 1);

	return data;
}

void vb_nwrite(int vaddr, char* data, int d_size)
{
	win32_write_bus(vaddr, data, d_size);
}

void vb_write(int addr, char data)
{
	win32_write_bus(addr, &data, 1);
}

bool vb_load(char* busname)
{
	return win32_load_bus(busname);
}