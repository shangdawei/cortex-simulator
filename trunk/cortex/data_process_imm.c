/**
 *
 * This file is to define the function to handle the Data_Processing_Imme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#ifndef _DATAPROCESSIMM
#define _DATAPROCESSIMM
#include "stdio.h"
#include "instruction.h"
//#include "register.h"
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
typedef void (*func)(int);

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
	f_ptr(instruction);
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


//Add with Carry (immediate) adds an immediate value and the carry flag value to a register value, and writes the result to the destination register. 
void add_with_carry(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);//immediate expand without imm_carry
	//printf(" imm = %X",imm);
   int source = get_general_register(dataProModified.rn);//get data from source register
	//printf(" source = %X",source);
	unsigned apsr_c = get_flag_c();
	//printf(" apsr_c = %X",apsr_c);
	apsr_c = apsr_c >> 29;
	int result = addwithcarry(source,imm,apsr_c);
	set_general_register(dataProModified.rd, result);//send data to destination register
	if(dataProModified.s==1){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)//whether zero
			set_flag_z();
			//printf(" kkkkk ");}
		else
			cle_flag_z();
			//printf(" kkkkk ");}
		if(get_calculate_carry())//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***add with carry\n");	
	printf("********ADC{s}<c><q>	{<Rd>,} <Rn>, #<const>******* \n");

}

//This instruction adds an immediate value to a register value, and writes the result to the destination register.
void add(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = addwithcarry(source,imm,0);
	set_general_register(dataProModified.rd, result);
	if(dataProModified.s==1){
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
			//printf(" kkkkk ");}
		else
			cle_flag_z();
			//printf(" kkkkk ");}
		if(get_calculate_carry())
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())
			set_flag_v();
		else
			cle_flag_v();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***add\n");	

}

//This instruction performs a bitwise AND of a register value and an immediate value, and writes the result to the destination register.
void logical_and(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = source & imm;
	//int a = result & 0x80000000;
	//printf(" a = %x",a);
	set_general_register(dataProModified.rd, result);
	//printf(" a = %x",result);
	if(dataProModified.s==1){
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***logical and\n");	

}

//Bit Clear (immediate) performs a bitwise AND of a register value and the complement of an immediate value, and writes the result to the destination register. 
void bit_clear(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = source & (~imm);
	//int a = result & 0x80000000;
	//printf(" a = %x",a);
	set_general_register(dataProModified.rd, result);
	//printf(" a = %x",result);
	if(dataProModified.s==1){
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***bit_clear\n");	

}

//Compare Negative (immediate) adds a register value and an immediate value. It updates the condition flags based on the result, and discards the result.
void compare_negative(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = addwithcarry(source,imm,0);
	if(result & 0x80000000)
		set_flag_n();
	else
		cle_flag_n();
	if(result==0)
		set_flag_z();
	else
		cle_flag_z();
	if(get_calculate_carry())
		set_flag_c();
	else
		cle_flag_c();
	if(get_calculate_overflow())
		set_flag_v();
	else
		cle_flag_v();
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***compare_negative\n");	

}

//Compare (immediate) subtracts an immediate value from a register value. It updates the condition flags based on the result, and discards the result.
void compare(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = addwithcarry(source,~imm,1);
	if(result & 0x80000000)
		set_flag_n();
	else
		cle_flag_n();
	if(result==0)
		set_flag_z();
	else
		cle_flag_z();
	if(get_calculate_carry())
		set_flag_c();
	else
		cle_flag_c();
	if(get_calculate_overflow())
		set_flag_v();
	else
		cle_flag_v();
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***compare\n");	

}

//Exclusive OR (immediate) performs a bitwise Exclusive OR of a register value and an immediate value, and writes the result to the destination register. 
void exclusive_or(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = source ^ imm;
	//int a = result & 0x80000000;
	//printf(" a = %x",a);
	set_general_register(dataProModified.rd, result);
	//printf(" a = %x",result);
	if(dataProModified.s==1){
		if(result & 0x80000000) //it's a problem.
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***exclusive or\n");	

}

//Move (immediate) writes an immediate value to the destination register. 
void move(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	int result = imm;
	set_general_register(dataProModified.rd, result);
	if(dataProModified.s==1){
		if(result & 0x80000000) //it's a problem.
			set_flag_n();
			//printf(" kkkk");}
		else
			cle_flag_n();
			//printf(" rrrr");}
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***move\n");	

}

//Move Negative (immediate) writes the logical ones complement of an immediate value to the destination register. 
void move_negative(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	//printf(" imm = %x",imm);
	int result = ~imm;
	//int a = result & 0x80000000;
	//printf(" a = %x",a);
	set_general_register(dataProModified.rd, result);
	//printf(" a = %x",result);
	if(dataProModified.s==1){
		if(result & 0x80000000) //it's a problem.
			set_flag_n();
			//printf(" kkkk");}
		else
			cle_flag_n();
			//printf(" kkkk");}
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
   printf("	***move negative\n");	

}

//Logical OR NOT (immediate) performs a bitwise (inclusive) OR of a register value and the complement of an immediate value, and writes the result to the destination register.
void logical_or_not(int i){
   *((int *)(&dataProModified)) = i;
   int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
   int result = source|(~imm);
   set_general_register(dataProModified.rd, result);
   if(dataProModified.s==1)
     {if(result & 0x80000000)
        set_flag_n();
      else
        cle_flag_n();
      if(result==0)
        set_flag_z();
      else
        cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
              }
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***logical or not\n");	

}

//Logical OR (immediate) performs a bitwise (inclusive) OR of a register value and an immediate value, and writes the result to the destination register. 
void logical_or(int i){
   *((int *)(&dataProModified)) = i;
   int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
   int result = source|imm;
   set_general_register(dataProModified.rd, result);
   if(dataProModified.s==1)
     {if(result & 0x80000000)
        set_flag_n();
      else
        cle_flag_n();
      if(result==0)
        set_flag_z();
      else
        cle_flag_z();
		if(get_carry()==0)
			cle_flag_c();
		else
			set_flag_c();
              }
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***logical or\n");	

}

//Reverse Subtract (immediate) subtracts a register value from an immediate value, and writes the result to the destination register. 
void reverse_subtract(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = addwithcarry(~source,imm,1);
	set_general_register(dataProModified.rd, result);
	if(dataProModified.s==1){
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
			//printf(" kkkkk ");}
		else
			cle_flag_z();
			//printf(" kkkkk ");}
		if(get_calculate_carry())
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())
			set_flag_v();
		else
			cle_flag_v();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***reverse subtract\n");	

}

//Subtract with Carry (immediate) subtracts an immediate value and the value of NOT(Carry flag) from a register value, and writes the result to the destination register. 
void subtract_with_carry(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	unsigned apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	int result = addwithcarry(source,~imm,apsr_c);
	set_general_register(dataProModified.rd, result);
	if(dataProModified.s==1){
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())
			set_flag_v();
		else
			cle_flag_v();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***subtract with carry \n");	

}

//This instruction subtracts an immediate value from a register value, and writes the result to the destination register. 
void subtract(int i){
	*((int *)(&dataProModified)) = i;
	int imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
	int result = addwithcarry(source,~imm,1);
	set_general_register(dataProModified.rd, result);
	if(dataProModified.s==1){
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())
			set_flag_v();
		else
			cle_flag_v();
	}
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProModified.rd));
	printf("	***subtract\n");	

}

//Test Equivalence (immediate) performs an exclusive OR operation on a register value and an immediate value. 
void test_equal(int i){
   *((int *)(&dataProModified)) = i;
   int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
   int result = source ^ imm;
   if(result & 0x80000000)
     set_flag_n();
   else
     cle_flag_n();
   if(result==0)
     set_flag_z();
   else
     cle_flag_z();
	if(get_carry()==0)
		cle_flag_c();
	else
		set_flag_c();
   printf(" APSR = %X",get_apsr());
	printf("	***test equal\n");	

}

//Test (immediate) performs a logical AND operation on a register value and an immediate value.
void test(int i){
   *((int *)(&dataProModified)) = i;
   int imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
   int source = get_general_register(dataProModified.rn);
   int result = source & imm;
   if(result & 0x80000000)
     set_flag_n();
   else
     cle_flag_n();
   if(result==0)
     set_flag_z();
   else
     cle_flag_z();
	if(get_carry()==0)
		cle_flag_c();
	else
		set_flag_c();
   printf(" APSR = %X",get_apsr());
	printf("	***test\n");	

}

#endif
