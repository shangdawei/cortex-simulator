#include "vbus_procedures.h"

int main()
{
	vbus_descriptor des;

	des.busname = (char*)malloc(125);
	des.busname = (char*)malloc(25);
	loadconfig("vbus", &des);
	init_vbus(&des);

	release_vbus();
	getchar();

	return 0;
}