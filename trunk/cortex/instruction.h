#ifndef _INSTRUCTION
#define _INSTRUCTION
#include <stdio.h>
#include "stdlib.h"
#include "register.h"
#include "memory.h"
#include "helper_procedures.h"
#include "operators_built-in_func.h"
#include <string.h>

/**
 *to handle the shift_rotate
 *
 */ 
struct RESULTCARRY* lsl_c(unsigned x,unsigned n);
struct RESULTCARRY* lsr_c(unsigned x,unsigned n);
struct RESULTCARRY* asr_c(int x,unsigned n);
int lsl(unsigned x,unsigned n);
int lsr(unsigned x,unsigned n);
int asr(int x,unsigned n);
struct RESULTCARRY* ror_c(unsigned x,unsigned n);
struct RESULTCARRY* rol_c(unsigned x,unsigned n);
struct RESULTCARRY* rrx_c(unsigned x,unsigned c_in);
int ror(unsigned x,unsigned n);
int rol(unsigned x,unsigned n);
int rrx(unsigned x,unsigned n);
struct RESULTCARRY* decodeImmShift(int type,int imm5);
struct RESULTCARRY* shift_c(int value,int type,int n,int carry_in);
int shift(int value,int type,int n,int carry_in);
//int min(int x,int y);
//int max(int x,int y);
struct RESULTCARRY* signedSatQ(int i,int j);
struct RESULTCARRY* unsignedSatQ(int i,int j);
int signedSat(int i,int j);
int unsignedSat(int i,int j);
/**
 *to handle the calculate
 *
 */ 
struct CALCULATECO* addwithcarry(unsigned m,unsigned n,unsigned carry_in);
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
struct RESULTCARRY* ThumbExpandImm12WithC(int i1,int i3,int i8);
int ThumbExpandImm12(int i1,int i3,int i8);
/**
 *
 *to handle the error message
 */ 
void error_message(int instruction);
void opcode_error(int i);
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
void add_with_carry_imm(int i);		//1010		10
void add_imm(int i);					//1000		8
void logical_and_imm(int i);			//0000		0
void bit_clear_imm(int i);			//0001		1
void compare_negative_imm(int i);	//11000		24
void compare_imm(int i);				//11101		13--29
void exclusive_or_imm(int i);		//0100		4
void move_imm(int i);				//10010		2---18
void move_negative_imm(int i);		//10011		3--19
void logical_or_not_imm(int i);		//0011		3
void logical_or_imm(int i);			//0010		2
void reverse_subtract_imm(int i);	//1110		14
void subtract_with_carry_imm(int i);	//1011		11
void subtract_imm(int i);			//1101		13
void test_equal_imm(int i);			//10100		4--20	
void test_imm(int i);				//10000		0--16

/*
 *
 *Table shared by (1)Add, substract plain 12 imm (2)move 16 imm
 *
 */ 
void add_wide_imm(int i);//000---0
void sub_wide_imm(int i);//110---6
void address_before_current(int i);//010---2
void address_after_current(int i);//100---4

void move_top_imm(int i);//100+1 --101---5
void move_wide_imm(int i);//000+1---001---1

/*
 *Table for bit field operations
 *
 */ 
void bit_field_clear(int i);// 011+100---7
void bit_field_inset(int i);// 011---3
void signed_bit_field_extract(int i);//010---2
void signed_lsl(int i);//000---0
void signed_asr(int i);//001---1
void unsinged_bit_field_extract(int i);//110---6
void unsigned_lsl(int i);//100----4
void unsigned_asr(int i);//101----5

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
void data_pro_nonimm_reserved(int instruction);

/*
 *
 *Table for data processing instructions with constant shift 
 *
 */							//Opcode
void and_reg(int i);		//00000		0
void bic_reg(int i);		//00001		1
void orr_reg(int i);		//00010		2
void orn_reg(int i);		//00011		3
void eor_reg(int i);		//00100		4
void add_reg(int i);		//01000		8
void adc_reg(int i);		//01010		10
void sbc_reg(int i);		//01011		11
void sub_reg(int i);		//01101		13
void rsb_reg(int i);		//01110		14
void tst_reg(int i);		//10000		0+16
void mov_reg(int i);		//10010		2+16
void mvn_reg(int i);		//10011		3+16
void teq_reg(int i);		//10100		4+16
void cmn_reg(int i);		//11000		8+16
void cmp_reg(int i);		//11101		13+16

/*
 *
 *Table for register-controlled shift instructions
 *
 */ 
void lsl_reg(int i);
void lsr_reg(int i);
void asr_reg(int i);
void ror_reg(int i);

/*
 *
 *Table for Sign and unsigned extend instructions with optional addition
 *
 */ 
void sxtb(int i);
void sxth(int i);
void uxtb(int i);
void uxth(int i);

/*
 *
 *Table for other three-register data processing instrucions 
 *
 */
void clz(int i);
void rbit(int i);
void rev(int i);
void rev16(int i);
void revsh(int i);

/*
 *
 *Table for 32-bit multiplies, with or without accumulate
 *
 */
void mla(int i);
void mls(int i);
void mul(int i);
/*
 *
 *Table for 64-bit multiply, multiply-accumulate, and divide instrucions 
 *
 */
void smull(int i);
void sdiv(int i);
void umull(int i);
void udiv(int i);
void smlal(int i);
void umlal(int i);

/**************************************************************************
 *
 *Data Processing instruction: no immediate operand
 *
 **************************************************************************/
void ls_single_pc_12m(int instruction);
void ls_single_rnadd_12m(int instruction);
void ls_single_rnminus_8m(int instruction);
void ls_single_rnpri_8m(int instruction);
void ls_single_rnpost_8m(int instruction);
void ls_single_rnpre_8m(int instruction);
void ls_single_rnshift(int instruction);
void ls_single_reserved1(int instruction);
void ls_single_reserved2(int instruction);
void ls_single_reserved3(int instruction);
/*
 *
 *Table for load and store single data PC-relative. 
 *
 */
void ldr_lit(int i);
void ldrb_lit(int i);
void ldrsb_lit(int i);
void ldrh_lit(int i);
void ldrsh_lit(int i);
/*
 *
 *Table for load and store single data immediate offset. 
 *
 */
void ldr_imm(int i);
void ldrb_imm(int i);
void ldrsb_imm(int i);
void ldrh_imm(int i);
void ldrsh_imm(int i);
void str_imm(int i);
void strb_imm(int i);
void strh_imm(int i);
/*
 *
 *Table for load and store single data negative immediate offset. 
 *
 */
void ldr_neg_imm(int i);
void ldrb_neg_imm(int i);
void ldrsb_neg_imm(int i);
void ldrh_neg_imm(int i);
void ldrsh_neg_imm(int i);
void str_neg_imm(int i);
void strb_neg_imm(int i);
void strh_neg_imm(int i);
/*
 *
 *Table for load and store single data user privilege. 
 *
 */
void ldrt(int i);
void ldrbt(int i);
void ldrsbt(int i);
void ldrht(int i);
void ldrsht(int i);
void strt(int i);
void strbt(int i);
void strht(int i);
/*
 *
 *Table for load and store single data post-indexed. 
 *
 */
void ldr_post(int i);
void ldrb_post(int i);
void ldrsb_post(int i);
void ldrh_post(int i);
void ldrsh_post(int i);
void str_post(int i);
void strb_post(int i);
void strh_post(int i);
/*
 *
 *Table for load and store single data pre-indexed. 
 *
 */
void ldr_pre(int i);
void ldrb_pre(int i);
void ldrsb_pre(int i);
void ldrh_pre(int i);
void ldrsh_pre(int i);
void str_pre(int i);
void strb_pre(int i);
void strh_pre(int i);
/*
 *
 *Table for load and store single data register offset. 
 *
 */
void ldr_reg(int i);
void ldrb_reg(int i);
void ldrsb_reg(int i);
void ldrh_reg(int i);
void ldrsh_reg(int i);
void str_reg(int i);
void strb_reg(int i);
void strh_reg(int i);
#endif

