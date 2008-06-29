#ifndef _LOADSTORESINGLEDATA
#define _LOADSTORESINGLEDATA

#include "instruction.h"

typedef void (*func)(int);

struct LSSINGLEPC{
	unsigned imm12 :12;
	unsigned rt    :4;
	unsigned rn    :4;
	unsigned l     :1;
	unsigned size  :2;
	unsigned u     :1;
	unsigned s     :1;
	unsigned pass1 :2;
	unsigned pass2 :5;
}LsSinglePc,LsSingleRnAdd;

struct LSSINGLERN{
	unsigned imm8  :8;
	unsigned pass1 :1;
	unsigned pass2 :1;
	unsigned pass3 :1;
	unsigned pass4 :1;
	unsigned rt    :4;
	unsigned rn    :4;
	unsigned l     :1;
	unsigned size  :2;
	unsigned u     :1;
	unsigned s     :1;
	unsigned pass5 :2;
	unsigned pass6 :5;
}LsSingleRnMinus,LsSingleRnPri,LsSingleRnPost,LsSingleRnPre;

struct LSSINGLERNSHIFT{
	unsigned rm    :4;
	unsigned shift :2;
	unsigned pass1 :5;
	unsigned pass2 :1;
	unsigned rt    :4;
	unsigned rn    :4;
	unsigned l     :1;
	unsigned size  :2;
	unsigned u     :1;
	unsigned s     :1;
	unsigned pass3 :2;
	unsigned pass4 :5;
}LsSingleRnShift;

void* ls_single_pc[6]={
	(void *)ldr_lit,
	(void *)ldrb_lit,
	(void *)ldrsb_lit,
	(void *)ldrh_lit,
	(void *)ldrsh_lit,
	(void *)opcode_error,
};

void* ls_single_rnadd[9]={
	(void *)ldr_imm,
	(void *)ldrb_imm,
	(void *)ldrsb_imm,
	(void *)ldrh_imm,
	(void *)ldrsh_imm,
	(void *)str_imm,
	(void *)strb_imm,
	(void *)strh_imm,
	(void *)opcode_error,
};

void* ls_single_rnminus[9]={
	(void *)ldr_neg_imm,
	(void *)ldrb_neg_imm,
	(void *)ldrsb_neg_imm,
	(void *)ldrh_neg_imm,
	(void *)ldrsh_neg_imm,
	(void *)str_neg_imm,
	(void *)strb_neg_imm,
	(void *)strh_neg_imm,
	(void *)opcode_error,
};

void* ls_single_rnpri[9]={
	(void *)ldrt,
	(void *)ldrbt,
	(void *)ldrsbt,
	(void *)ldrht,
	(void *)ldrsht,
	(void *)strt,
	(void *)strbt,
	(void *)strht,
	(void *)opcode_error,
};

void* ls_single_rnpost[9]={
	(void *)ldr_post,
	(void *)ldrb_post,
	(void *)ldrsb_post,
	(void *)ldrh_post,
	(void *)ldrsh_post,
	(void *)str_post,
	(void *)strb_post,
	(void *)strh_post,
	(void *)opcode_error,
};

void* ls_single_rnpre[9]={
	(void *)ldr_pre,
	(void *)ldrb_pre,
	(void *)ldrsb_pre,
	(void *)ldrh_pre,
	(void *)ldrsh_pre,
	(void *)str_pre,
	(void *)strb_pre,
	(void *)strh_pre,
	(void *)opcode_error,
};

void* ls_single_rnsh[9]={
	(void *)ldr_reg,
	(void *)ldrb_reg,
	(void *)ldrsb_reg,
	(void *)ldrh_reg,
	(void *)ldrsh_reg,
	(void *)str_reg,
	(void *)strb_reg,
	(void *)strh_reg,
	(void *)opcode_error,
};

#endif