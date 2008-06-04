#ifndef _INSTRUCTION
#define _INSTRUCTION
#include <stdio.h>
#include "register.h"
#include "memory.h"
#include <string.h>

/**
 *to handle the shift_rotate
 *
 */ 
int lsl_c(unsigned x,unsigned n);
int lsr_c(unsigned x,unsigned n);
int asr_c(int x,unsigned n);
int lsl(unsigned x,unsigned n);
int lsr(unsigned x,unsigned n);
int asr(int x,unsigned n);
int ror_c(unsigned x,unsigned n);
int rol_c(unsigned x,unsigned n);
int rrx_c(unsigned x,unsigned c_in);
int ror(unsigned x,unsigned n);
int rol(unsigned x,unsigned n);
int rrx(unsigned x,unsigned n);
int decodeImmShift(int type,int imm5);
int shift_c(int value,int type,int n,int carry_in);
int shift(int value,int type,int n,int carry_in);
int min(int x,int y);
int max(int x,int y);
int signedSatQ(int i,unsigned j);
int unsignedSatQ(int i,unsigned j);
int signedSat(int i,unsigned j);
int unsignedSat(int i,unsigned j);
/**
 *to handle the calculate
 *
 */ 
unsigned addwithcarry(unsigned m,unsigned n,unsigned carry_in);
unsigned align(unsigned x,unsigned y);
/**
 *to handle the immediate decode
 *
 */ 
int decode_imm5(int i3,int i2);
int decode_imm12(int i1,int i3,int i8);
int decode_imm16(int i1,int i4,int i3,int i8);
int decode_bitOperation(int i3,int i2,int i5);
int decode_shift(int i3,int i2);
int ThumbExpandImm12WithC(int i1,int i3,int i8);
int ThumbExpandImm12(int i1,int i3,int i8);
/**
 *
 *to handle the error message
 */ 
void error_message(int instruction);
void opcode_error();
void err_reg();
/**************************************************************************
 *
 *Data Processing instruction: immediatae, including bitfield and saturate
 *
 **************************************************************************/ 
void data_pro_modified_12m(int instuction);
void data_pro_mov_16m(int instuction);
void data_pro_add_12m(int instruction);
void data_pro_bitoperation(int instuction);
void data_pro_reserved(int instruction);
/*
 *
 *Table for data processing with 12 imm
 *
 */ 
void add_with_carry_imm();		//1010		10
void add_imm();					//1000		8
void logical_and_imm();			//0000		0
void bit_clear_imm();			//0001		1
void compare_negative_imm();	//11000		24
void compare_imm();				//11101		13--29
void exclusive_or_imm();		//0100		4
void move_imm();				//10010		2---18
void move_negative_imm();		//10011		3--19
void logical_or_not_imm();		//0011		3
void logical_or_imm();			//0010		2
void reverse_subtract_imm();	//1110		14
void subtract_with_carry_imm();	//1011		11
void subtract_imm();			//1101		13
void test_equal_imm();			//10100		4--20	
void test_imm();				//10000		0--16

/*
 *
 *Table shared by (1)Add, substract plain 12 imm (2)move 16 imm
 *
 */ 
void add_wide_imm();//000---0
void sub_wide_imm();//110---6
void address_before_current();//010---2
void address_after_current();//100---4

void move_top_imm();//100+1 --101---5
void move_wide_imm();//000+1---001---1

/*
 *Table for bit field operations
 *
 */ 
void bit_field_clear();// 011+100---7
void bit_field_inset();// 011---3
void signed_bit_field_extract();//010---2
void signed_lsl();//000---0
void signed_asr();//001---1
void unsinged_bit_field_extract();//110---6
void unsigned_lsl();//100----4
void unsigned_asr();//101----5

/**************************************************************************
 *
 *Data Processing instruction: no immediate operand
 *
 **************************************************************************/ 
void data_pro_con_shift(int instruction);
void reg_ctrl_shift(int instuction);
void sign_unsign_extend(int instruction);
void simd_add_sub(int instruction);
void other_three_reg_data_pro(int instruction);
void bit32_multiply_acc(int instruction);
void bit64_multiply(int instruction);

/*
 *
 *Table for data processing: constant shift
 *
 */ 
void and_reg();				//00000		0
void bic_reg();				//00001		1
void orr_reg();				//00010		2
void orn_reg();				//00011		3
void eor_reg();				//00100		4
void add_reg();				//01000		8
void adc_reg();				//01010		10
void sbc_reg();				//01011		11
void sub_reg();				//01101		13
void rsb_reg();				//01110		14
void tst_reg();				//10000		0+16
void mov_reg();				//10010		2+16
void mvn_reg();				//10011		3+16
void teq_reg();				//10100		4+16
void cmn_reg();				//11000		8+16
void cmp_reg();				//11101		13+16








#endif

