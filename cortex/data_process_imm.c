/**
 *
 * This file is to define the function to handle the Data_Processing_Imme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#include "data_process_imm.h" 
#include "instruction.h"
/**
 *
 *To define the struct to handle the instruction
 *
 */ 


void opcode_error(int i){
	printf("	The instruction: 0x%x is error in this situation. \n",i);
}

void data_pro_modified_12m(int instruction){
	int imm12,index;
	func f_ptr;
	*((int *)(&dataProModified)) = instruction;
#if DEBUG
	printf("data_pro_modified_12m: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n", dataProModified.op);
	printf("S: 0x%x \n", dataProModified.s);
	printf("Rn: 0x%x \n", dataProModified.rn);
	printf("Rd: 0x%x \n", dataProModified.rd);
#endif
	imm12=decode_imm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
#if DEBUG
	printf("imm 12: 0x%x \n",imm12);
#endif

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
#if DEBUG
	printf("index is %d", index);
#endif
	f_ptr=(void *)data_pro_m[index];
	f_ptr(instruction);
}

void data_pro_add_12m(int instruction){
	int op,imm12,index;
	func f_ptr;
#if DEBUG
	printf("data_pro_add_12m: 0x%X \n",instruction);
#endif
	*((int *)(&dataProAdd)) = instruction;
	op=(dataProAdd.op<<2)+dataProAdd.op2;
#if DEBUG
	printf("Operate Code : 0x%x \n", op);
	printf("Rn: 0x%x \n", dataProAdd.rn);
	printf("Rd: 0x%x \n", dataProAdd.rd);
#endif
	imm12=decode_imm12(dataProAdd.imm1, dataProAdd.imm3,dataProAdd.imm8);
#if DEBUG
	printf("imm 12: 0x%x \n",imm12);
#endif
	index = op;
	if((op == 0) && (dataProAdd.rn == 15)){
		index = op + 4;
	}else if((op == 6) && (dataProAdd.rn == 15)){
		index = op - 4;
	}
#if DEBUG
	printf("index is %d", index);
#endif
	f_ptr=(void *)data_pro_p[index];
	f_ptr(instruction);
}

void data_pro_mov_16m(int instruction){
	int op, imm16,index;
	func f_ptr;
	//printf("data_pro_mov_16m: 0x%X \n",instruction);
	*((int *)(&dataProMov)) = instruction;
	op = (dataProMov.op<<2)+dataProMov.op2;
	//printf("Operate Code : 0x%x \n",op);
	//printf("Rd: 0x%x \n", dataProMov.rd);
	imm16=decode_imm16(dataProMov.imm1,dataProMov.imm4, dataProMov.imm3,dataProMov.imm8);
	//printf("imm 16: 0x%x \n",imm16);
	index = op;
	//printf("index is %d", index);
	f_ptr=(void *)move_p[index];
	f_ptr(instruction);
}

void data_pro_bitoperation(int instruction){
	int index;
	func f_ptr;
	//printf("data_pro_bitoperation: 0x%X \n",instruction);
	*((int *)(&dataProBit)) = instruction;
	//printf("Operate Code : 0x%x \n", dataProBit.op);
	//printf("Rn: 0x%x \n", dataProBit.rn);
	//printf("Rd: 0x%x \n", dataProBit.rd);
	//imm12=decode_bitOperation(dataProBit.imm3, dataProBit.imm2,dataProBit.imm5);
	//printf("imm 12: 0x%x \n",imm12);
	index = dataProBit.op;
	if((dataProBit.op == 3) && (dataProBit.rn == 15))
		index = dataProBit.op + 4;
	//printf("index is %d", index);
	f_ptr=(void *)bitfield_saturate[index];
	f_ptr(instruction);	
}

void data_pro_reserved(int instruction){
	//printf("data_pro_reserved: 0x%X \n",instruction);

}


//Add with Carry (immediate) adds an immediate value and the carry flag value to a register value, and writes the result to the destination register. 
void add_with_carry_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	unsigned apsr_c;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);//immediate expand without imm_carry
	if(Bad_Reg(dataProModified.rd) || Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);//get data from source register
		apsr_c = get_flag_c();
		apsr_c = apsr_c >> 29;
		addwithcarry(source,imm,apsr_c, result);
		set_general_register(dataProModified.rd, result->result);//send data to destination register
		if(dataProModified.s==1){
			if(result->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(result->result == 0)//whether zero
				set_flag_z();
				//printf(" kkkkk ");}
			else
				cle_flag_z();
				//printf(" kkkkk ");}
			if(result->carry_out)//whether carry
				set_flag_c();
			else
				cle_flag_c();
			if(result->overflow)//whether overflow
				set_flag_v();
			else
				cle_flag_v();
		}
#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***add with carry\n");	
		printf("********ADC{s}<c><q>	{<Rd>,} <Rn>, #<const>******* \n");
#endif
	}
	free(result);
}

//This instruction adds an immediate value to a register value, and writes the result to the destination register.
void add_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	if(Bad_Reg(dataProModified.rd) || dataProModified.rn == 15)
		printf("	it is unpredictable!");
	else{	
		source = get_general_register(dataProModified.rn);
		addwithcarry(source,imm,0, result);
		set_general_register(dataProModified.rd, result->result);
		if(dataProModified.s==1){
			if(result->result & 0x80000000)
				set_flag_n();
			else
				cle_flag_n();
			if(result->result == 0)
				set_flag_z();
				//printf(" kkkkk ");}
			else
				cle_flag_z();
				//printf(" kkkkk ");}
			if(result->carry_out)
				set_flag_c();
			else
				cle_flag_c();
			if(result->overflow)
				set_flag_v();
			else
				cle_flag_v();
		}
	#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***add\n");
#endif
	}
	free(result);
}

//This instruction performs a bitwise AND of a register value and an immediate value, and writes the result to the destination register.
void logical_and_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd) || Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source & imm->result;
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
	#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***logical and\n");
#endif
	}
	free(imm);
}

//Bit Clear (immediate) performs a bitwise AND of a register value and the complement of an immediate value, and writes the result to the destination register. 
void bit_clear_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd) || Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source & (~imm->result);
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***bit_clear\n");
#endif
	}
	free(imm);
}

//Compare Negative (immediate) adds a register value and an immediate value. It updates the condition flags based on the result, and discards the result.
void compare_negative_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	if(dataProModified.rn == 15)
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		addwithcarry(source,imm,0, result);
		if(result->result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result->result == 0)
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)
			set_flag_v();
		else
			cle_flag_v();
		//printf(" APSR = %X",get_apsr());
		//printf(" rd = %X",get_general_register(dataProModified.rd));
		//printf("	***compare_negative\n");
	}
	free(result);
}

//Compare (immediate) subtracts an immediate value from a register value. It updates the condition flags based on the result, and discards the result.
void compare_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	if(dataProModified.rn == 15)
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		addwithcarry(source,~imm,1, result);
		if(result->result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result->result == 0)
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)
			set_flag_v();
		else
			cle_flag_v();
		//printf(" APSR = %X",get_apsr());
		//printf(" rd = %X",get_general_register(dataProModified.rd));
		//printf("	***compare\n");
	}
	free(result);
}

//Exclusive OR (immediate) performs a bitwise Exclusive OR of a register value and an immediate value, and writes the result to the destination register. 
void exclusive_or_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd) || Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source ^ imm->result;
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
	}
	free(imm);
}

//Move (immediate) writes an immediate value to the destination register. 
void move_imm(int i){
	int result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd))
		printf("	it is unpredictable!");
	else{
		result = imm->result;
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
	}
	free(imm);
}

//Move Negative (immediate) writes the logical ones complement of an immediate value to the destination register. 
void move_negative_imm(int i){
	int result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd))
		printf("	it is unpredictable!");
	else{
		//printf(" imm = %x",imm);
		result = ~imm->result;
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***move negative\n");
#endif
	}
	free(imm);
}

//Logical OR NOT (immediate) performs a bitwise (inclusive) OR of a register value and the complement of an immediate value, and writes the result to the destination register.
void logical_or_not_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd) || dataProModified.rn == 13)
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source|(~imm->result);
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***logical or not\n");
#endif
	}
	free(imm);
}

//Logical OR (immediate) performs a bitwise (inclusive) OR of a register value and an immediate value, and writes the result to the destination register. 
void logical_or_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rd) || dataProModified.rn == 13)
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source | imm->result;
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
			if(imm->carry)
				cle_flag_c();
			else
				set_flag_c();
		}
	#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***logical or\n");
#endif
	}
	free(imm);
}

//Reverse Subtract (immediate) subtracts a register value from an immediate value, and writes the result to the destination register. 
void reverse_subtract_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	if(Bad_Reg(dataProModified.rd) || Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		addwithcarry(~source,imm,1, result);
		set_general_register(dataProModified.rd, result->result);
		if(dataProModified.s==1){
			if(result->result & 0x80000000)
				set_flag_n();
			else
				cle_flag_n();
			if(result->result == 0)
				set_flag_z();
				//printf(" kkkkk ");}
			else
				cle_flag_z();
				//printf(" kkkkk ");}
			if(result->carry_out)
				set_flag_c();
			else
				cle_flag_c();
			if(result->overflow)
				set_flag_v();
			else
				cle_flag_v();
		}
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***reverse subtract\n");
#endif
	}
	free(result);
}

//Subtract with Carry (immediate) subtracts an immediate value and the value of NOT(Carry flag) from a register value, and writes the result to the destination register. 
void subtract_with_carry_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	unsigned apsr_c;
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	if(Bad_Reg(dataProModified.rd) || Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		apsr_c = get_flag_c();
		apsr_c = apsr_c >> 29;
		addwithcarry(source,~imm,apsr_c, result);
		set_general_register(dataProModified.rd, result->result);
		if(dataProModified.s==1){
			if(result->result & 0x80000000)
				set_flag_n();
			else
				cle_flag_n();
			if(result->result == 0)
				set_flag_z();
			else
				cle_flag_z();
			if(result->carry_out)
				set_flag_c();
			else
				cle_flag_c();
			if(result->overflow)
				set_flag_v();
			else
				cle_flag_v();
		}
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***subtract with carry \n");
#endif
	}
	free(result);
}

//This instruction subtracts an immediate value from a register value, and writes the result to the destination register. 
void subtract_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProModified)) = i;
	imm = ThumbExpandImm12(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8);
	if(Bad_Reg(dataProModified.rd) || dataProModified.rn == 15)
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		addwithcarry(source,~imm,1, result);
		set_general_register(dataProModified.rd, result->result);
		if(dataProModified.s==1){
			if(result->result & 0x80000000)
				set_flag_n();
			else
				cle_flag_n();
			if(result->result == 0)
				set_flag_z();
			else
				cle_flag_z();
			if(result->carry_out)
				set_flag_c();
			else
				cle_flag_c();
			if(result->overflow)
				set_flag_v();
			else
				cle_flag_v();
		}
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProModified.rd));
		printf("	***subtract\n");
#endif
	}
	free(result);
}

//Test Equivalence (immediate) performs an exclusive OR operation on a register value and an immediate value. 
void test_equal_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source ^ imm->result;
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(imm->carry)
			cle_flag_c();
		else
			set_flag_c();
		//printf(" APSR = %X",get_apsr());
		//printf("	***test equal\n");	
	}
	free(imm);
}

//Test (immediate) performs a logical AND operation on a register value and an immediate value.
void test_imm(int i){
	int source,result;
	struct RESULTCARRY *imm = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProModified)) = i;
	ThumbExpandImm12WithC(dataProModified.imm1, dataProModified.imm3,dataProModified.imm8,imm);
	if(Bad_Reg(dataProModified.rn))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProModified.rn);
		result = source & imm->result;
		if(result & 0x80000000)
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)
			set_flag_z();
		else
			cle_flag_z();
		if(imm->carry)
			cle_flag_c();
		else
			set_flag_c();
		//printf(" APSR = %X",get_apsr());
		//printf("	***test\n");
	}
	free(imm);
}

//This instruction adds an immediate value to a register value, and writes the result to the destination register.
void add_wide_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	if(Bad_Reg(dataProAdd.rd))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProAdd.rn);
		addwithcarry(source,imm,0, result);
		set_general_register(dataProAdd.rd, result->result);
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProAdd.rd));
		printf("	***add_wide\n");
#endif
	}
	free(result);
}

//This instruction subtracts an immediate value from a register value, and writes the result to the destination register.
void sub_wide_imm(int i){
	int imm,source;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	if(Bad_Reg(dataProAdd.rd))
		printf("	it is unpredictable!");
	else{
		source = get_general_register(dataProAdd.rn);
		addwithcarry(source,~imm,1, result);
		set_general_register(dataProAdd.rd, result->result);
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProAdd.rd));
		printf("	***subtract_wide\n");
#endif
	}
	free(result);
}

//Address to Register adds an immediate value to the PC value, and writes the result to the destination register.
void address_before_current(int i){
	int imm,result,pc,base;
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	if(Bad_Reg(dataProAdd.rd))
		printf("	it is unpredictable!");
	else{
		pc = get_pc();
		base = align(pc,4);
		result = base - imm;
		set_general_register(dataProAdd.rd, result);
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProAdd.rd));	
		printf("	***address_before_ins\n");
#endif
	}
}

//Address to Register adds an immediate value to the PC value, and writes the result to the destination register.
void address_after_current(int i){
	int imm,result,pc,base;
	*((int *)(&dataProAdd)) = i;
	imm = decode_imm12(dataProAdd.imm1,dataProAdd.imm3,dataProAdd.imm8);
	if(Bad_Reg(dataProAdd.rd))
		printf("	it is unpredictable!");
	else{
		pc = get_pc();
		base = align(pc,4);
		result = base + imm;
		set_general_register(dataProAdd.rd, result);
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProAdd.rd));
		printf("	***address_after_ins\n");
#endif
	}
}

//Move Top writes an immediate value to the top halfword of the destination register. 
void move_top_imm(int i){
	int imm,result;
	*((int *)(&dataProMov)) = i;
	imm = decode_imm16(dataProMov.imm1,dataProMov.imm4,dataProMov.imm3,dataProMov.imm8);
	if(Bad_Reg(dataProMov.rd))
		printf("	it is unpredictable!");
	else{
		result = get_general_register(dataProMov.rd);
		imm = imm << 16;
		result = result & 0x0000FFFF;
		result = result | imm;
		set_general_register(dataProMov.rd, result);
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProMov.rd));	
		printf("	***move_top\n");
#endif
	}
}

//Move (immediate) writes an immediate value to the destination register. 
void move_wide_imm(int i){
	int imm,result;
	*((int *)(&dataProMov)) = i;
	imm = decode_imm16(dataProMov.imm1,dataProMov.imm4,dataProMov.imm3,dataProMov.imm8);
	if(Bad_Reg(dataProMov.rd))
		printf("	it is unpredictable!");
	else{
		result = imm;
		set_general_register(dataProMov.rd, result);
		#if DEBUG
		printf(" APSR = %X",get_apsr());
		printf(" rd = %X",get_general_register(dataProMov.rd));	
		printf("	***move_wide\n");
#endif
	}
}

//Bit Field Clear clears any number of adjacent bits at any position in a register, without affecting the other bits in the register.
void bit_field_clear(int i){
	int msbit,lsbit,result,j,m,n,temp;
	*((int *)(&dataProBit)) = i;
	msbit = dataProBit.imm5;
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	if(Bad_Reg(dataProBit.rd))
		printf("	it is unpredictable!");
	else{
		if(msbit >= lsbit){
			m = 0xFFFFFFFF;
			for(j = msbit;j >= 0;j--)
				m = m << 1;
			//printf(" m = %x",m);
			n = 1;
			for(j = lsbit;j > 1;j--){
				n = n << 1;
				n = n + 1;
			}
			//printf(" n = %x",n);
			temp = m | n;
			//printf(" temp = %x",temp);
			result = get_general_register(dataProBit.rd);
			result = result & temp;
			set_general_register(dataProBit.rd, result);
			//printf(" APSR = %X",get_apsr());
			//printf(" rd = %X",get_general_register(dataProBit.rd));
		}
		else
			printf(" it is unpredictable!\n");
		//printf("	***bit_field_clear\n");
	}
}

//Bit Field Insert copies any number of low order bits from a register into the same number of adjacent bits at any position in the destination register.
void bit_field_inset(int i){
	int msbit,lsbit,source,result,j,m,n,p,temp;
	*((int *)(&dataProBit)) = i;
	msbit = dataProBit.imm5;
	//printf(" msbit = %d",msbit);
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	//printf(" lsbit = %d",lsbit);
	if(Bad_Reg(dataProBit.rd) || dataProBit.rn == 13)
		printf("	it is unpredictable!");
	else{
		if(msbit >= lsbit){
			m = 1;
			for(j = msbit-lsbit;j > 0;j--){
				m = m << 1;
				m = m +1;
			}
			//printf(" m = %X",m);
			source = get_general_register(dataProBit.rn);
			source = source & m;
			//printf(" source = %X",source);
			source = source << lsbit;
			//printf(" source = %X",source);
			p = 0xFFFFFFFF;
			for(j = msbit;j >= 0;j--)
				p = p << 1;
			n = 1;
			for(j = lsbit;j > 1;j--){
				n = n << 1;
				n = n + 1;
			}
			temp = p | n;
			//printf(" temp = %X",temp);
			result = get_general_register(dataProBit.rd);
			result = result & temp;
			//printf(" result = %X",result);
			result = result | source;
			set_general_register(dataProBit.rd, result);
			//printf(" APSR = %X",get_apsr());
			//printf(" rd = %X",get_general_register(dataProBit.rd));
		}
		else
			printf(" it is unpredictable!\n");
		//printf("	***bit_field_inset\n");
	}
}

//Signed Bit Field Extract extracts any number of adjacent bits at any position from one register, sign extends them to 32 bits, and writes the result to the destination register.
void signed_bit_field_extract(int i){
	int msbit,lsbit,widthminus1,source,result,j,m,n,temp,p,q;
	*((int *)(&dataProBit)) = i;
	widthminus1 = dataProBit.imm5;
	lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
	msbit = lsbit + widthminus1;
	//printf(" msbit = %d",msbit);
	if(Bad_Reg(dataProBit.rd) || Bad_Reg(dataProBit.rn))
		printf("	it is unpredictable!");
	else{
		if(msbit <= 31){
			m = 0xFFFFFFFF;
			for(j = msbit;j >= 0;j--)
				m = m << 1;
			n = 1;
			for(j = lsbit;j > 1;j--){
				n = n << 1;
				n = n + 1;
			}
			temp = m | n;
			//printf(" temp = %X",temp);
			source = get_general_register(dataProBit.rn);
			source = source & (~temp);
			//printf(" source = %X",source);
			p = source;
			for(j = msbit;j < 31;j++)
				p = p << 1;
			//printf(" p = %X",p);
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
			//printf(" APSR = %X",get_apsr());
			//printf(" rd = %X",get_general_register(dataProBit.rd));
		}
		else
			printf(" it is unpredictable!\n");
		//printf("	***signed_bit_field_extract\n");
	}
}

//Signed Saturate saturates an optionally-shifted signed value to a selectable signed range.
void signed_lsl(int i){
	int imm,source,operand;
	struct RESULTCARRY *shift_tn = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	struct RESULTCARRY *result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	if(Bad_Reg(dataProBit.rd) || Bad_Reg(dataProBit.rn))
		printf("	it is unpredictable!");
	else{
		imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
		saturate_to = dataProBit.imm5 + 1;
		//printf(" saturate_to = %d",saturate_to);
		source = get_general_register(dataProBit.rn);
		//printf(" source = %X",source);
		decodeImmShift(0,imm,shift_tn);
		//printf(" shift_n = %X",shift_n);
		apsr_c = get_flag_c();
		apsr_c = apsr_c >> 29;
		operand = shift(source,shift_tn->carry,shift_tn->result,apsr_c);
		//printf(" operand = %d",operand);
		signedSatQ(operand,saturate_to,result);
		set_general_register(dataProBit.rd, result->result);//it exsit a problem.
		if(result->carry)
			set_flag_q();
		#if DEBUG
		printf(" APSR = 0x%x",get_apsr());
		printf(" rd = 0x%x",get_general_register(dataProBit.rd));
		printf("	***signed_lsl\n");
#endif
	}
}

//Signed Saturate saturates an optionally-shifted signed value to a selectable signed range.
void signed_asr(int i){
	int imm,source,operand;
	struct RESULTCARRY *shift_tn = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	struct RESULTCARRY *result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	if(Bad_Reg(dataProBit.rd) || Bad_Reg(dataProBit.rn))
		printf("	it is unpredictable!");
	else{
		imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
		if(imm == 0)
			printf(" it is unpredictable!\n");
		else{
			saturate_to = dataProBit.imm5 + 1;
			source = get_general_register(dataProBit.rn);
			decodeImmShift(2,imm,shift_tn);
			apsr_c = get_flag_c();
			apsr_c = apsr_c >> 29;
			operand = shift(source,shift_tn->carry,shift_tn->result,apsr_c);
			signedSatQ(operand,saturate_to,result);
			set_general_register(dataProBit.rd, result->result);//it exsit a problem.
			if(result->carry)
				set_flag_q();
			//printf(" APSR = %X",get_apsr());
			//printf(" rd = %X",get_general_register(dataProBit.rd));
		}
		//printf("	***signed_asr\n");
	}
	free(result);
	free(shift_tn);
}

//Unsigned Bit Field Extract extracts any number of adjacent bits at any position from one register, zero extends them to 32 bits, and writes the result to the destination register.
void unsinged_bit_field_extract(int i){
	int lsbit,msbit,source,result,widthminus1,m,n,j,temp;
	*((int *)(&dataProBit)) = i;
	if(Bad_Reg(dataProBit.rd) || Bad_Reg(dataProBit.rn))
		printf("	it is unpredictable!");
	else{
		lsbit = decode_shift(dataProBit.imm3,dataProBit.imm2);
		widthminus1 = dataProBit.imm5;
		msbit = lsbit + widthminus1;
		if(msbit <= 31){
			m = 0xFFFFFFFF;
			for(j = msbit;j >= 0;j--)
				m = m << 1;
			n = 1;
			for(j = lsbit;j > 1;j--){
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
			//printf(" APSR = %X",get_apsr());
			//printf(" rd = %X",get_general_register(dataProBit.rd));
		}
		else
			printf(" it is unpredictable!\n");
		//printf("	***unsinged_bit_field_extract\n");
	}
}

//Unsigned Saturate saturates an optionally-shifted signed value to a selected unsigned range.
void unsigned_lsl(int i){
	int imm,source,operand;
	struct RESULTCARRY *shift_tn = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	struct RESULTCARRY *result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	if(Bad_Reg(dataProBit.rd) || Bad_Reg(dataProBit.rn))
		printf("	it is unpredictable!");
	else{
		imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
		saturate_to = dataProBit.imm5;
		source = get_general_register(dataProBit.rn);
		decodeImmShift(0,imm,shift_tn);
		apsr_c = get_flag_c();
		apsr_c = apsr_c >> 29;
		operand = shift(source,shift_tn->carry,shift_tn->result,apsr_c);
		unsignedSatQ(operand,saturate_to,result);
		set_general_register(dataProBit.rd, result->result);
		if(result->carry)
			set_flag_q();
		//printf(" APSR = %X",get_apsr());
		//printf(" rd = %X",get_general_register(dataProBit.rd));
		//printf("	***unsigned_lsl\n");
	}
	free(result);
	free(shift_tn);
}

//Unsigned Saturate saturates an optionally-shifted signed value to a selected unsigned range.
void unsigned_asr(int i){
	int imm,source,operand;
	struct RESULTCARRY *shift_tn = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	struct RESULTCARRY *result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned saturate_to,apsr_c;
	*((int *)(&dataProBit)) = i;
	if(Bad_Reg(dataProBit.rd) || Bad_Reg(dataProBit.rn))
		printf("	it is unpredictable!");
	else{
		imm = decode_shift(dataProBit.imm3,dataProBit.imm2);
		if(imm == 0)
			printf(" it is unpredictable!\n");
		else{
			saturate_to = dataProBit.imm5;
			source = get_general_register(dataProBit.rn);
			decodeImmShift(2,imm,shift_tn);
			apsr_c = get_flag_c();
			apsr_c = apsr_c >> 29;
			operand = shift(source,shift_tn->carry,shift_tn->result,apsr_c);
			unsignedSatQ(operand,saturate_to,shift_tn);
			set_general_register(dataProBit.rd, result->result);
			if(result->carry)
				set_flag_q();
			//printf(" APSR = %X",get_apsr());
			//printf(" rd = %X",get_general_register(dataProBit.rd));
		}
		//printf("	***unsigned_asr\n");
	}
	free(shift_tn);
	free(result);
}
