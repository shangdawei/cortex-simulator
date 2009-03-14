#ifndef _CALCULATE
#define _CALCULATE
#include "instruction.h"
#include "stdio.h"

//simulate CPU based unit ----addition implemet

void addwithcarry(unsigned m,unsigned n,unsigned carry_in,struct CALCULATECO *result){
	unsigned sum,temp1,temp2,temp3,temp4,temp5;
	sum = m + n + carry_in;
	temp1 = (m & 0x7FFFFFFF) + (n & 0x7FFFFFFF) + carry_in;
	temp1 = temp1 >> 31;
	temp2 = m >> 31;
	temp3 = n >> 31;
	temp4 = temp1 + temp2 + temp3;
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
}

//word-aligned operation
unsigned align(unsigned x,unsigned y){
	unsigned m,n;
	m = x/y;
	n = m*y;
	return n;
}
#endif
