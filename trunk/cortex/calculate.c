#ifndef _CALCULATE
#define _CALCULATE
#include "instruction.h"
#include "stdio.h"

//simulate CPU based unit ----addition implemet

unsigned addwithcarry(unsigned m,unsigned n,unsigned carry_in){
	unsigned sum,temp1,temp2,temp3,temp4,temp5;
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
		set_calculate_carry();
	else
		cle_calculate_carry();
	temp5 = (temp1&&temp2&&(!temp3))||((!temp1)&&(!temp2)&&temp3);//It is a formula that can decide overflow.
	if(temp5)//judge overflow bit
		set_calculate_overflow();
	else
		cle_calculate_overflow();
	return sum;
}
#endif
