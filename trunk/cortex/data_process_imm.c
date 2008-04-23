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
 *To define the struct to handle the instruction
 *
 */ 
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

/**
 *
 *To define the table for execute for these instructions
 */ 
typedef void (*func)();

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

void opcode_error(){
	printf("opcode error\n");
}

void data_pro_modified_12m(int instruction){
	*((int *)(&dataProModified)) = instruction;
	printf("data_pro_modified_12m: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n", dataProModified.op);
	printf("S: 0x%x \n", dataProModified.s);
	printf("Rn: 0x%x \n", dataProModified.rn);
	printf("Rd: 0x%x \n", dataProModified.rd);
	int imm12=decode_imm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	printf("imm 12: 0x%x \n",imm12);
	int index=0;

	index = dataProModified.op;
//	printf("index : %d", index);

	if((dataProModified.op == 0x8) &&(dataProModified.rd ==0xf)&&(dataProModified.s==0x1 )){
		index = dataProModified.op+0x10;
		printf("entering for op+16");
	}else if((dataProModified.op == 13) &&(dataProModified.rd ==15)&&(dataProModified.s==1 )){
		index = dataProModified.op+16;
	}else if((dataProModified.op == 2) &&(dataProModified.rn ==15)){
		 index = dataProModified.op+16;
	}else if((dataProModified.op == 3) &&(dataProModified.rn ==15)){
		 index = dataProModified.op+16;
	}else if((dataProModified.op == 4) &&(dataProModified.rd ==15)&&(dataProModified.s==1 )){
		index = dataProModified.op+16;
	}else if((dataProModified.op == 0) &&(dataProModified.rd ==15)&&(dataProModified.s==1 )){
		 index = dataProModified.op+16;
	}
	printf("index is %d", index);
	func f_ptr=(void *)data_pro_m[index];
	f_ptr();
}

void data_pro_add_12m(int instruction){
	printf("data_pro_add_12m: 0x%X \n",instruction);
	*((int *)(&dataProAdd)) = instruction;
	int op=(dataProAdd.op<<2)+dataProAdd.op2;
	printf("Operate Code : 0x%x \n", op);
	printf("Rn: 0x%x \n", dataProAdd.rn);
	printf("Rd: 0x%x \n", dataProAdd.op);
	int imm12=decode_imm12(dataProAdd.imm1, dataProAdd.imm3,dataProAdd.imm8);
	printf("imm 12: 0x%x \n",imm12);

}
void data_pro_mov_16m(int instruction){
	printf("data_pro_mov_16m: 0x%X \n",instruction);
	*((int *)(&dataProMov)) = instruction;
	int op = (dataProMov.op<<2)+dataProMov.op2;
	printf("Operate Code : 0x%x \n",op);
	printf("Rn: 0x%x \n", dataProModified.rn);
	printf("Rd: 0x%x \n", dataProMov.op);
	int imm12=decode_imm16(dataProMov.imm1,dataProMov.imm4, dataProMov.imm3,dataProMov.imm8);
	printf("imm 12: 0x%x \n",imm12);

}
void data_pro_bitoperation(int instruction){
	printf("data_pro_bitoperation: 0x%X \n",instruction);
	*((int *)(&dataProBit)) = instruction;
	printf("Operate Code : 0x%x \n", dataProBit.op);
	printf("Rn: 0x%x \n", dataProBit.rn);
	printf("Rd: 0x%x \n", dataProBit.op);
	int imm12=decode_bitOperation(dataProBit.imm3, dataProBit.imm2,dataProBit.imm5);
	printf("imm 12: 0x%x \n",imm12);

}
void data_pro_reserved(int instruction){
	printf("data_pro_reserved: 0x%X \n",instruction);

}
void logical_add(){
	printf("	***logical add\n");	
}



void add_with_carry(){
	printf("	***add with carry\n");	
	printf("********ADC{s}<c><q>	{<Rd>,} <Rn>, #<const>******* \n");
	
	}
void add(){
		printf("	***add\n");	

}
void logical_and(){
		printf("	***logical and\n");	

}
void bit_clear(){
		printf("	***bit_clear\n");	

}
void compare_negative(){
		printf("	***compare_negative\n");	

}
void compare(){
		printf("	***compare\n");	

}
void exclusive_or(){
		printf("	***exclusive or\n");	

}
void move(){
		printf("	***move\n");	

}
void move_negative(){
		printf("	***move negative\n");	

}
void logical_or_not(){
		printf("	***logical or not\n");	

}
void logical_or(){
		printf("	***logical or\n");	

}
void reverse_subtract(){
		printf("	***reverse subtract\n");	

}
void subtract_with_carry(){
		printf("	***subtract with carry \n");	

}
void subtract(){
		printf("	***subtract\n");	

}
void test_equal(){
		printf("	***test equal\n");	

}
void test(){
		printf("	***test\n");	

}


















#endif
