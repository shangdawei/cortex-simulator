/**
 *
 * This file can deal with load/store byte or half word between memory and register.
 *
 */
#include "instruction.h"

int load_byte(int address,int s){
	int quotient,residual,result,temp;
	unsigned data;
	quotient = address / 4;
	data = get_memory(quotient);
	residual = address % 4;
	if(residual == 0){
		data = data & 0x000000FF;
		result = data;
	}
	else if(residual == 1){
		data = data & 0x0000FF00;
		result = data >> 8;
	}
	else if(residual == 2){
		data = data & 0x00FF0000;
		result = data >> 16;
	}
	else{
		data = data & 0xFF000000;
		result = data >> 24;
	}
	temp = result & 0x00000080;
	if(s && temp)
		result = result | 0xFFFFFF00;
	return result;
}

int load_half(int address,int s){
	int quotient,residual,result,temp;
	unsigned data;
	quotient = address / 2;
	data = get_memory(quotient);
	residual = address % 2;
	if(residual == 0){
		data = data & 0x0000FFFF;
		result = data;
	}
	else{
		data = data & 0xFFFF0000;
		result = data >> 16;
	}
	temp = result & 0x00008000;
	if(s && temp)
		result = result | 0xFFFF0000;
	return result;
}