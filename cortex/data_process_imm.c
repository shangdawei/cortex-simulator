/**
 *
 * This file is to define the function to handle the Data_Processing_Imme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#include "data_process_imm.h" 
//#include "register.h"
/**
 *
 *To define the struct to handle the instruction
 *
 */ 


void opcode_error(){
	printf("	opcode error\n");
}

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

	index = dataProModified.op;
//	printf("index : %d", index);

	if((dataProModified.op == 0x8) &&(dataProModified.rd ==0xf)&&(dataProModified.s==0x1 )){
		index = dataProModified.op+16;
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
	int op,imm12,index;
	func f_ptr;
	printf("data_pro_add_12m: 0x%X \n",instruction);
	*((int *)(&dataProAdd)) = instruction;
	op=(dataProAdd.op<<2)+dataProAdd.op2;
	printf("Operate Code : 0x%x \n", op);
	printf("Rn: 0x%x \n", dataProAdd.rn);
	printf("Rd: 0x%x \n", dataProAdd.rd);
	imm12=decode_imm12(dataProAdd.imm1, dataProAdd.imm3,dataProAdd.imm8);
	printf("imm 12: 0x%x \n",imm12);
	index = op;
	if((op == 0) && (dataProAdd.rn == 15)){
		index = op + 4;
	}else if((op == 6) && (dataProAdd.rn == 15)){
		index = op - 4;
	}
	printf("index is %d", index);
	f_ptr=(void *)data_pro_p[index];
	f_ptr(instruction);
}

void data_pro_mov_16m(int instruction){
	int op, imm16,index;
	func f_ptr;
	printf("data_pro_mov_16m: 0x%X \n",instruction);
	*((int *)(&dataProMov)) = instruction;
	op = (dataProMov.op<<2)+dataProMov.op2;
	printf("Operate Code : 0x%x \n",op);
	printf("Rd: 0x%x \n", dataProMov.rd);
	imm16=decode_imm16(dataProMov.imm1,dataProMov.imm4, dataProMov.imm3,dataProMov.imm8);
	printf("imm 16: 0x%x \n",imm16);
	index = op;
	printf("index is %d", index);
	f_ptr=(void *)move_p[index];
	f_ptr(instruction);
}

void data_pro_bitoperation(int instruction){
	int imm12,index;
	func f_ptr;
	printf("data_pro_bitoperation: 0x%X \n",instruction);
	*((int *)(&dataProBit)) = instruction;
	printf("Operate Code : 0x%x \n", dataProBit.op);
	printf("Rn: 0x%x \n", dataProBit.rn);
	printf("Rd: 0x%x \n", dataProBit.op);
	imm12=decode_bitOperation(dataProBit.imm3, dataProBit.imm2,dataProBit.imm5);
	printf("imm 12: 0x%x \n",imm12);
	index = dataProBit.op;
	if((dataProBit.op == 3) && (dataProBit.rn == 15))
		index = dataProBit.op + 4;
	printf("index is %d", index);
	f_ptr=(void *)bitfield_saturate[index];
	f_ptr(instruction);	
}

void data_pro_reserved(int instruction){
	printf("data_pro_reserved: 0x%X \n",instruction);

}


//Add with Carry (immediate) adds an immediate value and the carry flag value to a register value, and writes the result to the destination register. 
void add_with_carry_imm(int i){
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
void add_imm(int i){
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
void logical_and_imm(int i){
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
void bit_clear_imm(int i){
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
void compare_negative_imm(int i){
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
void compare_imm(int i){
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
void exclusive_or_imm(int i){
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
void move_imm(int i){
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
void move_negative_imm(int i){
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
void logical_or_not_imm(int i){
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
void logical_or_imm(int i){
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
void reverse_subtract_imm(int i){
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
void subtract_with_carry_imm(int i){
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
void subtract_imm(int i){
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
void test_equal_imm(int i){
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
void test_imm(int i){
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

//This instruction adds an immediate value to a register value, and writes the result to the destination register.
void add_wide_imm(int i){
	int imm,source,result;
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	source = get_general_register(dataProAdd.rn);
	result = addwithcarry(source,imm,0);
	set_general_register(dataProAdd.rd, result);
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProAdd.rd));
	printf("	***add_wide\n");

}

//This instruction subtracts an immediate value from a register value, and writes the result to the destination register.
void sub_wide_imm(int i){
	int imm,source,result;
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	source = get_general_register(dataProAdd.rn);
	result = addwithcarry(source,~imm,1);
	set_general_register(dataProAdd.rd, result);
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProAdd.rd));
	printf("	***subtract_wide\n");

}

//Address to Register adds an immediate value to the PC value, and writes the result to the destination register.
void address_before_current(int i){
	int imm,result,pc,base;
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	pc = get_pc();
	base = align(pc,4);
	result = base - imm;
	set_general_register(dataProAdd.rd, result);
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProAdd.rd));	
	printf("	***address_before_ins\n");

}

//Address to Register adds an immediate value to the PC value, and writes the result to the destination register.
void address_after_current(int i){
	int imm,result,pc,base;
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	pc = get_pc();
	base = align(pc,4);
	result = base + imm;
	set_general_register(dataProAdd.rd, result);
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProAdd.rd));
	printf("	***address_after_ins\n");

}

//Move Top writes an immediate value to the top halfword of the destination register. 
void move_top_imm(int i){
	int imm,result;
	*((int *)(&dataProMov)) = i;
	imm = decode_imm16(dataProMov.imm1,dataProMov.imm4,dataProMov.imm3,dataProMov.imm8);
	result = get_general_register(dataProMov.rd);
	imm = imm << 16;
	result = result & 0x0000FFFF;
	result = result | imm;
	set_general_register(dataProMov.rd, result);
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProMov.rd));	
	printf("	***move_top\n");

}

//Move (immediate) writes an immediate value to the destination register. 
void move_wide_imm(int i){
	int imm,result;
	*((int *)(&dataProMov)) = i;
	imm = decode_imm16(dataProMov.imm1,dataProMov.imm4,dataProMov.imm3,dataProMov.imm8);
	result = imm;
	set_general_register(dataProMov.rd, result);
   printf(" APSR = %X",get_apsr());
   printf(" rd = %X",get_general_register(dataProMov.rd));	
	printf("	***move_wide\n");

}

//Bit Field Clear clears any number of adjacent bits at any position in a register, without affecting the other bits in the register.
void bit_field_clear(int i){
	int msbit,lsbit,result,j,m,n,temp;
	*((int *)(&dataProBit)) = i;
	msbit = dataProBit.imm5;
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	if(msbit >= lsbit){
		m = 0xFFFFFFFF;
		for(j = msbit;j > 0;j--)
			m = m << 1;
		n = 1;
		for(j = lsbit;j > 0;j--){
			n = n << 1;
			n = n + 1;
		}
		temp = m | n;
	result = get_general_register(dataProBit.rd);
	result = result & temp;
	set_general_register(dataProBit.rd, result);
	printf(" APSR = %X",get_apsr());
	printf(" rd = %X",get_general_register(dataProBit.rd));
	}
	else
		printf(" it is unpredictable!\n");
	printf("	***bit_field_clear\n");

}

//Bit Field Insert copies any number of low order bits from a register into the same number of adjacent bits at any position in the destination register.
void bit_field_inset(int i){
	int msbit,lsbit,source,result,j,m,n,p,temp;
	*((int *)(&dataProBit)) = i;
	msbit = dataProBit.imm5;
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	if(msbit >= lsbit){
		m = 1;
		for(j = msbit-lsbit;j > 0;j--){
			m = m << 1;
			m = m +1;
		}
		source = get_general_register(dataProBit.rn);
		source = source & n;
		p = 0xFFFFFFFF;
		for(j = msbit;j > 0;j--)
			p = p << 1;
		n = 1;
		for(j = lsbit;j > 0;j--){
			n = n << 1;
			n = n + 1;
		}
		temp = p | n;
	result = get_general_register(dataProBit.rd);
	result = result & temp;
	result = result | source;
	set_general_register(dataProBit.rd, result);
	printf(" APSR = %X",get_apsr());
	printf(" rd = %X",get_general_register(dataProBit.rd));
	}
	else
		printf(" it is unpredictable!\n");
	printf("	***bit_field_cinset\n");

}

//Signed Bit Field Extract extracts any number of adjacent bits at any position from one register, sign extends them to 32 bits, and writes the result to the destination register.
void signed_bit_field_extract(int i){
	int msbit,lsbit,widthminus1,source,result,j,m,n,temp,p,q;
	*((int *)(&dataProBit)) = i;
	widthminus1 = dataProBit.imm5;
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	msbit = lsbit + widthminus1;
	if(msbit <= 31){
		m = 0xFFFFFFFF;
		for(j = msbit;j > 0;j--)
			m = m << 1;
		n = 1;
		for(j = lsbit;j > 0;j--){
			n = n << 1;
			n = n + 1;
		}
		temp = m | n;
		source = get_general_register(dataProBit.rn);
		source = source & (~temp);
		p = source;
		for(j = msbit;j <= 31;j++)
			p = p << 1;
		if(p & 0x80000000){
			q = 0xFFFFFFFF;
			for(j = 0;j <= msbit;j++)
				q = q << 1;
			source = source | q;
			for(j = lsbit;j > 0;j--)
				source = source >> 1;
		}
		else{
			for(j = lsbit;j > 0;j--)
				source = source >> 1;
		}
		result = source;
		set_general_register(dataProBit.rd, result);
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProBit.rd));
	}
	else
		printf(" it is unpredictable!\n");
	printf("	***signed_bit_field_extract\n");

}

//Signed Saturate saturates an optionally-shifted signed value to a selectable signed range.
void signed_lsl(int i){
	int imm,source,result,shift_n,operand;
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
	saturate_to = dataProBit.imm5 + 1;
	source = get_general_register(dataProBit.rn);
	shift_n = decodeImmShift(0,imm);
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	operand = shift(source,get_shift_t(),shift_n,apsr_c);
	result = signedSatQ(operand,saturate_to);
	set_general_register(dataProBit.rd, result);//it exsit a problem.
	if(get_sat())
		set_flag_q();
	printf(" APSR = %X",get_apsr());
	printf(" rd = %X",get_general_register(dataProBit.rd));
	printf("	***signed_lsl\n");

}

//Signed Saturate saturates an optionally-shifted signed value to a selectable signed range.
void signed_asr(int i){
	int imm,source,result,shift_n,operand;
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
	if(imm == 0)
		printf(" it is unpredictable!\n");
	else{
		saturate_to = dataProBit.imm5 + 1;
		source = get_general_register(dataProBit.rn);
		shift_n = decodeImmShift(2,imm);
		apsr_c = get_flag_c();
		apsr_c = apsr_c >> 29;
		operand = shift(source,get_shift_t(),shift_n,apsr_c);
		result = signedSatQ(operand,saturate_to);
		set_general_register(dataProBit.rd, result);//it exsit a problem.
		if(get_sat())
			set_flag_q();
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProBit.rd));
	}
	printf("	***signed_asr\n");

}

//Unsigned Bit Field Extract extracts any number of adjacent bits at any position from one register, zero extends them to 32 bits, and writes the result to the destination register.
void unsinged_bit_field_extract(int i){
	int lsbit,msbit,source,result,widthminus1,m,n,j,temp;
	*((int *)(&dataProBit)) = i;
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	widthminus1 = dataProBit.imm5;
	msbit = lsbit + widthminus1;
	if(msbit <= 31){
		m = 0xFFFFFFFF;
		for(j = msbit;j > 0;j--)
			m = m << 1;
		n = 1;
		for(j = lsbit;j > 0;j--){
			n = n << 1;
			n = n + 1;
		}
		temp = m | n;
		source = get_general_register(dataProBit.rn);
		source = source & (~temp);
		for(j = lsbit;j > 0;j--)
			source = source >> 1;
		result = source;
		set_general_register(dataProBit.rd, result);
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProBit.rd));
	}
	else
		printf(" it is unpredictable!\n");
	printf("	***unsinged_bit_field_extract\n");

}

//Unsigned Saturate saturates an optionally-shifted signed value to a selected unsigned range.
void unsigned_lsl(int i){
	int imm,source,result,shift_n,operand;
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
	saturate_to = dataProBit.imm5;
	source = get_general_register(dataProBit.rn);
	shift_n = decodeImmShift(0,imm);
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	operand = shift(source,get_shift_t(),shift_n,apsr_c);
	result = unsignedSatQ(operand,saturate_to);
	set_general_register(dataProBit.rd, result);
	if(get_sat())
		set_flag_q();
	printf(" APSR = %X",get_apsr());
	printf(" rd = %X",get_general_register(dataProBit.rd));
	printf("	***unsigned_lsl\n");

}

//Unsigned Saturate saturates an optionally-shifted signed value to a selected unsigned range.
void unsigned_asr(int i){
	int imm,source,result,shift_n,operand;
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
	if(imm == 0)
		printf(" it is unpredictable!\n");
	else{
		saturate_to = dataProBit.imm5;
		source = get_general_register(dataProBit.rn);
		shift_n = decodeImmShift(2,imm);
		apsr_c = get_flag_c();
		apsr_c = apsr_c >> 29;
		operand = shift(source,get_shift_t(),shift_n,apsr_c);
		result = unsignedSatQ(operand,saturate_to);
		set_general_register(dataProBit.rd, result);
		if(get_sat())
			set_flag_q();
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProBit.rd));
	}
	printf("	***unsigned_asr\n");

}
