#ifndef _INSTRUCTION
#define _INSTRUCTION
#include <stdio.h>
#include "register.h"
#include "memory.h"
#include <string.h>

/**
 *to handle the immediate decode
 *
 */ 
int decode_imm12(int i1,int i3,int i8);
int decode_imm16(int i1,int i4,int i3,int i8);
int decode_bitOperation(int i3,int i2,int i5);
int decode_shift(int i3,int i2);
/**
 *
 *to handle the error message
 */ 
void error_message(int instruction);
void opcode_error();
/*
 *
 *Data Processing instruction: immediatae, including bitfield and saturate
 *
 */ 
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
void add_with_carry(); //1010  10
void add();//1000		8
void logical_and();//0000		0
void bit_clear();//0001		1
void compare_negative();//11000---24
void compare();//11101		13--29
void exclusive_or();//0100		4
void move();//10010				2---18
void move_negative();//10011		3--19
void logical_or_not();//0011		3
void logical_or();//0010			2
void reverse_subtract();//1110	14
void subtract_with_carry();//1011	11
void subtract();//1101			13
void test_equal();//10100			4--20	
void test();//10000				0--16

/*
 *
 *Tabel shared by (1)Add, substract plain 12 imm (2)move 16 imm
 *
 */ 
void add_wide();//000---0
void sub_wide();//110---6
void address_before_current();//010---2
void address_after_current();//100---4

void move_top();//100+1 --101---5
void move_wide();//000+1---001---1

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












#endif

