#include "vbus_procedures.h"

bool loadconfig(char* filename, vbus_descriptor* des)
{
	des->poolsize = 4096;

	return TRUE;
}

bool init_vbus(vbus_descriptor* des)
{
	return win32_build_bus("vbus",des->poolsize);
}

void release_vbus()
{
	win32_release_bus();
}