#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <windows.h>
#include "../exceptions.h"
#include "../register.h"
#include "../device/common/device.h"
#include "../helper_procedures.h"

bool initalBuffer();
bool eventUpdate();

#define MEMID		"Cortex_M3_Devices_Buffer"
#define PERISIZE	241+256

HANDLE hMemMap;
unsigned char* ibufferr;
unsigned char* ibufferw;

#endif