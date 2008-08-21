#ifndef THUMB_ADD_SUB_IMM_H_
#define THUMB_ADD_SUB_IMM_H_

typedef void (*func)(short instruction);

struct DATAADDSUBIMM
{
	unsigned short Rd	:3;
	unsigned short Rn	:3;
	unsigned short imm3	:3;
	unsigned short opc	:1;
	unsigned short pass1	:1;
	unsigned short pass2 :2;
	unsigned short pass3 :3;
	
}DataAddSubImm;

void *data_add_sub_imm_process[2]=
{
	(void *)thumb_add_imm,
	(void *)thumb_sub_imm
	
};

#endif /*THUMB_ADD_SUB_IMM_H_*/
