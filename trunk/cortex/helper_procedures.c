/**
 *
 * The functions described in this file are not part of the pseudo-code specification. They are helper
 * procedures and functions used by pseudo-code to perform useful architecture-specific jobs. Each has a brief
 * description and a pseudo-code prototype. Some have had a pseudo-code definition added.
 *
 */
#include "helper_procedures.h"

void ALUWritePC(int value)
{
/*
This procedure writes a value to the PC with the correct semantics for such a write by the ADD
(register) and MOV (register) data-processing instructions.
*/
	set_pc(value);
}

int ArchVersion()
{
//This function returns the major version number of the architecture.
	return 2;
}

bool Bad_Reg(int n){
//This function performs the check for the register numbers 13 and 15 that are disallowed for many Thumb register specifiers.
	return (n == 13 || n == 15);
}

bool InITBlock(){
//This function returns TRUE if execution is currently in an IT block and FALSE otherwise.
}

bool LastInITBlock(){
//This function returns TRUE if the current instruction is the last instruction in an IT block, and FALSE otherwise.
}

void LoadWritePC(int value){
//This procedure writes a value to the PC with BX-like interworking behavior for writes by load instructions.
	set_pc(value);
}
