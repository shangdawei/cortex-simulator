#ifndef _IMMEDIATEDECODE
#define _IMMEDIATEDECODE
#include "instruction.h"
int decode_imm12(int i1,int i3,int i8){
	int i = (i1<<11)+(i3<<8)+i8;
	return i;
}
int decode_imm16(int i1,int i4,int i3,int i8){
	int i =(i1<<15)+(i4<<11)+(i3<<8)+i8;
	return i;
}

int decode_bitOperation(int i3,int i2,int i5){
	int i=(i3<<7)+(i2<<5)+i5;
	return i;
}

int decode_shift(int i3,int i2){
	int i=(i3<<2)+i2;
	return i;
}
#endif
