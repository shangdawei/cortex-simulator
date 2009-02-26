#include "vbus_interface.h"

bool vb_nread(int vaddr, char* data, int d_size)
{
	return win32_read_bus(vaddr, data, d_size);
}

char vb_read(int addr)
{
	char data;
	win32_read_bus(addr, &data, 1);

	return data;
}

bool vb_nwrite(int vaddr, char* data, int d_size)
{
	return win32_write_bus(vaddr, data, d_size);
}

void vb_write(int addr, char data)
{
	win32_write_bus(addr, &data, 1);
}