#ifndef _THUMBLOADSTORE
#define _THUMBLOADSTORE

#include "instruction.h"

typedef void (*func)(short);

//load from literal pool
//{0xF800, 0x4800, thumb_ldr_lit}
struct LDRFROMLITERALPOOL{
	unsigned imm8		:8;
	unsigned rd			:3;
	unsigned pass		:5;
}LdrFromLiteralPool;

//load/store register offset
//{0xF000, 0x5000, thumb_ld_st_reg_off}
struct LDRSTRREGOFFSET{
	unsigned rt			:3;
	unsigned rn			:3;
	unsigned rm			:3;
	unsigned op			:3;
	unsigned pass		:4;
}LdrStrRegOffset;

void* ldr_str_reg_off[8] = {
	(void*) thumb_str_reg,				//0
	(void*) thumb_strh_reg,				//1
	(void*) thumb_strb_reg,				//2
	(void*) thumb_ldrsb_reg,			//3
	(void*) thumb_ldr_reg,				//4
	(void*) thumb_ldrh_reg,				//5
	(void*) thumb_ldrb_reg,				//6
	(void*) thumb_ldrsh_reg,			//7
};

//load/store word/byte imm offset
//{0xE000, 0x6000, thumb_ld_st_word_byte_imm_off}
struct LDRSTRWORDBYTEIMMOFFSET{
	unsigned rt			:3;
	unsigned rn			:3;
	unsigned imm5		:5;
	unsigned l			:1;
	unsigned b			:1;
	unsigned pass		:3;
}LdrStrWordByteImmOffset;

void* ldr_str_word_byte_imm_off[4] = {
	(void*) thumb_str_imm,
	(void*) thumb_ldr_imm,
	(void*) thumb_strb_imm,
	(void*) thumb_ldrb_imm,
};

//load / store halfword imm offset
//{0xF000, 0x8000, thumb_ld_st_hw_imm_off}
struct LDRSTRHALFWORDIMMOFFSET{
	unsigned rt			:3;
	unsigned rn			:3;
	unsigned imm5		:5;
	unsigned l			:1;
	unsigned pass		:4;
}LdrStrHalfwordImmOffset;

void* ldr_str_halfword_imm_off[2] = {
	(void*) thumb_strh_imm,
	(void*) thumb_ldrh_imm,
};

//load from /store to stack
//{0xF000, 0x9000, thumb_ld_st_stack}
struct LDRSTRSTACK{
	unsigned imm8		:8;
	unsigned rt			:3;
	unsigned l			:1;
	unsigned pass		:4;
}LdrStrStack;

void* ldr_str_stack[2] = {
	(void*) thumb_str_sp_imm,
	(void*) thumb_ldr_sp_imm,
};

//load / store multiple
//{0xF000, 0xC000, thumb_ld_st_multiple}
struct LDRSTRMUL{
	unsigned reg_list	:8;
	unsigned rn			:3;
	unsigned l			:1;
	unsigned pass		:4;
}LdrStrMultiple;

void* ldr_str_multiple[2] = {
	(void*) thumb_stm,
	(void*) thumb_ldm,
};

//service (system) call
//{0xFF00, 0xDF00, thumb_service_call
struct SERVICECALL{
	unsigned imm8		:8;
	unsigned pass		:4;
	unsigned pass1		:4;
}SVCall;

//special data processing
//{0xFC00, 0x4400, thumb_sepecial_data_pro}
struct SPEDATAPRO{
	unsigned rdn		:3;
	unsigned rm			:4;
	unsigned dn			:1;
	unsigned op			:2;
	unsigned pass		:6;
}SpecialDataProcessing;

void* special_data_processing[4] = {
	(void*) thumb_add_reg,
	(void*) thumb_cmp_reg,
	(void*) thumb_mov_reg,
	(void*) thumb_branch_exchange_instruction_set,
};

#endif