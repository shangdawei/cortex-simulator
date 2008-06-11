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



/*
 *
 *function of data processing: constant shift
 *
 */	

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
void and_reg(int i)
{
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
void sub_reg(int i){}
void rsb_reg(int i){}
void tst_reg(int i){}
void mov_reg(int i){}
void mvn_reg(int i){}
void teq_reg(int i){}
void cmn_reg(int i){}
void cmp_reg(int i){}


/*
 *
 *function of Register-controlled shift
 *
 */	

void lsl_reg(int i){}
void lsr_reg(int i){}
void asr_reg(int i){}
void ror_reg(int i){}

/*
 *
 *function of Sign and unsigned extend instructions with optional addition
 *
 */	

void sxtb(int i){}
void sxth(int i){}
void uxtb(int i){}
void uxth(int i){}

/*
 *
 *functions of other three-register data processing instructions
 *
 */
void clz(int i){}
void rbit(int i){}
void rev(int i){}
void rev16(int i){}
void revsh(int i){}

/*
 *
 *functions of 32-bit multiplies instuctions, with or without accumulate
 *
 */
void mla(int i){}
void mls(int i){}
void mul(int i){}
/*
 *
 *functions of 64-bit multiply, multiply-accumulate, and divide instrucions 
 *
 */
void smull(int i){}
void sdiv(int i){}
void umull(int i){}
void udiv(int i){}
void smlal(int i){}
void umlal(int i){}

