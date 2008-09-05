#ifndef _LOADSTOREDOUBLEEXCLUSIVE
#define _LOADSTOREDOUBLEEXCLUSIVE

#include "instruction.h"

typedef void (*func)(int);

struct LSEXBHTB{
	unsigned rm   :4;
	unsigned op   :4;
	unsigned rt2  :4;
	unsigned rt   :4;
	unsigned rn   :4;
	unsigned l    :1;
	unsigned pass1:1;
	unsigned pass2:1;
	unsigned pass3:1;
	unsigned pass4:1;
	unsigned pass5:2;
	unsigned pass6:5;
}TbB,TbH;

struct LSDOUBLE{
	unsigned imm8 :8;
	unsigned rt2  :4;
	unsigned rt   :4;
	unsigned rn   :4;
	unsigned l    :1;
	unsigned w    :1;
	unsigned pass1:1;
	unsigned u    :1;
	unsigned p    :1;
	unsigned pass2:2;
	unsigned pass3:5;
}LdrD,StrD;

void* ls_ex_bh_tb[7]={
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)tbb,
	(void *)tbh,
	(void *)opcode_error,
};

void* ls_doub[3]={
	(void *)ldrd,
	(void *)strd,
	(void *)opcode_error,
};

#endif