#ifndef _SHIFT_ROTATE
#define _SHIFT_ROTATE

#include "stdio.h"
#include "instruction.h"

void lsl_c(unsigned x,unsigned n, struct RESULTCARRY* result_lsl_c){
	unsigned c_out;

	for(; n > 0; n--)
	{
		c_out = x;
		x = x << 1;
	}
	c_out = (c_out & 0x80000000) >> 31;
	result_lsl_c->result = x;
	result_lsl_c->carry = c_out;
}

void lsr_c(unsigned x,unsigned n,struct RESULTCARRY* result_lsr_c){
	unsigned c_out;
	for(; n > 0; n--)
	{
		c_out = x;
		x = x >>1;
	}
	result_lsr_c->result = x;
	result_lsr_c->carry = c_out;
}

void asr_c(int x,unsigned n,struct RESULTCARRY *result_asr_c){
	unsigned c_out;

	for(; n > 0; n--)
	{
		c_out = x;
		x = x >>1;
	}
	c_out = c_out & 0x00000001;
	result_asr_c->result = x;
	result_asr_c->carry = c_out;
}

int lsl(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;
	if(n == 0)
		result->result = x;
	else
		lsl_c(x,n,result);
	k = result->result;
	free(result);
	return k;
}

int lsr(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;
	if(n == 0)
		result->result = x;
	else
		lsr_c(x,n,result);
	k = result->result;
	free(result);
	return k;
}

int asr(int x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;
	if(n == 0)
		result->result = x;
	else
		asr_c(x,n,result);
	k= result->result;
	free(result);
	return k;
}

void ror_c(unsigned x,unsigned n, struct RESULTCARRY* result_ror_c){
	unsigned m = n % 32;
	unsigned result, c_out;
	if(m == 0)
		result = x;
	else
		result = lsr(x,m) | lsl(x,32-m);
	c_out = result;
//	c_out = (c_out & 0x80000000) >> 2;				modified by Jacky on 08.7.3, for carry returned should be a bit,
	c_out = (c_out & 0x80000000) >> 31;			//	so only can be a 1 or 0, so does rol_c, rrx_c....
	result_ror_c->result = result;
	result_ror_c->carry = c_out;
}

void rol_c(unsigned x,unsigned n,struct RESULTCARRY* result_rol_c){
	unsigned m = n % 32;
	unsigned result, c_out;
	if(m == 0)
		result = x;
	else
		result = lsl(x,m) | lsr(x,32-m);
	c_out = result;
	c_out = c_out & 0x00000001;
	result_rol_c->result = result;
	result_rol_c->carry = c_out;
}

void rrx_c(unsigned x,unsigned c_in,struct RESULTCARRY* result_rrx_c){
	unsigned result, c_out;
	result = (c_in << 31) | (x >> 1);
	c_out = x;
	c_out = c_out & 0x00000001;
	result_rrx_c->result = result;
	result_rrx_c->carry = c_out;
}

int ror(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;

	ror_c(x,n,result);
	k = result->result;
	free(result);

	return k;
}

int rol(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;
	rol_c(x,n,result);
	k = result->result;
	free(result);
	return k;
}

int rrx(unsigned x,unsigned n){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;
	rrx_c(x,n,result);
	k = result->result;
	free(result);
	return k;
}

void decodeImmShift(int type,int imm5,struct RESULTCARRY *immshift ){
	int shift_n,shift_t;

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
	}
	immshift->result = shift_n;
	immshift->carry = shift_t;
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
void shift_c(int value,int type,int n,int carry_in,struct RESULTCARRY *result_shiftc){
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
				lsl_c(value,n,result_shiftc);
		}break;
		case SRType_LSR:
			lsr_c(value,n,result_shiftc);
			break;
		case SRType_ASR:
			asr_c(value,n,result_shiftc);
			break;
		case SRType_ROR:
			ror_c(value,n,result_shiftc);
			break;
		case SRType_RRX:
			rrx_c(value,carry_in,result_shiftc);
			break;
	}
}

int shift(int value,int type,int n,int carry_in){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;

	shift_c(value,type,n,carry_in,result);
	k = result->result;
	free(result);
	return k;
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

void signedSatQ(int i,int j,struct RESULTCARRY* signedsatq){
	int saturated_i,result,k,m;
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
}

void unsignedSatQ(int i,int j,struct RESULTCARRY* unsignedsatq){
	int saturated_i,result,k,m;

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
}

int signedSat(int i,int j){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;
	signedSatQ(i,j,result);
	k = result->result;
	free(result);
	return k;
}

int unsignedSat(int i,int j){
	struct RESULTCARRY* result = (struct RESULTCARRY*)malloc(sizeof(struct RESULTCARRY));
	int k;

	unsignedSatQ(i,j,result);
	k = result->result;

	free(result);
	return k;
}
#endif
