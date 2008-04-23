#ifndef _MISELLANEOUS
#define _MISELLANEOUS
#include "instruction.h"
void error_message(int instruction){
	printf("This instruction can not be decoded 0x%X \n",instruction);
}
void un_finished(int instruction){
	printf("This instruction has not finished 0x%X \n", instruction);
}
#endif
