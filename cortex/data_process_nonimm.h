/**
 *
 * This file is to define the function to handle the Data_Processing_Imme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#ifndef _DATA_PROCESS_NONIMM
#define _DATA_PROCESS_NONIMM
#include <stdio.h>
#include "instruction.h"

/**
 *
 *To define the table for execute for these instructions
 */ 
typedef void (*func)(int);

struct DATAPROCONSHIFT{
	unsigned rm		:4;
	unsigned type	:2;
	unsigned imm2	:2;
	unsigned rd		:4;
	unsigned imm3	:3;
	unsigned pass1	:1;
	unsigned rn		:4;
	unsigned s		:1;
	unsigned op		:4;
	unsigned pass2	:2;
	unsigned pass3	:5;
}dataProConShift;

struct REGCTRLSHIFT{
	unsigned rm		:4;
	unsigned op2	:3;
	unsigned pass1	:1;
	unsigned rd		:4;
	unsigned pass2	:4;
	unsigned rn		:4;
	unsigned s		:1;
	unsigned op		:2;
	unsigned pass3	:1;
	unsigned pass4	:3;
	unsigned pass5	:5;
}regCtrlShift;

struct SIGNUNSIGNEXTEND{
	unsigned rm		:4;
	unsigned rot	:2;
	unsigned pass1	:1;
	unsigned pass2	:1;
	unsigned rd		:4;
	unsigned pass3	:4;
	unsigned rn		:4;
	unsigned op		:3;
	unsigned pass4	:1;
	unsigned pass5	:3;
	unsigned pass6	:5;
}signUnsignExtend;

struct SIMDADDSUB{
	unsigned rm		:4;
	unsigned prefix	:3;
	unsigned pass1	:1;
	unsigned rd		:4;
	unsigned pass2	:4;
	unsigned rn		:4;
	unsigned op		:3;
	unsigned pass3	:1;
	unsigned pass4	:3;
	unsigned pass5	:5;
}SIMDAddSub;

struct OTHERTHREEREGDATAPRO{
	unsigned rm		:4;
	unsigned op2	:3;
	unsigned pass1	:1;
	unsigned rd		:4;
	unsigned pass2	:4;
	unsigned rn		:4;
	unsigned op		:3;
	unsigned pass3	:1;
	unsigned pass4	:3;
	unsigned pass5	:5;
}otherThreeRegDataPro;

struct BIT32MULTIPLYACC{
	unsigned rm		:4;
	unsigned op2	:4;
	unsigned rd		:4;
	unsigned racc	:4;
	unsigned rn		:4;
	unsigned op		:3;
	unsigned pass1	:4;
	unsigned pass2	:5;
}bit32MultiplyAcc;

struct BITMULTIPLY{
	unsigned rm		:4;
	unsigned op2	:4;
	unsigned rdhi	:4;
	unsigned rdlo	:4;
	unsigned rn		:4;
	unsigned op		:3;
	unsigned pass1	:4;
	unsigned pass2	:5;
}Bit64Multiply;


void* data_pro_con_s[30]={
	(void *)and_reg,//0
	(void *)bic_reg,
	(void *)orr_reg,//2
	(void *)orn_reg,//3
	(void *)eor_reg,//4
	(void *)err_reg,
	(void *)err_reg,
	(void *)err_reg,

	(void *)add_reg, //8
	(void *)err_reg,
	(void *)adc_reg,//10
	(void *)sbc_reg,//11
	(void *)err_reg,
	(void *)sub_reg,
	(void *)rsb_reg,//14
	(void *)err_reg,
	(void *)tst_reg,//16
	(void *)err_reg,
	(void *)mov_reg,//18
	(void *)mvn_reg,//19
	(void *)teq_reg,//20
	(void *)err_reg,
	(void *)err_reg,
	(void *)err_reg,

	(void *)cmn_reg,//24
	(void *)err_reg,
	(void *)err_reg,
	(void *)err_reg,
	(void *)err_reg,
	(void *)cmp_reg,//29
	};
#endif