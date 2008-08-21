#ifndef _THUMBSPECIALDATAPRO
#define _THUMBSPECIALDATAPRO

#include "instruction.h"
typedef void (*func)(short);
//special data processing
//{0xFC00, 0x4400, thumb_sepecial_data_pro}
struct SPEDATAPRO{
	unsigned rdn		:3;
	unsigned rm			:4;
	unsigned dn			:1;
	unsigned op			:2;
	unsigned pass		:6;
}SpecialDataProcessing;

void* special_data_processing[4] = {
	(void*) thumb_add_reg,
	(void*) thumb_cmp_reg,
	(void*) thumb_mov_reg,
	(void*) thumb_branch_exchange_instruction_set,
};

#endif