#ifndef _ELF_LOADER
#define _ELF_LOADER
#include "elf.h"
#include <stdio.h>
#include "helper_procedures.h"
#include "memory.h"
#define DEBUG 0
//	Elf32_Ehdr.e_type
//
//	该成员确定该object的类型。
//
//		Name        Value  Meaning
//		====        =====  =======
#define	ET_NONE         0  //No file type
#define	ET_REL          1  //Relocatable file
#define	ET_EXEC         2  //Executable file
#define	ET_DYN          3  //Shared object file
#define ET_CORE         4  //Core file
#define	ET_LOPROC  0xff00  //Processor-specific
#define	ET_HIPROC  0xffff  //Processor-specific

//	Elf32_Phdr.p_type
//		Name             Value
//		====             =====
#define	PT_NULL              0
#define	PT_LOAD              1
#define	PT_DYNAMIC           2
#define	PT_INTERP            3
#define	PT_NOTE              4
#define	PT_SHLIB             5
#define	PT_PHDR              6
#define	PT_LOPROC   0x70000000
#define	PT_HIPROC   0x7fffffff

//	Elf32_Phdr.p_flags
//		Name             Value
//		====             =====
#define PF_X            (1 << 0)        /* Segment is executable */
#define PF_W            (1 << 1)        /* Segment is writable */
#define PF_R            (1 << 2)        /* Segment is readable */
#define PF_MASKOS       0x0ff00000      /* OS-specific */
#define PF_MASKPROC     0xf0000000      /* Processor-specific */
#define PROT_EXEC		(1 << 0)
#define	PROT_WRITE		(1 << 1)
#define PROT_READ		(1 << 2)

bool load_elf(char *p);
int initial_entry(int entry);
#endif
