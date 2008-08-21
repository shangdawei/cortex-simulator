#ifndef THUMB_ADD_SUB_CMP_MOV_IMM8_H_
#define THUMB_ADD_SUB_CMP_MOV_IMM8_H_

#include "instruction.h"

typedef void (*func)(short instruction);

struct DATAADDSUBCMPMOVIMM8
{
	unsigned short imm8	:8;
	unsigned short Rdn	:3;
	unsigned short opc	:2;
	unsigned short pass	:3;
}DataAddSubCmpMovImm8;

void* data_add_sub_cmp_mov_imm8_process[4]=
{
	(void *)thumb_mov_imm8,
	(void *)thumb_cmp_imm8,
	(void *)thumb_add_imm8,
	(void *)thumb_sub_imm8
};

#endif /*THUMB_ADD_SUB_CMP_MOV_IMM8_H_*/
