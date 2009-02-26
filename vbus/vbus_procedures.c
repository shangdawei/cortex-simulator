#include "vbus_procedures.h"

bool loadconfig(char* filename, vbus_descriptor* des)
{
	des->INT_number = 5;
	des->INTsize = 256;
	des->INTstart = 2;
	des->event_addr = 0;
	des->poolsize = 4096;
	des->busname[0] = 'v';
	des->busname[1] = 'b';
	des->busname[2] = 'u';
	des->busname[3] = 's';
	des->busname[4] = '\0';

	return TRUE;
}

bool init_vbus(vbus_descriptor* des)
{
	return win32_build_bus(des->busname,des->poolsize);
}

bool release_vbus()
{
	return win32_release_bus();
}