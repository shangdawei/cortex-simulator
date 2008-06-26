#ifndef _IMMEDIATE_DECODE
#define _IMMEDIATE_DECODE

int decode_imm12(int i1,int i3,int i8);
int decode_imm16(int i1,int i4,int i3,int i8);
int decode_bitOperation(int i3,int i2,int i5);
int decode_shift(int i3,int i2);
struct RESULTCARRY* ThumbExpandImm12WithC(int i1,int i3,int i8);
int ThumbExpandImm12(int i1,int i3,int i8);

#endif
