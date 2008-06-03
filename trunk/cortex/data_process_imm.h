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
	(void *)logical_and_imm,
	(void *)bit_clear_imm,
	(void *)logical_or_imm,
	(void *)logical_or_not_imm,
	(void *)exclusive_or_imm,//4
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,

	(void *)add_imm, //8
	(void *)opcode_error,
	(void *)add_with_carry_imm,//10
	(void *)subtract_with_carry_imm,//11
	(void *)opcode_error,
	(void *)subtract_imm,
	(void *)reverse_subtract_imm,//14
	(void *)opcode_error,
	(void *)test_imm,//16
	(void *)opcode_error,
	(void *)move_imm,//18
	(void *)move_negative_imm,//19
	(void *)test_equal_imm,//20
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,

	(void *)compare_negative_imm,//24
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)compare_imm,//29
	};

void* data_pro_p[10]={
	(void *)add_wide_imm,//0
	(void *)opcode_error,
	(void *)address_before_current,//2
	(void *)opcode_error,
	(void *)address_after_current,//4
	(void *)opcode_error,
	(void *)sub_wide_imm,//6
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	};

void* move_p[8]={
	(void *)move_wide_imm,//0
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)move_top_imm,//4
	(void *)opcode_error,
	(void *)opcode_error,
	(void *)opcode_error,
	};

void* bitfield_saturate[8]={
	(void *)signed_lsl,//0
	(void *)signed_asr,//1
	(void *)signed_bit_field_extract,//2
	(void *)bit_field_inset,//3
	(void *)unsigned_lsl,//4
	(void *)unsigned_asr,//5
	(void *)unsinged_bit_field_extract,//6
	(void *)bit_field_clear,//7
	};
#endif
