/**
 *
 * This file is to define the function to handle the Data_Processing_NonImme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#include "data_process_nonimm.h" 
//#include "register.h"
/**
 *
 *To define the struct to handle the instruction
 *
 */ 

void data_pro_con_shift(int instruction)
{
	int shift,index;
	func f_ptr;
	*((int *)(&dataProConShift)) = instruction;
	printf("data_pro_con_shift: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n", dataProConShift.op);
	printf("S: 0x%x \n", dataProConShift.s);
	printf("Rn: 0x%x \n", dataProConShift.rn);
	printf("Rd: 0x%x \n", dataProConShift.rd);
	printf("Rm: 0x%x \n", dataProConShift.rm);
	printf("type: 0x%x \n",dataProConShift.type);
	shift=decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	printf("shift: 0x%x \n",shift);

	index = dataProConShift.op;
//	printf("index : %d", index);

	if((dataProConShift.op == 0x8) &&(dataProConShift.rd ==0xf)&&(dataProConShift.s==0x1 )){
		index = dataProConShift.op+16;
	}else if((dataProConShift.op == 0x0) &&(dataProConShift.rd ==0xf)&&(dataProConShift.s==1 )){
		index = dataProConShift.op+16;
	}else if((dataProConShift.op == 0x2) &&(dataProConShift.rn ==0xf)){
		index = dataProConShift.op+16;
	}else if((dataProConShift.op == 0x3) &&(dataProConShift.rn ==0xf)){
		index = dataProConShift.op+16;
	}else if((dataProConShift.op == 0x4) &&(dataProConShift.rd ==0xf)&&(dataProConShift.s==1 )){
		index = dataProConShift.op+16;
	}else if((dataProConShift.op == 0xd) &&(dataProConShift.rd ==0xf)&&(dataProConShift.s==1 )){
		index = dataProConShift.op+16;
	}
	printf("index is %d", index);
	f_ptr=(void *)data_pro_con_s[index];
	f_ptr(instruction);
}

//void reg_ctrl_shift(int instuction)
//void sign_unsign_extend(int instruction)
//void simd_add_sub(int instruction)
//void other_three_reg_data_pro(int instruction)
//void bit32_multiply_acc(int instruction)
//void bit64_multiply(int instruction)

void err_reg(){
	printf("opcode error\n");
}

void and_reg()
{}

void bic_reg()
{}

void orr_reg(){}
void orn_reg(){}
void eor_reg(){}
void add_reg(){}
void adc_reg(){}
void sbc_reg(){}
void sub_reg(){}
void rsb_reg(){}
void tst_reg(){}
void mov_reg(){}
void mvn_reg(){}
void teq_reg(){}
void cmn_reg(){}
void cmp_reg(){}

/*
void data_pro_modified_12m(int instruction){
	int imm12,index;
	func f_ptr;
	*((int *)(&dataProModified)) = instruction;
	printf("data_pro_modified_12m: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n", dataProModified.op);
	printf("S: 0x%x \n", dataProModified.s);
	printf("Rn: 0x%x \n", dataProModified.rn);
	printf("Rd: 0x%x \n", dataProModified.rd);
	imm12=decode_imm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	printf("imm 12: 0x%x \n",imm12);
	index=0;

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
	f_ptr=(void *)data_pro_m[index];
	f_ptr(instruction);
}

void data_pro_add_12m(int instruction){
	int op,imm12;
	printf("data_pro_add_12m: 0x%X \n",instruction);
	*((int *)(&dataProAdd)) = instruction;
	op=(dataProAdd.op<<2)+dataProAdd.op2;
	printf("Operate Code : 0x%x \n", op);
	printf("Rn: 0x%x \n", dataProAdd.rn);
	printf("Rd: 0x%x \n", dataProAdd.op);
	imm12=decode_imm12(dataProAdd.imm1, dataProAdd.imm3,dataProAdd.imm8);
	printf("imm 12: 0x%x \n",imm12);

}
void data_pro_mov_16m(int instruction){
	int op, imm12;
	printf("data_pro_mov_16m: 0x%X \n",instruction);
	*((int *)(&dataProMov)) = instruction;
	op = (dataProMov.op<<2)+dataProMov.op2;
	printf("Operate Code : 0x%x \n",op);
	printf("Rn: 0x%x \n", dataProModified.rn);
	printf("Rd: 0x%x \n", dataProMov.op);
	imm12=decode_imm16(dataProMov.imm1,dataProMov.imm4, dataProMov.imm3,dataProMov.imm8);
	printf("imm 12: 0x%x \n",imm12);

}
void data_pro_bitoperation(int instruction){
	int imm12;
	printf("data_pro_bitoperation: 0x%X \n",instruction);
	*((int *)(&dataProBit)) = instruction;
	printf("Operate Code : 0x%x \n", dataProBit.op);
	printf("Rn: 0x%x \n", dataProBit.rn);
	printf("Rd: 0x%x \n", dataProBit.op);
	imm12=decode_bitOperation(dataProBit.imm3, dataProBit.imm2,dataProBit.imm5);
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
	int imm,source,result;
	unsigned apsr_c;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);//immediate expand without imm_carry
	//printf(" imm = %X",imm);
    source = get_general_register(dataProModified.rn);//get data from source register
	//printf(" source = %X",source);
	apsr_c = get_flag_c();
	//printf(" apsr_c = %X",apsr_c);
	apsr_c = apsr_c >> 29;
	result = addwithcarry(source,imm,apsr_c);
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
	int imm, result,source;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
    source = get_general_register(dataProModified.rn);
	result = addwithcarry(source,imm,0);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
    source = get_general_register(dataProModified.rn);
	result = source & imm;
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
    source = get_general_register(dataProModified.rn);
	result = source & (~imm);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
    source = get_general_register(dataProModified.rn);
	result = addwithcarry(source,imm,0);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
    source = get_general_register(dataProModified.rn);
	result = addwithcarry(source,~imm,1);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
    source = get_general_register(dataProModified.rn);
	result = source ^ imm;
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
	int imm,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	result = imm;
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
	int imm,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	//printf(" imm = %x",imm);
	result = ~imm;
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	result = source|(~imm);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	result = source|imm;
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	result = addwithcarry(~source,imm,1);
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
	int imm,source,result;
	unsigned apsr_c;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	result = addwithcarry(source,~imm,apsr_c);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	result = addwithcarry(source,~imm,1);
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	result = source ^ imm;
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
	int imm,source,result;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	source = get_general_register(dataProModified.rn);
	result = source & imm;
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
*/