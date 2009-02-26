#ifndef __VBUS_PROCEDURES_H__
#define __VBUS_PROCEDURES_H__

#include "vbus_structure.h"
#include "win32/vbus_win32.h"

#ifndef __TRUE_FALSE__
#define __TRUE_FALSE__

typedef enum{false=0, true} bool;

#endif

bool loadconfig(char* filename, vbus_descriptor* des);
bool init_vbus(vbus_descriptor* des);
void release_vbus();

#endif