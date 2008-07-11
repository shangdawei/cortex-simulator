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

	if(dataProConShift.pass1)
	{
	printf("unpredictable instruction");
	return;
	}

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


void reg_ctrl_shift(int instruction)
{
	int opcode,index;
	func f_ptr;
	*((int *)(&regCtrlShift)) = instruction;
	opcode=decode_imm5(regCtrlShift.op,regCtrlShift.op2);
	printf("reg_ctrl_shift: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n", opcode);
	printf("S: 0x%x \n", regCtrlShift.s);
	printf("Rn: 0x%x \n", regCtrlShift.rn);
	printf("Rd: 0x%x \n", regCtrlShift.rd);
	printf("Rm: 0x%x \n", regCtrlShift.rm);

	if(!regCtrlShift.op2)
	{
		printf("UNDEFINED instructions!\n");
		return;
	}
	index = regCtrlShift.op;
	printf("index : %d", index);


	f_ptr=(void *)reg_ctrl_s[index];
	f_ptr(instruction);
}
void sign_unsign_extend(int instruction)
{
	int index;
	func f_ptr;
	*((int *)(&signUnsignExtend)) = instruction;
	printf("sign_unsign_extend: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n",signUnsignExtend.op);
	printf("Rn: 0x%x \n", signUnsignExtend.rn);
	printf("Rd: 0x%x \n", signUnsignExtend.rd);
	printf("Rm: 0x%x \n", signUnsignExtend.rm);
	printf("rot: 0x%x \n",signUnsignExtend.rot);

	if(signUnsignExtend.rn!=0xf)
	{
		printf("UNDEFINED instructions!\n");
		return;
	}
	if(signUnsignExtend.pass1)
	{
		printf("unpredictable instruction");
		return;
	}

	index = signUnsignExtend.op;
	printf("index : %d", index);


	f_ptr=(void *)reg_ctrl_s[index];
	f_ptr(instruction);
}
void simd_add_sub(int instruction)
{
	*((int *)(&SIMDAddSub)) = instruction;
	printf("simd_add_sub: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n",SIMDAddSub.op);
	printf("Rn: 0x%x \n", SIMDAddSub.rn);
	printf("Rd: 0x%x \n", SIMDAddSub.rd);
	printf("Rm: 0x%x \n", SIMDAddSub.rm);
	printf("prefix: 0x%x \n",SIMDAddSub.prefix);

}
void other_three_reg_data_pro(int instruction)
{
	int index,opcode;
	func f_ptr;
	*((int *)(&otherThreeRegDataPro)) = instruction;
	opcode=decode_imm5(otherThreeRegDataPro.op,otherThreeRegDataPro.op2);
	printf("other_three_reg_data_pro: 0x%X \n",instruction);
	printf("Operate Code : 0x%x \n",opcode);
	printf("Rn: 0x%x \n", otherThreeRegDataPro.rn);
	printf("Rd: 0x%x \n", otherThreeRegDataPro.rd);
	printf("Rm: 0x%x \n", otherThreeRegDataPro.rm);

	if(otherThreeRegDataPro.op==1)
	{
		index = otherThreeRegDataPro.op2;
	}
	else if(otherThreeRegDataPro.op==3&&otherThreeRegDataPro.op2==0)
	{
		index = 4;
	}
	else
	{
		printf("unpredictable instruction");
		return;
	}
	f_ptr=(void *)other_three_reg_data_p[index];
	f_ptr(instruction);
}
void bit32_multiply_acc(int instruction)
{
	int index;
	func f_ptr;
	*((int *)(&bit32MultiplyAcc)) = instruction;
	printf("bit32_multiply_acc: 0x%X \n",instruction);
	printf("Op : 0x%x \n",bit32MultiplyAcc.op);
	printf("Op2 : 0x%x \n",bit32MultiplyAcc.op2);
	printf("Rn: 0x%x \n", bit32MultiplyAcc.rn);
	printf("Rd: 0x%x \n", bit32MultiplyAcc.rd);
	printf("Rm: 0x%x \n", bit32MultiplyAcc.rm);
	printf("Racc: 0x%x \n", bit32MultiplyAcc.racc);

	if(bit32MultiplyAcc.op||bit32MultiplyAcc.op2>1)
	{
		printf("UNDEFINED instructions!\n");
		return;
	}
	else if(bit32MultiplyAcc.racc!=0xf)
	{
		index = bit32MultiplyAcc.op2;
	}
	else if(bit32MultiplyAcc.op2==0)
	{
		index = 2;
	}
	else
	{
		printf("UNDEFINED instructions!\n");
		return;
	}
	f_ptr=(void *)bit32_multiply_a[index];
	f_ptr(instruction);

}
void bit64_multiply(int instruction)
{
	int index;
	func f_ptr;
	*((int *)(&bit64Multiply)) = instruction;
	printf("bit64_multiply: 0x%X \n",instruction);
	printf("Op : 0x%x \n",bit64Multiply.op);
	printf("Op2 : 0x%x \n",bit64Multiply.op2);
	printf("Rn: 0x%x \n", bit64Multiply.rn);
	printf("Rdlo: 0x%x \n", bit64Multiply.rdlo);
	printf("Rdhi: 0x%x \n", bit64Multiply.rdhi);
	printf("Rm: 0x%x \n", bit64Multiply.rm);
	switch(bit64Multiply.op)
	{
	case 0:
		if(!bit64Multiply.op2)
		{
			index = 0;
		}
		else
		{
			printf("UNDEFINED instructions!\n");
			return;
		}
		break;
	case 1:
		if(bit64Multiply.op2==0xf)
		{
			index = 1;
		}
		else
		{
			printf("UNDEFINED instructions!\n");
			return;
		}
		break;
	case 2:
		if(!bit64Multiply.op2)
		{
			index = 2;
		}
		else
		{
			printf("UNDEFINED instructions!\n");
			return;
		}
		break;
	case 3:
		if(bit64Multiply.op2==0xf)
		{
			index = 3;
		}
		else
		{
			printf("UNDEFINED instructions!\n");
			return;
		}
		break;		
	case 4:
		if(!bit64Multiply.op2)
		{
			index = 4;
		}
		else
		{
			printf("UNDEFINED instructions!\n");
			return;
		}
		break;
	case 6:
		if(!bit64Multiply.op2)
		{
			index = 5;
		}
		else
		{
			printf("UNDEFINED instructions!\n");
			return;
		}
		break;
	default:
			printf("UNDEFINED instructions!\n");
			return;
	}
	f_ptr=(void *)bit64_mul[index];
	f_ptr(instruction);
}
void data_pro_nonimm_reserved(int instruction)
{
	printf("data_pro_nonimm_reserved: 0x%X \n",instruction);
}

void err_reg(){
	printf("UNDEFINED instructions!\n");
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
	int source,result;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source & shift_carry->result;
	set_general_register(dataProConShift.rd, result);//send data to destination register
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	if(dataProConShift.s){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int source,result;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source & (~shift_carry->result);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int source,result;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source|shift_carry->result;
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result);
#endif
	set_general_register(dataProConShift.rd, result);//send data to destination register
	if(dataProConShift.s){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int source,result,shift_n;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shift_tn = decodeImmShift(dataProConShift.type,shift_n);
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = get_general_register(dataProConShift.rm)|(~shift_carry->result);
	set_general_register(dataProConShift.rd,result);
#if DEBUG
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
#endif
	if(dataProConShift.s){
		if(result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int source,result;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source^shift_carry->result;
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" apsr_c = %x",apsr_c);
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int shifted;
	struct CALCULATECO *result;
	struct RESULTCARRY *shift_tn;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shifted = shift(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
	result = addwithcarry(get_general_register(dataProConShift.rn),shifted,0);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shifted);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result->result);
#endif
	if(dataProConShift.rd==15)
		ALUWritePC(result->result);
	else
		set_general_register(dataProConShift.rd, result->result);//send data to destination register
	if(dataProConShift.s==1){
		if(result->result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result->result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
	printf("	***add_reg\n");	
	printf("********ADD{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}

void adc_reg(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
shifted = Shift(R[m], shift_t, shift_n, APSR.C);
(result, carry, overflow) = AddWithCarry(R[n], shifted, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted;
	struct CALCULATECO *result;
	struct RESULTCARRY *shift_tn;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shifted = shift(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
	result = addwithcarry(get_general_register(dataProConShift.rn),shifted,apsr_c);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shifted);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result->result);
#endif
	set_general_register(dataProConShift.rd, result->result);//send data to destination register
	if(dataProConShift.s==1){
		if(result->result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result->result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int shifted;
	struct CALCULATECO *result;
	struct RESULTCARRY *shift_tn;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shifted = shift(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
	result = addwithcarry(get_general_register(dataProConShift.rn),~shifted,apsr_c);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shifted);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result->result);
#endif
	set_general_register(dataProConShift.rd, result->result);//send data to destination register
	if(dataProConShift.s){
		if(result->result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result->result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int shifted;
	struct CALCULATECO *result;
	struct RESULTCARRY *shift_tn;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shifted = shift(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
	result = addwithcarry(get_general_register(dataProConShift.rn),~shifted,1);
#if DEBUG_I
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shifted);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result->result);
#endif
	set_general_register(dataProConShift.rd, result->result);//send data to destination register
	if(dataProConShift.s==1){
		if(result->result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result->result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
(result, carry, overflow) = AddWithCarry(NOT(R[n]), shifted, '1');
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
APSR.V = overflow;
*/
	int shifted;
	struct CALCULATECO *result;
	struct RESULTCARRY *shift_tn;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shifted = shift(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
	printf("addwithcarry(%x,%x,1)",~get_general_register(dataProConShift.rn),shifted);
	result = addwithcarry(~get_general_register(dataProConShift.rn),shifted,1);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shifted);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result->result);
#endif
	set_general_register(dataProConShift.rd, result->result);//send data to destination register
	if(dataProConShift.s==1){
		if(result->result & 0x80000000)//whether negative
			set_flag_n();
		else
			cle_flag_n();
		if(!result->result)//whether zero
			set_flag_z();
		else
			cle_flag_z();
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		if(result->overflow)//whether overflow
			set_flag_v();
		else
			cle_flag_v();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shift_tn = decodeImmShift(dataProConShift.type,shift_n);
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = source & shift_carry->result;
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" source = %x",get_general_register(dataProConShift.rn));
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
	if(shift_carry->carry)//whether carry
		set_flag_c();
	else
		cle_flag_c();
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
	printf("	***tst_reg\n");	
	printf("********TST{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
#endif
}
void mov_reg(int i)
{
/*
in fact, this function includes 6 different instructions(MOV,LSL,LSR,ASR,ROR,RRX), they are distinguished by type and imm5.  
*/
	int source,result,shift_n;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shift_tn = decodeImmShift(dataProConShift.type,shift_n);
	//shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	switch(dataProConShift.type)
	{
	case 0:
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
			result = get_general_register(dataProConShift.rm);
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
			if(!result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(apsr_c)//whether carry
				set_flag_c();
			else
				cle_flag_c();
			}
#ifdef DEBUG
	printf(" MOV instructions");
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
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
			shift_carry = shift_c(get_general_register(dataProConShift.rm),SRType_LSL,shift_n,apsr_c);
			set_general_register(dataProConShift.rd, shift_carry->result);
			if(dataProConShift.s)
			{
				if(shift_carry->result & 0x80000000)//whether negative
					set_flag_n();
				else
					cle_flag_n();
				if(!shift_carry->result)//whether zero
				//{
					set_flag_z();
				//	printf("	set flag zero!	");
				//}
				else
				//{
				//	printf("	clear flag zero!	");
					cle_flag_z();
				//}
				if(shift_carry->carry)//whether carry
				//{
					set_flag_c();
					//printf("set flag carry!");
				//}
				else
				//{
					cle_flag_c();
				//	printf("clear flag carry!");
				//}
			}
#if DEBUG
	printf(" LSL instructions");
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
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
		shift_carry = shift_c(get_general_register(dataProConShift.rm),SRType_LSR,shift_n,apsr_c);
		set_general_register(dataProConShift.rd, shift_carry->result);
		if(dataProConShift.s)
		{
			if(shift_carry->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(!shift_carry->result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(shift_carry->carry)//whether carry
				set_flag_c();
			else
				cle_flag_c();
		}
#if DEBUG
	printf(" LSR instructions");
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
#endif
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
		shift_carry = shift_c(get_general_register(dataProConShift.rm),SRType_ASR,shift_n,apsr_c);
		set_general_register(dataProConShift.rd, shift_carry->result);
		if(dataProConShift.s)
		{
			if(shift_carry->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(!shift_carry->result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(shift_carry->carry)//whether carry
				set_flag_c();
			else
				cle_flag_c();
		}
#if DEBUG
	printf(" ASR instructions");
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
#endif
		break;
	case 3:
		if(shift_n)
		{
		//ror
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
		shift_carry = shift_c(get_general_register(dataProConShift.rm),SRType_ROR,shift_n,apsr_c);
		set_general_register(dataProConShift.rd, shift_carry->result);
		if(dataProConShift.s)
		{
			if(shift_carry->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(!shift_carry->result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(shift_carry->carry)//whether carry
				set_flag_c();
			else
				cle_flag_c();
		}
#if DEBUG
	printf(" ROR instructions");
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
#endif
		}
		else
		{
		//rrx
/*
if ConditionPassed() then
EncodingSpecificOperations();
(result, carry) = Shift_C(R[m], SRType_RRX, 1, APSR.C);
R[d] = result;
if setflags then
APSR.N = result<31>;
APSR.Z = IsZeroBit(result);
APSR.C = carry;
// APSR.V unchanged
*/
		shift_carry = shift_c(get_general_register(dataProConShift.rm),SRType_RRX,1,apsr_c);
		set_general_register(dataProConShift.rd, shift_carry->result);
		if(dataProConShift.s)
		{
			if(shift_carry->result & 0x80000000)//whether negative
				set_flag_n();
			else
				cle_flag_n();
			if(!shift_carry->result)//whether zero
				set_flag_z();
			else
				cle_flag_z();
			if(shift_carry->carry)//whether carry
				set_flag_c();
			else
				cle_flag_c();
		}
#if DEBUG
	printf(" RRX instructions");
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
#endif
		}
		break;
	}

#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shift_tn = decodeImmShift(dataProConShift.type,shift_n);
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = ~shift_carry->result;
	set_general_register(dataProConShift.rd,result);
#if DEBUG
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = decode_imm5(dataProConShift.imm3,dataProConShift.imm2);
	shift_tn = decodeImmShift(dataProConShift.type,shift_n);
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = get_general_register(dataProConShift.rn)^shift_carry->result;
#if DEBUG
	printf(" shift_n = %x",shift_n);
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" R[m] = %x",get_general_register(dataProConShift.rm));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" carry = %x",shift_carry->carry);
	printf(" apsr_c = %x",apsr_c);
	printf(" APSR = %x",get_apsr());
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
	if(shift_carry->carry)//whether carry
		set_flag_c();
	else
		cle_flag_c();
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int source,result;
	struct RESULTCARRY *shift_tn,*shift_carry;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shift_carry = shift_c(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
    source = get_general_register(dataProConShift.rn);//get data from source register
	result = ~shift_carry->result;
	set_general_register(dataProConShift.rd,result);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" shifted = %x",shift_carry->result);
	printf(" source = %x",get_general_register(dataProConShift.rn));
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	int shifted;
	struct CALCULATECO *result;
	struct RESULTCARRY *shift_tn;
	unsigned apsr_c;
	*((int *)(&dataProConShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_tn = decodeImmShift(dataProConShift.type,decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	shifted = shift(get_general_register(dataProConShift.rm),shift_tn->carry,shift_tn->result,apsr_c);
	result = addwithcarry(get_general_register(dataProConShift.rn),~shifted,1);
#if DEBUG
	printf(" imm3 = %x",dataProConShift.imm3);
	printf(" imm2 = %x",dataProConShift.imm2);
	printf(" imm5 = %x",decode_imm5(dataProConShift.imm3,dataProConShift.imm2));
	printf(" R[n] = %x",get_general_register(dataProConShift.rn));
	printf(" shift_t = %x",shift_tn->carry);
	printf(" shift_n = %x",shift_tn->result);
	printf(" ~shifted = %x",~shifted);
	printf(" source = %x",get_general_register(dataProConShift.rn));
	printf(" apsr_c = %x",apsr_c);
	printf(" result = %x",result->result);
	printf(" carry = %x",result->carry_out);
#endif
	if(dataProConShift.rd==15)
		ALUWritePC(result->result);
	else
		set_general_register(dataProConShift.rd, result->result);//send data to destination register

	if(result->result & 0x80000000)//whether negative
		set_flag_n();
	else
		cle_flag_n();
	if(!result->result)//whether zero
		set_flag_z();
		cle_flag_z();
	if(result->carry_out)//whether carry
		set_flag_c();
	else
		cle_flag_c();
	if(result->overflow)//whether overflow
		set_flag_v();
	else
		cle_flag_v();
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
	printf("	***cmp_reg\n");	
	printf("********CMP{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}******* \n");
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
	struct RESULTCARRY* shift_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rn);//get data from source register
	shift_carry = shift_c(source,SRType_LSL,shift_n,apsr_c);
	result = shift_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shift_carry->result);
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(regCtrlShift.rd));
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
	struct RESULTCARRY* shift_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rn);//get data from source register
	shift_carry = shift_c(source,SRType_LSR,shift_n,apsr_c);
	result = shift_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shift_carry->result);
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(dataProConShift.rd));
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
	struct RESULTCARRY* shift_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rn);//get data from source register
	shift_carry = shift_c(source,SRType_ASR,shift_n,apsr_c);
	result = shift_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shift_carry->result);
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(regCtrlShift.rd));
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
	struct RESULTCARRY* shift_carry = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	unsigned apsr_c;
	*((int *)(&regCtrlShift)) = i;
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	shift_n = regCtrlShift.rm<<24>>24;
    source = get_general_register(regCtrlShift.rm);//get data from source register
	shift_carry = shift_c(source,SRType_ROR,shift_n,apsr_c);
	result = shift_carry->result;
	set_general_register(regCtrlShift.rd,result);
#if DEBUG_I
	printf(" shifted = %x",shift_carry->result);
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
		if(shift_carry->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
#if DEBUG_I
	printf(" APSR = %x",get_apsr());
	printf(" rd = %x",get_general_register(regCtrlShift.rd));
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
d = UInt(Rd); m = UInt(Rm); rotation = UInt(rotate:'000');
if BadReg(d) || BadReg(m) then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
rotated = ROR(R[m], rotation);
R[d] = SignExtend(rotated<7:0>, 32);
*/
	unsigned int rotated,rotation,result;
	*((int *)(&signUnsignExtend)) = i;
	if(Bad_Reg(signUnsignExtend.rd)||Bad_Reg(signUnsignExtend.rm))
	{
		printf("UNPREDICTABLE instructions!!/n");
		return;
	}
	rotation = signUnsignExtend.rot<<3;
	rotated = ror(get_general_register(signUnsignExtend.rm),signUnsignExtend.rot);
	result = rotated<<24>>24;
	if(result>>7)
	{
		result = 0xfff0|result;
	}
	set_general_register(signUnsignExtend.rd,result);
}
void sxth(int i)
{
/*
d = UInt(Rd); m = UInt(Rm); rotation = UInt(rotate:'000');
if BadReg(d) || BadReg(m) then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
rotated = ROR(R[m], rotation);
R[d] = SignExtend(rotated<15:0>, 32);
*/
	unsigned int rotated,rotation,result;
	*((int *)(&signUnsignExtend)) = i;
	if(Bad_Reg(signUnsignExtend.rd)||Bad_Reg(signUnsignExtend.rm))
	{
		printf("UNPREDICTABLE instructions!!/n");
		return;
	}
	rotation = signUnsignExtend.rot<<3;
	rotated = ror(get_general_register(signUnsignExtend.rm),signUnsignExtend.rot);
	result = rotated<<16>>16;
	if(result>>15)
	{
		result = 0xff00|result;
	}
	set_general_register(signUnsignExtend.rd,result);
}
void uxtb(int i)
{
/*
d = UInt(Rd); m = UInt(Rm); rotation = UInt(rotate:'000');
if BadReg(d) || BadReg(m) then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
rotated = ROR(R[m], rotation);
R[d] = ZeroExtend(rotated<7:0>, 32);
*/
	unsigned int rotated,rotation,result;
	*((int *)(&signUnsignExtend)) = i;
	if(Bad_Reg(signUnsignExtend.rd)||Bad_Reg(signUnsignExtend.rm))
	{
		printf("UNPREDICTABLE instructions!!/n");
		return;
	}
	rotation = signUnsignExtend.rot<<3;
	rotated = ror(get_general_register(signUnsignExtend.rm),signUnsignExtend.rot);
	result = rotated<<24>>24;
	set_general_register(signUnsignExtend.rd,result);
}
void uxth(int i)
{
/*
d = UInt(Rd); m = UInt(Rm); rotation = UInt(rotate:'000');
if BadReg(d) || BadReg(m) then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
rotated = ROR(R[m], rotation);
R[d] = ZeroExtend(rotated<15:0>, 32);
*/
	unsigned int rotated,rotation,result;
	*((int *)(&signUnsignExtend)) = i;
	if(Bad_Reg(signUnsignExtend.rd)||Bad_Reg(signUnsignExtend.rm))
	{
		printf("UNPREDICTABLE instructions!!/n");
		return;
	}
	rotation = signUnsignExtend.rot<<3;
	rotated = ror(get_general_register(signUnsignExtend.rm),signUnsignExtend.rot);
	result = rotated<<16>>16;
	set_general_register(signUnsignExtend.rd,result);
}

/*************************************************************************************************
 *
 *functions of other three-register data processing instructions
 *
 *************************************************************************************************/
void clz(int i)
{
/*
d = UInt(Rd); m = UInt(Rm); m2 = UInt(Rm2);
if BadReg(d) || BadReg(m) || m2 != m then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
result = 31 - HighestSetBit(R[m]); // = 32 if R[m] is zero
R[d] = result<31:0>;
*/
	int result;
	*((int *)(&otherThreeRegDataPro)) = i;
	if(Bad_Reg(otherThreeRegDataPro.rd)||Bad_Reg(otherThreeRegDataPro.rm)||(otherThreeRegDataPro.rn!=otherThreeRegDataPro.rm))
	{
		printf("UNPREDICTABLE instructions!!\n");
		return;
	}
	result = 31 - HighestSetBit(get_general_register(otherThreeRegDataPro.rm));
	set_general_register(otherThreeRegDataPro.rd,result);
}
void rbit(int i)
{
/*
d = UInt(Rd); m = UInt(Rm); m2 = UInt(Rm2);
if BadReg(d) || BadReg(m) || m2 != m then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
bits(32) result;
for i = 0 to 31 do
result<31-i> = R[m]<i>;
R[d] = result;
*/
	int result=0,j,mask,source;
	*((int *)(&otherThreeRegDataPro)) = i;
	if(Bad_Reg(otherThreeRegDataPro.rd)||Bad_Reg(otherThreeRegDataPro.rm)||(otherThreeRegDataPro.rn!=otherThreeRegDataPro.rm))
	{
		printf("UNPREDICTABLE instructions!!/n");
		return;
	} 
	source = get_general_register(otherThreeRegDataPro.rm);
	for(j = 0;j<31;j++)
	{
		mask = (source>>j)&1;
		result = result|(mask<<(31-j));
	}
}
void rev(int i)
{

}
void rev16(int i)
{

}
void revsh(int i)
{

}

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

