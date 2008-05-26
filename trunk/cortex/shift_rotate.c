#ifndef _SHIFT_ROTATE
#define _SHIFT_ROTATE

#include "stdio.h"
#include "instruction.h"

int lsl_c(int x,unsigned n){
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

int lsr_c(int x,unsigned n){
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

int lsl(int x,unsigned n){
	unsigned result;
	if(n == 0)
		result = x;
	else
		result = lsl_c(x,n);
	return result;
}

int lsr(int x,unsigned n){
	unsigned result;
	if(n == 0)
		result = x;
	else
		result = lsr_c(x,n);
	return result;
}

int ror_c(int x,unsigned n){
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
#endif
