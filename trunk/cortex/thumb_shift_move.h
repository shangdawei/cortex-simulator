#ifndef THUMB_SHIFT_MOVE_H_
#define THUMB_SHIFT_MOVE_H_

typedef void (*func)(short instruction);

struct DATASHIFTMOVE
{
	unsigned short Rd	:3;
	unsigned short Rm	:3;
	unsigned short imm5	:5;
	unsigned short op	:2;
	unsigned short pass	:3;
	
}DataShiftMove;

void* data_shift_move_process[4]=
{
	(void *)thumb_mov_reg_t2,
	(void *)thumb_lsl_imm5,
	(void *)thumb_lsr_imm5,
	(void *)thumb_asr_imm5
};

#endif /*THUMB_SHIFT_MOVE_*/
