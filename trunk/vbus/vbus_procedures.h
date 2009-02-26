#ifndef __VBUS_PROCEDURES_H__
#define __VBUS_PROCEDURES_H__

#include "vbus_structure.h"
#include "win32/vbus_win32.h"

void updateINT(int INT_ID,char state);
void addINT (int INT_ID);
bool delINT (int INT_ID);

bool loadconfig(char* filename, vbus_descriptor* des);
bool init_vbus(vbus_descriptor* des);

#endif