#ifndef _SHIFT_ROTATE
#define _SHIFT_ROTATE

#include "stdio.h"
#include "instruction.h"

struct RESULTCARRY* lsl_c(unsigned x,unsigned n){
	unsigned c_out;
	struct RESULTCARRY *result_lsl_c = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	for(; n > 0; n--)
	{
		c_out = x;
		x = x << 1;
	}
	c_out = (c_out & 0x80000000) >> 2;
	result_lsl_c->result = x;
	result_lsl_c->carry = c_out;
	return result_lsl_c;
}

struct RESULTCARRY* lsr_c(unsigned x,unsigned n){
	unsigned c_out;
	struct RESULTCARRY *result_lsr_c = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	for(; n > 0; n--)
	{
		c_out = x;
		x = x >>1;
	}
	result_lsr_c->result = x;
	result_lsr_c->carry = c_out;
	return result_lsr_c;
}

struct RESULTCARRY* asr_c(int x,unsigned n){
	unsigned c_out;
	struct RESULTCARRY *result_asr_c = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	for(; n > 0; n--)
	{
		c_out = x;
		x = x >>1;
	}
	c_out = (c_out & 0x00000001) << 29;
	result_asr_c->result = x;
	result_asr_c->carry = c_out;
	return result_asr_c;	
}

int lsl(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	if(n == 0)
		result->result = x;
	else
		result = lsl_c(x,n);
	return result->result;
}

int lsr(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	if(n == 0)
		result->result = x;
	else
		result = lsr_c(x,n);
	return result->result;
}

int asr(int x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	if(n == 0)
		result->result = x;
	else
		result = asr_c(x,n);
	return result->result;
}

struct RESULTCARRY* ror_c(unsigned x,unsigned n){
	unsigned m = n % 32;
	unsigned result, c_out;
	struct RESULTCARRY* result_ror_c = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	if(m == 0)
		result = x;
	else
		result = lsr(x,m) | lsl(x,32-m);
	c_out = result;
	c_out = (c_out & 0x80000000) >> 2;
	result_ror_c->result = result;
	result_ror_c->carry = c_out;
	return result_ror_c;
}

struct RESULTCARRY* rol_c(unsigned x,unsigned n){
	unsigned m = n % 32;
	unsigned result, c_out;
	struct RESULTCARRY* result_rol_c = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	if(m == 0)
		result = x;
	else
		result = lsl(x,m) | lsr(x,32-m);
	c_out = result;
	c_out = (c_out & 0x00000001) << 29;
	result_rol_c->result = result;
	result_rol_c->carry = c_out;
	return result_rol_c;
}

struct RESULTCARRY* rrx_c(unsigned x,unsigned c_in){
	unsigned result, c_out;
	struct RESULTCARRY* result_rrx_c = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = (c_in << 31) | (x >> 1);
	c_out = x;
	c_out = (c_out & 0x00000001) << 29;
	result_rrx_c->result = result;
	result_rrx_c->carry = c_out;
	return result_rrx_c;
}

int ror(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = ror_c(x,n);
	return result->result;
}

int rol(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = rol_c(x,n);
	return result->result;
}

int rrx(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = rrx_c(x,n);
	return result->result;
}

struct RESULTCARRY* decodeImmShift(int type,int imm5){
	int shift_n,shift_t;
	struct RESULTCARRY *immshift = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	if((type == 0) && (imm5 == 0)){
		shift_t = SRType_None;
		shift_n = imm5;
	}
	else if((type == 0) && (imm5 != 0)){
		shift_t = SRType_LSL;
		shift_n = imm5;
	}
	else if(type == 1){
		shift_t = SRType_LSR;
		if(imm5 == 0)
			shift_n = 32;
		else
			shift_n = imm5;
	}
	else if(type == 2){
		shift_t = SRType_ASR;
		if(imm5 == 0)
			shift_n = 32;
		else
			shift_n = imm5;
	}
	else if(type == 3){
		if(imm5 == 0){
			shift_t = SRType_RRX;
			shift_n = 1;
		}
		else{
			shift_t = SRType_ROR;
			shift_n = imm5;
		}
	}
	else
	{
		printf("type error");
		immshift->result = 0;
		immshift->carry = 0;
		return immshift;
	}
	immshift->result = shift_n;
	immshift->carry = shift_t;
	return immshift;
}
/*
in register.h
#define SRType_None 0
#define SRType_LSL	1
#define SRType_LSR	2
#define SRType_ASR	3
#define SRType_ROR	4
#define SRType_RRX	5
*/
struct RESULTCARRY* shift_c(int value,int type,int n,int carry_in){
	struct RESULTCARRY *result_shiftc = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	switch(type){
		case SRType_None:{
			result_shiftc->result = value;
			result_shiftc->carry = carry_in;
			//set_carry(carry_in);
		}break;
		case SRType_LSL:{
			if(n == 0){
				result_shiftc->result = value;
				result_shiftc->carry = carry_in;
				//set_carry(carry_in);
			}
			else
				result_shiftc = lsl_c(value,n);
		}break;
		case SRType_LSR:
			result_shiftc = lsr_c(value,n);
			break;
		case SRType_ASR:
			result_shiftc = asr_c(value,n);
			break;
		case SRType_ROR:
			result_shiftc = ror_c(value,n);
			break;
		case SRType_RRX:
			result_shiftc = rrx_c(value,carry_in);
			break;
	}
//#ifdef DEBUG
//	printf(" shiftc_result = %d",result);
//	printf(" shiftc_carry = %d",carry);
//#endif
//	result_shiftc->result = result;
//	result_shiftc->carry = carry;
	return result_shiftc;
}

int shift(int value,int type,int n,int carry_in){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = shift_c(value,type,n,carry_in);
	return result->result;
}

//int min(int x,int y){
//	int z;
//	z = (x <= y)?x:y;
//	return z;
//}
//
//int max(int x,int y){
//	int z;
//	z = (x >= y)?x:y;
//	return z;
//}

struct RESULTCARRY* signedSatQ(int i,int j){
	int saturated_i,result,k,m;
	struct RESULTCARRY* signedsatq = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	m = 1;
	saturated_i = min(max(i,-(1<<(j-1))),(1<<(j-1))-1);
	for(k = j-1;k > 0;k--){
		m = m << 1;
		m = m + 1;
	}
	result = saturated_i & m;
	signedsatq->result = result;
	if(result != i)
		signedsatq->carry = 1;
	else
		signedsatq->carry = 0;
	return signedsatq;
}

struct RESULTCARRY* unsignedSatQ(int i,int j){
	int saturated_i,result,k,m;
	struct RESULTCARRY* unsignedsatq = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	m = 1;
	saturated_i = min(max(i,0),(1<<j)-1);
	for(k = j-1;k > 0;k--){
		m = m << 1;
		m = m + 1;
	}
	result = saturated_i & m;
	unsignedsatq->result = result;
	if(result != i)
		unsignedsatq->carry = 1;
	else
		unsignedsatq->carry = 0;
	return unsignedsatq;
}

int signedSat(int i,int j){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = signedSatQ(i,j);
	return result->result;
}

int unsignedSat(int i,int j){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	result = unsignedSatQ(i,j);
	return result->result;
}
#endif
