#ifndef _LOADSTOREEXCLUSIVE
#define _LOADSTOREEXCLUSIVE

#include <stdio.h>

struct LOADSTOREDOUBLE{
	unsigned imm8	:8;
	unsigned rt2	:4;
	unsigned rt		:4;
	unsigned rn		:4;
	unsigned l		:1;
	unsigned w		:1;
	unsigned pass	:1;
	unsigned u		:1;
	unsigned p		:1;
	unsigned pass2	:7;
}loadStoreDouble;

struct LOADSTOREEXCLUSIVE{
	unsigned imm8	:8;
	unsigned rd		:4;
	unsigned rt		:4;
	unsigned rn		:4;
	unsigned l		:1;
	unsigned pass	:11;
}loadStoreExclusive;

struct LOADSTOREBRANCH{
	unsigned rm		:4;
	unsigned op		:4;
	unsigned rt2	:4;
	unsigned rt		:4;
	unsigned rn		:4;
	unsigned l		:1;
	unsigned pass	:11;
}loadStoreBranch;

void load_store_exclusive(int instruction){
	(*(int *)(&loadStoreExclusive)) = instruction;
	printf("load store exclusive 0x%X \n", instruction);
	printf("imm8 is 0x%X \n", loadStoreExclusive.imm8);
	printf("Rd is 0x%X \n, ", loadStoreExclusive.rd);
	printf("Rt is 0x%X \n", loadStoreExclusive.rt);
	printf("Rn is 0x%X \n", loadStoreExclusive.rn);
	printf("L is 0x%X \n", loadStoreExclusive.l);
}

void load_store_branch(int instruction){
	(*(int *)(&loadStoreBranch)) = instruction;
	printf("load store branch 0x%X \n", instruction);
	printf("Rm is 0x%X \n, ", loadStoreBranch.rm);
	printf("OP is 0x%X \n, ", loadStoreBranch.op);
	printf("Rt2 is 0x%X \n", loadStoreBranch.rt2);
	printf("Rt is 0x%X \n, ", loadStoreBranch.rt);
	printf("Rn is 0x%X \n", loadStoreBranch.rn);
	printf("L is 0x%X \n", loadStoreBranch.l);
}

void load_store_double(int instruction){
	(*(int *)(&loadStoreDouble)) = instruction;
	printf("load store double 0x%X \n", instruction);
	printf("Imm8 is 0x%X \n ", loadStoreDouble.imm8);
	printf("Rt2 is 0x%X \n", loadStoreDouble.rt2);
	printf("Rt is 0x%X \n", loadStoreDouble.rt);
	printf("Rn is 0x%X \n", loadStoreDouble.rn);
	printf("L is 0x%X \n", loadStoreDouble.l);
	printf("W is 0x%X \n", loadStoreDouble.w);
	printf("U is 0x%X \n", loadStoreDouble.u);			
	printf("P is 0x%X \n", loadStoreDouble.p);
}
#endif
