#ifndef _SHIFT_ROTATE
#define _SHIFT_ROTATE

#include "stdio.h"
#include "instruction.h"

int lsl_c(unsigned x,unsigned n){
	unsigned c_out;
	for(; n > 0; n--)
	{
		c_out = x;
		x = x << 1;
	}
	c_out = (c_out & 0x80000000) >> 2;
	set_carry(c_out);
	return x;
}

int lsr_c(unsigned x,unsigned n){
	unsigned c_out;
	for(; n > 0; n--)
	{
		c_out = x;
		x = x >>1;
	}
	c_out = (c_out & 0x00000001) << 29;
	set_carry(c_out);
	return x;
}

int asr_c(int x,unsigned n){
	unsigned c_out;
	for(; n > 0; n--)
	{
		c_out = x;
		x = x >>1;
	}
	c_out = (c_out & 0x00000001) << 29;
	set_carry(c_out);
	return x;	
}

int lsl(unsigned x,unsigned n){
	unsigned result;
	if(n == 0)
		result = x;
	else
		result = lsl_c(x,n);
	return result;
}

int lsr(unsigned x,unsigned n){
	unsigned result;
	if(n == 0)
		result = x;
	else
		result = lsr_c(x,n);
	return result;
}

int asr(int x,unsigned n){
	unsigned result;
	if(n == 0)
		result = x;
	else
		result = asr_c(x,n);
	return result;
}

int ror_c(unsigned x,unsigned n){
	unsigned m = n % 32;
	unsigned result, c_out;
	if(m == 0)
		result = x;
	else
		result = lsr(x,m) | lsl(x,32-m);
	c_out = result;
	c_out = (c_out & 0x80000000) >> 2;
	set_carry(c_out);
	return result;
}

int rol_c(unsigned x,unsigned n){
	unsigned m = n % 32;
	unsigned result, c_out;
	if(m == 0)
		result = x;
	else
		result = lsl(x,m) | lsr(x,32-m);
	c_out = result;
	c_out = (c_out & 0x00000001) << 29;
	set_carry(c_out);
	return result;
}

int rrx_c(unsigned x,unsigned c_in){
	unsigned result, c_out;
	result = (c_in << 31) | (x >> 1);
	c_out = x;
	c_out = (c_out & 0x00000001) << 29;
	set_carry(c_out);
	return result;
}

int ror(unsigned x,unsigned n){
	int result;
	result = ror_c(x,n);
	return result;
}

int rol(unsigned x,unsigned n){
	int result;
	result = rol_c(x,n);
	return result;
}

int rrx(unsigned x,unsigned n){
	int result;
	result = rrx_c(x,n);
	return result;
}

int decodeImmShift(int type,int imm5){
	int shift_n;
	if((type == 0) && (imm5 == 0)){
		set_shift_t(0);
		shift_n = imm5;
	}
	else if((type == 0) && (imm5 != 0)){
		set_shift_t(1);
		shift_n = imm5;
	}
	else if(type == 1){
		set_shift_t(2);
		if(imm5 == 0)
			shift_n = 32;
		else
			shift_n = imm5;
	}
	else if(type == 2){
		set_shift_t(3);
		if(imm5 == 0)
			shift_n = 32;
		else
			shift_n = imm5;
	}
	else{
		if(imm5 == 0){
			set_shift_t(5);
			shift_n = 1;
		}
		else{
			set_shift_t(4);
			shift_n = imm5;
		}
	}
	return shift_n;
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
	int result,carry;
	struct RESULTCARRY* result_shiftc = NULL;
	switch(type){
		case SRType_None:{
			result = value;
			carry = carry_in;
			//set_carry(carry_in);
		}break;
		case SRType_LSL:{
			if(n == 0){
				result = value;
				carry = carry_in;
				//set_carry(carry_in);
			}
			else
				result = lsl_c(value,n);
				carry = n;
		}break;
		case SRType_LSR:
			result = lsr_c(value,n);
			carry = n;
			break;
		case SRType_ASR:
			result = asr_c(value,n);
			carry = n;
			break;
		case SRType_ROR:
			result = ror_c(value,n);
			carry = n;
			break;
		case SRType_RRX:
			result = rrx_c(value,carry_in);
			carry = carry_in;
			break;
	}
	result_shiftc->result = result;
	result_shiftc->carry = carry;
	return result_shiftc;
}

int shift(int value,int type,int n,int carry_in){
	struct RESULTCARRY* result;
	result = shift_c(value,type,n,carry_in);
	return result->result;
}

int min(int x,int y){
	int z;
	z = (x <= y)?x:y;
	return z;
}

int max(int x,int y){
	int z;
	z = (x >= y)?x:y;
	return z;
}

int signedSatQ(int i,int j){
	int saturated_i,result,k,m;
	m = 1;
	saturated_i = min(max(i,-(1<<(j-1))),(1<<(j-1))-1);//?????
	for(k = j-1;k > 0;k--){
		m = m << 1;
		m = m + 1;
	}
	result = saturated_i & m;
	if(result != i)
		set_sat(1);
	else
		set_sat(0);
	return result;
}

int unsignedSatQ(int i,int j){
	int saturated_i,result,k,m;
	m = 1;
	saturated_i = min(max(i,0),(1<<j)-1);
	for(k = j-1;k > 0;k--){
		m = m << 1;
		m = m + 1;
	}
	result = saturated_i & m;
	if(result != i)
		set_sat(1);
	else
		set_sat(0);
	return result;
}

int signedSat(int i,int j){
	int result;
	result = signedSatQ(i,j);
	return result;
}

int unsignedSat(int i,int j){
	int result;
	result = unsignedSatQ(i,j);
	return result;
}
#endif
