#ifndef THUMB_ADD_SUB_REG_H_
#define THUMB_ADD_SUB_REG_H_

typedef void (*func)(short instruction);

struct DATAADDSUBREG
{
	unsigned short Rd	:3;
	unsigned short Rn	:3;
	unsigned short Rm	:3;
	unsigned short opc	:1;
	unsigned short pass1	:1;
	unsigned short pass2 :2;
	unsigned short pass3 :3;
	
}DataAddSubReg;

void *data_add_sub_reg_process[2]=
{
	(void *)thumb_add_reg_t1,
	(void *)thumb_sub_reg
	
};

#endif /*THUMB_ADD_SUB_REG_H_*/
