/**
 *
 * This file is to define the function to handle the Data_Processing_Imme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#ifndef _DATAPROCESSIMM
#define _DATAPROCESSIMM
#include <stdio.h>
#include "instruction.h"

/**
 *
 *To define the table for execute for these instructions
 */ 
typedef void (*func)(int);

struct DATAPROMODIFIED{
	unsigned imm8 :8;
	unsigned rd   :4;
	unsigned imm3 :3;
	unsigned pass1:1;
	unsigned rn   :4;
	unsigned s	  :1;
	unsigned op	  :4;
	unsigned pass2:1;
	unsigned imm1 :1;
	unsigned pass3:5;
}dataProModified;

struct DATAPROADD{
	unsigned imm8	:8;
	unsigned rd		:4;
	unsigned imm3	:3;
	unsigned pass1	:1;
	unsigned rn		:4;
	unsigned op2	:2;
	unsigned pass2	:1;
	unsigned op		:1;
	unsigned pass3	:2;
	unsigned imm1	:1;
	unsigned pass4	:5;
}dataProAdd;

struct DATAPROMOV{
	unsigned imm8	:8;
	unsigned rd		:4;
	unsigned imm3	:3;
	unsigned pass1	:1;
	unsigned imm4	:4;
	unsigned op2	:2;
	unsigned pass2	:1;
	unsigned op		:1;
	unsigned pass3	:2;
	unsigned imm1	:1;
	unsigned pass4	:5;

}dataProMov;

struct DATAPROBIT{
	unsigned imm5	:5;
	unsigned pass1	:1;
	unsigned imm2	:2;
	unsigned rd		:4;
	unsigned imm3	:3;
	unsigned pass2	:1;
	unsigned rn		:4;
	unsigned pass3	:1;
	unsigned op		:3;
	unsigned pass4	:8;
}dataProBit;



void* data_pro_m[30]={
	(void *)logical_and,
	(void *)bit_clear,
	(void *)logical_or,
	(void *)logical_or_not,
	(void *)exclusive_or,//4
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,

	(void *)add, //8
	(void *)opcode_error,
	(void *)add_with_carry,//10
	(void *)subtract_with_carry,//11
	(void *)opcode_error,
	(void *)subtract,
	(void *)reverse_subtract,//14
	(void *)opcode_error,
	(void *)test,//16
	(void *)opcode_error,
	(void *)move,//18
	(void *)move_negative,//19
	(void *)test_equal,//20
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,

	(void *)compare_negative,//24
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)compare,//29
	};
#endif