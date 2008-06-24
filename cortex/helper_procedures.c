/**
 *
 * The functions described in this file are not part of the pseudo-code specification. They are helper
 * procedures and functions used by pseudo-code to perform useful architecture-specific jobs. Each has a brief
 * description and a pseudo-code prototype. Some have had a pseudo-code definition added.
 *
 */
#include "helper_procedures.h"

void ALUWritePC(value)
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

//bool bad_Reg(n)
//{
//	return false;
//}