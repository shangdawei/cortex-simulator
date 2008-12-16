#ifndef _CALCULATE
#define _CALCULATE
#include "instruction.h"
#include "stdio.h"

//simulate CPU based unit ----addition implemet

struct CALCULATECO* addwithcarry(unsigned m,unsigned n,unsigned carry_in){
/*
unsigned_sum = UInt(x) + UInt(y) + UInt(carry_in);
signed_sum = SInt(x) + SInt(y) + UInt(carry_in);
result = unsigned_sum<N-1:0>; // = signed_sum<N-1:0>
carry_out = if UInt(result) == unsigned_sum then '0' else '1';
overflow = if SInt(result) == signed_sum then '0' else '1';
return (result, carry_out, overflow);
*/

	//modified by Jacky on 08.7.3
	//long long u_sum,lx = x,ly = y;
	//long s_sum;
	//int sx = (int)x,sy = (int)y;
	//struct CALCULATECO *rco = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	////u_sum = lx+ly+carry_in;
	//u_sum = 0xfffffffffff;
	//printf("u_sum = %x",u_sum);
	//s_sum = sx+sy+carry_in;
	//printf("sx = %x, sy = %d, s_sum = %x",sx,sy,s_sum);
	//rco->result = x & 0x7fffffff;
	//if(rco->result==u_sum)
	//	rco->carry_out=0;
	//else
	//	rco->carry_out=1;
	//if(((int)rco->result)==s_sum)
	//	rco->overflow=0;
	//else
	//	rco->overflow=1;
	//printf("rco->result = %x,rco->carry = %x,rco->overflow = %x",rco->result,rco->carry_out,rco->overflow);
	//return rco;
	unsigned sum,temp1,temp2,temp3,temp4,temp5;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	sum = m + n + carry_in;
//printf(" %x",sum);
	temp1 = (m & 0x7FFFFFFF) + (n & 0x7FFFFFFF) + carry_in;
//printf(" %x",temp1);
	temp1 = temp1 >> 31;
//printf(" %x",temp1);
	temp2 = m >> 31;
//printf(" %x",temp2);
	temp3 = n >> 31;
//printf(" %x",temp3);
	temp4 = temp1 + temp2 + temp3;
//printf(" %x",temp4);
	if(temp4 >= 2)//judge carry bit
		result->carry_out = 1;
	else
		result->carry_out = 0;
	temp5 = (temp1&&temp2&&(!temp3))||((!temp1)&&(!temp2)&&temp3);//It is a formula that can decide overflow.
	if(temp5)//judge overflow bit
		result->overflow = 1;
	else
		result->overflow = 0;
	result->result = sum;
	//printf("adc.result = %x, adc.carry = %x,adc.overflow = %x",result->result,result->carry_out,result->overflow);
	return result;
}

//word-aligned operation
unsigned align(unsigned x,unsigned y){
	unsigned m,n;
	m = x/y;
	n = m*y;
	return n;
}
#endif
