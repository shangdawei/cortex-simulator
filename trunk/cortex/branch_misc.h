/**
 *
 * This file is to define the function to handle the branch, miscellaneous control instructions
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#ifndef _BRANCH_MISC_CTRL
#define _BRANCH_MISC_CTRL
#define DEBUG_I 1
#include <stdio.h>
#include "operators_built-in_func.h"
#include "instruction.h"

/**
 *
 *To define the table for execute for these instructions
 */ 
typedef void (*func)(int);

struct BRANCH{
	unsigned off1	:11;
	unsigned j2		:1;
	unsigned pass1	:1;
	unsigned j1		:1;
	unsigned pass2	:1;
	unsigned pass3	:1;
	unsigned off2	:10;
	unsigned s		:1;
	unsigned pass4	:5;
}branch;

struct BRANCHWITHLINK{
	unsigned off1	:11;
	unsigned j2		:1;
	unsigned pass1	:1;
	unsigned j1		:1;
	unsigned pass2	:1;
	unsigned pass3	:1;
	unsigned off2	:10;
	unsigned s		:1;
	unsigned pass4	:5;
}branchWithLink;

struct CONDITIONALBRANCH{
	unsigned off1	:11;
	unsigned j2		:1;
	unsigned pass1	:1;
	unsigned j1		:1;
	unsigned pass2	:2;
	unsigned off2	:6;
	unsigned cond	:4;
	unsigned s		:1;
	unsigned pass3	:5;
}conditionalBranch;

struct MOVETOSTATUS{
	unsigned sysm	:8;
	unsigned pass1	:4;
	unsigned pass2	:1;
	unsigned pass3	:1;
	unsigned pass4	:2;
	unsigned rn		:4;
	unsigned pass5	:1;
	unsigned pass6	:2;
	unsigned pass7	:3;
	unsigned pass8	:1;
	unsigned pass9	:5;
}moveToStatus;

struct NOOPHINTS{
	unsigned hint	:8;
	unsigned pass1	:3;
	unsigned pass2	:1;
	unsigned pass3	:1;
	unsigned pass4	:1;
	unsigned pass5	:2;
	unsigned pass6	:4;
	unsigned pass7	:1;
	unsigned pass8	:2;
	unsigned pass9	:3;
	unsigned pass10	:1;
	unsigned pass11	:5;
}noOpHints;

struct SPECIALCTRLOP{
	unsigned option	:4;
	unsigned opcode	:4;
	unsigned pass1	:4;
	unsigned pass2	:1;
	unsigned pass3	:1;
	unsigned pass4	:2;
	unsigned pass5	:4;
	unsigned pass6	:1;
	unsigned pass7	:2;
	unsigned pass8	:3;
	unsigned pass9	:1;
	unsigned pass10	:5;
}specialCtrlOp;

struct MOVETOREG{
	unsigned sysm	:8;
	unsigned rd		:4;
	unsigned pass1	:1;
	unsigned pass2	:1;
	unsigned pass3	:2;
	unsigned pass4	:4;
	unsigned pass5	:1;
	unsigned pass6	:2;
	unsigned pass7	:3;
	unsigned pass8	:1;
	unsigned pass9	:5;
}moveToReg;

void* branch_i[1]={
	(void *)b_t4,
};

void* branch_with_l[1]={
	(void *)bl,
};

void* conditional_b[1]={
	(void *) b_t3,
};

void* move_to_s[1]={
	(void *) msr,
};

void* no_op_h[6]={
	(void *) nop,
	(void *) yeild,
	(void *) wfe,
	(void *) wfi,
	(void *) sev,
	(void *) dbg,
};

void* special_ctrl_o[7]={
	(void *) err_branch,
	(void *) err_branch,
	(void *) clrex,			//0010
	(void *) err_branch,
	(void *) dsb,			//0100
	(void *) dmb,			//0101
	(void *) isb,			//0110
};
void* move_to_r[1]={
	(void *) mrs,
};
#endif