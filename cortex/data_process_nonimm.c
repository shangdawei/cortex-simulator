/**
 *
 * This file is to define the function to handle the Data_Processing_NonImme
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#include "data_process_nonimm.h" 
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
	printf("index : %d", index);

	if((dataProConShift.op == 0x8) &&(dataProConShift.rd ==0xf)&&(dataProConShift.s==0x1 )){
		index = dataProConShift.op+16;
	}else if((dataProConShift.op == 0x0) &&(dataProConShift.rd ==0xf)&&(dataProConShift.s==0x1 )){
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


void reg_ctrl_shift(int instuction){}
void sign_unsign_extend(int instruction){}
void simd_add_sub(int instruction){}
void other_three_reg_data_pro(int instruction){}
void bit32_multiply_acc(int instruction){}
void bit64_multiply(int instruction){}
void data_pro_nonimm_reserved(int instruction){}

void err_reg(){
	printf("opcode error\n");
}



/*************************************************************************************************
 *
 *function of data processing: constant shift
 *
*************************************************************************************************/	


void and_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] AND shifted;
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
#if DEBUG_I
	printf(" shifted = %d",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
#endif
	result = source & shifted;
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***and_reg\n");	
	printf("********AND {S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}

void bic_reg(int i)
{
/*  
	BIC
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] AND NOT(shifted);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source & (~shifted);
#if DEBUG_I
	printf(" shifted = %x",shifted);
	printf(" source = %x",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x", result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***bic_reg\n");	
	printf("********BIC{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void orr_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] OR shifted;
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source|shifted;
#if DEBUG_I
	printf(" shifted = %x",shifted);
	printf(" source = %x",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x", result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***orr_reg\n");	
	printf("********ORR{S}<c><q> {<Rd>,} <Rn>, <Rm> {,<shift>}******* \n");
#endif
}


void orn_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] OR NOT(shifted);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source|(~shifted);
#if DEBUG_I
	printf(" shifted = %x",shifted);
	printf(" source = %x",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x", result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***orn_reg\n");	
	printf("********ORN{S}<c><q> {<Rd>,} <Rn>, <Rm> {,<shift>}******* \n");
#endif
}
void eor_reg(int i)
{
/*if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] EOR shifted;
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source^shifted;
#if DEBUG_I
	printf(" shifted = %x",shifted);
	printf(" source = %x",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x", result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***eor_reg\n");	
	printf("********EOR{S}<c><q> {<Rd>,} <Rn>, <Rm> {,<shift>}******* \n");
#endif
}
void add_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], shifted, '0');
if d == 15 then
ALUWritePC(result); // setflags is always FALSE here
else
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = addwithcarry(source,shifted,0);
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	if(dataProConShift.rd==15)
		ALUWritePC(result);
	else
		set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***adc_reg\n");	
	printf("********ADC{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}

void adc_reg(int i)
{
/*if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], shifted, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = addwithcarry(source,shifted,apsr_c);
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***adc_reg\n");	
	printf("********ADC{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void sbc_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], NOT(shifted), APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = addwithcarry(source,~shifted,apsr_c);
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
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
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***sbc_reg\n");	
	printf("********SBC{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void sub_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], NOT(shifted), '1');
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = addwithcarry(source,~shifted,1);
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***sub_reg\n");	
	printf("********SUB{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void rsb_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], NOT(shifted), APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = addwithcarry(source,~shifted,apsr_c);
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s==1){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(get_calculate_overflow())//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***rsb_reg\n");	
	printf("********RSB{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void tst_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] AND shifted;
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted_carry = shift_c(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source & shifted_carry->result;
#if DEBUG_I
	printf(" shifted = %c",shifted_carry->result);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	if(result & 0x80000000)//whether negative
		set_flag_n();
	else
		cle_flag_n();
	if(result==0)//whether zero
		set_flag_z();
	else
		cle_flag_z();
	if(get_calculate_carry())//whether carry
		set_flag_c();
	else
		cle_flag_c();
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***tst_reg\n");	
	printf("********TST{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void mov_reg(int i)
{
/*
in fact, this function includes 6 different instructions(MOV,LSL,LSR,ASR,ROR,RRX), they are distinguished by type and imm5.  
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	struct RESULTCARRY* result_shiftc = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	switch(dataProConShift.type)
	{
	case 0:
		printf("Move, and immediate shift instructions:mov_reg \n");
		if(!shift_n)
		{
		//mov
/*
if ConditionPassed() then
EncodingSpecificOperations();
result = R[m]; if d == 15 then
ALUWritePC(result); // setflags is always FALSE here
else
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
		*/
			result = dataProConShift.rm;
			if(dataProConShift.rd==15)
				ALUWritePC(result);
			else
				set_general_register(dataProConShift.rd, result);
			if(dataProConShift.s)
			{
			if(result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(result==0)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(get_calculate_carry())//whether carry
				set_flag_c();
			else
				cle_flag_c();
			}
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
		}
		else
		{
		//lsl
/*
if ConditionPassed() then
EncodingSpecificOperations();
(result, carry) = Shift_C(R[m], SRType_LSL, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
			result_shiftc = shift_c(dataProConShift.rm,SRType_LSL,shift_n,apsr_c);
			set_general_register(dataProConShift.rd, result_shiftc->result);
			if(dataProConShift.s)
			{
				if(result_shiftc->result & 0x80000000)//whether negative
					set_flag_n();
				else
					cle_flag_n();
				if(result_shiftc->result==0)//whether zero
					set_flag_z();
				else
					cle_flag_z();
				if(result_shiftc->carry)//whether carry
					set_flag_c();
				else
					cle_flag_c();
			}
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result_shiftc->result);
#endif
		}
		break;
	case 1:
		//lsr
/*
if ConditionPassed() then
EncodingSpecificOperations();
(result, carry) = Shift_C(R[m], SRType_LSR, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
		result_shiftc = shift_c(dataProConShift.rm,SRType_LSR,shift_n,apsr_c);
		set_general_register(dataProConShift.rd, result_shiftc->result);
		if(dataProConShift.s)
		{
			if(result_shiftc->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(!result_shiftc->result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(result_shiftc->carry)//whether carry
				set_flag_c();
			else
				cle_flag_c();
		}
		break;
	case 2:
		//asr
/*
if ConditionPassed() then
EncodingSpecificOperations();
(result, carry) = Shift_C(R[m], SRType_ASR, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
		result_shiftc = shift_c(dataProConShift.rm,SRType_ASR,shift_n,apsr_c);
		set_general_register(dataProConShift.rd, result_shiftc->result);
		if(dataProConShift.s)
		{
			if(result_shiftc->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(!result_shiftc->result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(result_shiftc->carry)//whether carry
				set_flag_c();
			else
				cle_flag_c();
		}
		break;
	case 3:
		if(!shift_n)
		{
		//ror
		}
		else
		{
		//rrx
		}
		break;
	}

	//if(result & 0x80000000)//whether negative
	//	set_flag_n();
	//else
	//	cle_flag_n();
	//if(result==0)//whether zero
	//	set_flag_z();
	//else
	//	cle_flag_z();
	//if(get_calculate_carry())//whether carry
	//	set_flag_c();
	//else
	//	cle_flag_c();
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***mov_reg\n");	
	printf("********Move, and immediate shift instructions******* \n");
#endif
}
void mvn_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = NOT(shifted);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted_carry = shift_c(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = ~shifted_carry->result;
	set_general_register(dataProConShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(dataProConShift.s)
	{
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(result==0)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***mvn_reg\n");	
	printf("********MVN{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void teq_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = R[n] EOR shifted;
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted_carry = shift_c(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = dataProConShift.rn^shifted_carry->result;
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(result & 0x80000000)//whether negative
		set_flag_n();
	else
		cle_flag_n();
	if(result==0)//whether zero
		set_flag_z();
	else
		cle_flag_z();
	if(get_calculate_carry())//whether carry
		set_flag_c();
	else
		cle_flag_c();
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***teq_reg\n");	
	printf("********TEQ{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void cmn_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(shifted, carry) = Shift_C(R[m], shift_t, shift_n, APSR.C);
result = NOT(shifted);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted_carry = shift_c(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = ~shifted_carry->result;
	set_general_register(dataProConShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(dataProConShift.s)
	{
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***cmn_reg\n");	
	printf("********CMN{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void cmp_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], NOT(shifted), '1');
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted,source,result,shift_n;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shifted = shift(dataProConShift.rm,dataProConShift.type,shift_n,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = addwithcarry(source,~shifted,1);
#if DEBUG_I
	printf(" shifted = %c",shifted);
	printf(" source = %c",source);
	printf(" apsr_c = %c",apsr_c);
	printf(" result = %x",result);
#endif
	if(result & 0x80000000)//whether negative
		set_flag_n();
	else
		cle_flag_n();
	if(result==0)//whether zero
		set_flag_z();
	else
		cle_flag_z();
	if(get_calculate_carry())//whether carry
		set_flag_c();
	else
		cle_flag_c();
	if(get_calculate_overflow())//whether overflow
		set_flag_v();
	else
		cle_flag_v();
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***rsb_reg\n");	
	printf("********RSB{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}


/*************************************************************************************************
 *
 *function of Register-controlled shift
 *
 *************************************************************************************************/	

void lsl_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shift_n = UInt(R[m]<7:0>);
(result, carry) = Shift_C(R[n], SRType_LSL, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rn);//get data from source register
	shifted_carry = shift_c(source,SRType_LSL,shift_n,apsr_c);
	result = shifted_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(regCtrlShift.s)
	{
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(get_calculate_carry())//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(regCtrlShift.rd));
	printf("	***lsl_reg\n");	
	printf("********LSL{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void lsr_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shift_n = UInt(R[m]<7:0>);
(result, carry) = Shift_C(R[n], SRType_LSR, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rn);//get data from source register
	shifted_carry = shift_c(source,SRType_LSR,shift_n,apsr_c);
	result = shifted_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(regCtrlShift.s)
	{
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shifted_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(dataProConShift.rd));
	printf("	***lsr_reg\n");	
#endif
}
void asr_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shift_n = UInt(R[m]<7:0>);
(result, carry) = Shift_C(R[n], SRType_ASR, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rn);//get data from source register
	shifted_carry = shift_c(source,SRType_ASR,shift_n,apsr_c);
	result = shifted_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(regCtrlShift.s)
	{
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shifted_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(regCtrlShift.rd));
	printf("	***asr_reg\n");	
#endif
}
void ror_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
(result, carry) = Shift_C(R[m], SRType_ROR, shift_n, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
	int source,result,shift_n;
	struct RESULTCARRY* shifted_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rm);//get data from source register
	shifted_carry = shift_c(source,SRType_ROR,shift_n,apsr_c);
	result = shifted_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shifted_carry->result);
	printf(" source = %x",source);
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(regCtrlShift.s)
	{
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shifted_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %c",get_apsr());
	printf(" rd = %c",get_general_register(regCtrlShift.rd));
	printf("	***ror_reg\n");	
#endif
}

/*************************************************************************************************
 *
 *function of Sign and unsigned extend instructions with optional addition
 *
*************************************************************************************************/	

void sxtb(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
rotated = ROR(R[m], rotation);
R[d] = SignExtend(rotated<7:0>, 32);
*/
	int rotated;
	*((int *)(&signUnsignExtend)) = i;
	rotated = ror(get_general_register(signUnsignExtend.rm),signUnsignExtend.rot);

}
void sxth(int i){}
void uxtb(int i){}
void uxth(int i){}

/*************************************************************************************************
 *
 *functions of other three-register data processing instructions
 *
 *************************************************************************************************/
void clz(int i){}
void rbit(int i){}
void rev(int i){}
void rev16(int i){}
void revsh(int i){}

/*************************************************************************************************
 *
 *functions of 32-bit multiplies instuctions, with or without accumulate
 *
*************************************************************************************************/
void mla(int i){}
void mls(int i){}
void mul(int i){}
/*************************************************************************************************
 *
 *functions of 64-bit multiply, multiply-accumulate, and divide instrucions 
 *
*************************************************************************************************/
void smull(int i){}
void sdiv(int i){}
void umull(int i){}
void udiv(int i){}
void smlal(int i){}
void umlal(int i){}
