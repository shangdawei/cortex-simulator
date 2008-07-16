#ifndef _LOADSTOREMULTIPLE
#define _LOADSTOREMULTIPLE

#include "instruction.h"

typedef void (*func)(int);

struct LSMULTI{
	unsigned mask  :13;
	unsigned pass1 :1;
	unsigned m     :1;
	unsigned p     :1;
	unsigned rn    :4;
	unsigned l     :1;
	unsigned w     :1;
	unsigned pass2 :1;
	unsigned vu    :2;
	unsigned pass3 :2;
	unsigned pass4 :5;
}LdmDbEa,LdmIaFd,Pop,Push,StmDbFd,StmIaEa;

void* ls_multi[7]={
	(void *)ldm_db_ea,
	(void *)ldm_ia_fd,
	(void *)pop,
	(void *)push,
	(void *)stm_db_fd,
	(void *)stm_ia_ea,
	(void *)opcode_error,
};

#endif