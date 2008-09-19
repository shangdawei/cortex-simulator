/**
 *
 * This file is to define the function to handle the branch, miscellaneous control instructions
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#include "branch_misc.h" 
/**
 *
 *To define the struct to handle the instruction
 *
 */ 
void err_branch(int i)
{
	printf("the branch instruction 0x%x is error in this situation!",i);
}

void branch_instr(int instruction)
{
	func f_ptr;
	*((int *)(&branch)) = instruction;
	printf("branch instruction: 0x%x \n",instruction);
	printf("offset1 = %x",branch);
}

void branch_with_link(int instruction)
{}
void conditional_branch(int instruction)
{}
void move_to_status(int instruction)
{}
void no_op_hints(int instruction)
{}
void special_ctrl_operations(int instruction)
{}
void move_to_reg(int instruction)
{}
void branch_reserved(int instrution)
{}



void b_t3(int i)
{}
void b_t4(int i)
{}
void bl(int i)
{}
void mrs(int i)
{}
void msr(int i)
{}
/*
 *
 *Table for dealing with no operation and hint instructions
 *
 */
void nop(int i)
{}
void yield(int i)
{}
void wfe(int i)
{}
void wfi(int i)
{}
void sev(int i)
{}
void dbg(int i)
{}


/*
 *
 *Table for dealing with special control operations
 *
 */
void clrex(int i)
{}
void dsb(int i)
{}
void dmb(int i)
{}
void isb(int i)
{}