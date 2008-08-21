/**
 *
 * 
 * 
 * 
 *
 */
#ifndef _THUMBMISC
#define _THUMBMISC
#include <stdio.h>
#include "instruction.h"

/**
 *
 *To define the table for execute for these instructions
 */ 
typedef void (*func)(int);

struct BRANCHEXCHANGEINSTRUCTIONSET {
	unsigned pass1:3;
	unsigned rm   :4;
	unsigned l    :1;
	unsigned pass2:2;
	unsigned pass3:6;
} branchExchangeInstructionSet;

struct ADDTOSPORPC {
	unsigned imm8	:8;
	unsigned rd		:3;
	unsigned sp  	:1;
	unsigned pass1	:4;
} addToSpOrPc;

struct CONDITIONALBRANCH {
	unsigned imm8	:8;
	unsigned cond	:4;
	unsigned pass1	:4;
} conditionalBranch;

struct SERVICECALL {
	unsigned imm8	:8;
	unsigned pass1	:4;
	unsigned pass2	:4;
} serviceCall;

struct UNCONDITIONALBRANCH {
	unsigned imm11	:11;
	unsigned pass1	:5;
} unconditionalBranch;

struct ADJUSTSTACKPOINTER {
	unsigned imm7	:7;
	unsigned opc	:1;
	unsigned pass1	:4;
	unsigned pass2	:4;
} adjustStackPointer;

struct SIGNZEROEXTEND {
	unsigned rd		:3;
	unsigned rm		:3;
	unsigned opc	:2;
	unsigned pass1	:4;
	unsigned pass2	:4;
} signZeroExtend;

struct COMPAREANDBRANCH {
	unsigned rn		:3;
	unsigned imm5	:5;
	unsigned pass1	:1;
	unsigned i		:1;
	unsigned pass2	:1;
	unsigned n		:1;
	unsigned pass3	:4;
} compareAndBranch;

struct PUSHPOPREGISTERLIST {
	unsigned regList:8;
	unsigned r		:1;
	unsigned pass1	:2;
	unsigned l		:1;
	unsigned pass2	:4;
} pushPopRegisterList;

struct CHANGEPROCESSORSTATE {
	unsigned f		:1;
	unsigned i		:1;
	unsigned pass1	:1;
	unsigned pass2	:1;
	unsigned im		:1;
	unsigned pass3	:7;
	unsigned pass4	:4;
} changeProcessorState;

struct REVERSEBYTES {
	unsigned rd		:3;
	unsigned rm		:3;
	unsigned opc	:2;
	unsigned pass1	:4;
	unsigned pass2	:4;
} reverseBytes;

struct SOFTWAREBREAKPOINT {
	unsigned imm8	:8;
	unsigned pass1	:4;
	unsigned pass2	:4;
} softwareBreakpoint;

struct IFTHENINSTRUCTION {
	unsigned mask	:4;
	unsigned cond	:4;
	unsigned pass1	:8;
} ifThenInstruction;

struct NOPCOMPATIBLEHINTS {
	unsigned pass1	:4;
	unsigned hint	:4;
	unsigned pass2	:8;
} nopCompatibleHints;



void* branch_exchange_instruction_set[2] = {
	(void *)thumb_branch_and_exchange,				//0b0
	(void *)thumb_branch_with_link_and_exchange,	//0b1
};

void* add_to_sp_or_pc[2] = {
	(void *)thumb_add_to_pc,	//0b0
	(void *)thumb_add_to_sp,	//0b1
};

void* adjust_stack_pointer[2] = {
	(void *)thumb_increment_stack_pointer,	//0b0
	(void *)thumb_decrement_stack_pointer,	//0b1
};

void* sign_zero_extend[4] = {
	(void *)thumb_signed_extend_halfword,		//0b00
	(void *)thumb_signed_extend_byte,			//0b01
	(void *)thumb_unsigned_extend_halfword,		//0b10
	(void *)thumb_unsigned_extned_byte,			//0b11
};

void* compare_and_branch[2] = {
	(void *)thumb_compare_and_branch_on_zero,		//0b0
	(void *)thumb_compare_and_branch_on_nonzero,	//0b1
};

void* push_pop_register_list[2] = {
	(void *)thumb_push_register,	//0b0
	(void *)thumb_pop_register,		//0b1
};

void* reverse_bytes[4] = {
	(void *)thumb_byte_reverse_word,			//0b00
	(void *)thumb_byte_reverse_packed_halfword,	//0b01
	(void *)thumb_opcode_error,
	(void *)thumb_byte_reverse_signed_halfword,	//0b11
};

void* nop_compatible_hints[16] = {
	(void *)thumb_no_operation,			//0b0000
	(void *)thumb_yield,				//0b0001
	(void *)thumb_wait_for_event,		//0b0010
	(void *)thumb_wait_for_interrupt,	//0b0011
	(void *)thumb_send_event,			//0b0100
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
	(void *)thumb_opcode_error,
};
#endif
