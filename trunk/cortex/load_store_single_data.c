#include "stdio.h"
#include "load_store_single_data.h"
#include "memory.h"
#include "instruction.h"

void ls_single_pc_12m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSinglePc)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSinglePc.rn);
	printf("Rt: 0x%x \n", LsSinglePc.rt);
	if(LsSinglePc.s == 0 && LsSinglePc.size == 2)
		index = 0;
	else if(LsSinglePc.s == 0 && LsSinglePc.size == 0)
		index = 1;
	else if(LsSinglePc.s == 1 && LsSinglePc.size == 0)
		index = 2;
	else if(LsSinglePc.s == 0 && LsSinglePc.size == 1)
		index = 3;
	else if(LsSinglePc.s == 1 && LsSinglePc.size == 1)
		index = 4;
	else
		index = 5;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_pc[index];
	f_ptr(instruction);
}

void ls_single_rnadd_12m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnAdd)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnAdd.rn);
	printf("Rt: 0x%x \n", LsSingleRnAdd.rt);
	if(LsSingleRnAdd.s == 0 && LsSingleRnAdd.size == 2 && LsSingleRnAdd.l == 1)
		index = 0;
	else if(LsSingleRnAdd.s == 0 && LsSingleRnAdd.size == 0 && LsSingleRnAdd.l == 1)
		index = 1;
	else if(LsSingleRnAdd.s == 1 && LsSingleRnAdd.size == 0 && LsSingleRnAdd.l == 1)
		index = 2;
	else if(LsSingleRnAdd.s == 0 && LsSingleRnAdd.size == 1 && LsSingleRnAdd.l == 1)
		index = 3;
	else if(LsSingleRnAdd.s == 1 && LsSingleRnAdd.size == 1 && LsSingleRnAdd.l == 1)
		index = 4;
	else if(LsSingleRnAdd.s == 0 && LsSingleRnAdd.size == 2 && LsSingleRnAdd.l == 0)
		index = 5;
	else if(LsSingleRnAdd.s == 0 && LsSingleRnAdd.size == 0 && LsSingleRnAdd.l == 0)
		index = 6;
	else if(LsSingleRnAdd.s == 0 && LsSingleRnAdd.size == 1 && LsSingleRnAdd.l == 0)
		index = 7;
	else
		index = 8;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_rnadd[index];
	f_ptr(instruction);

}

void ls_single_rnminus_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnMinus)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnMinus.rn);
	printf("Rt: 0x%x \n", LsSingleRnMinus.rt);
	if(LsSingleRnMinus.s == 0 && LsSingleRnMinus.size == 2 && LsSingleRnMinus.l == 1)
		index = 0;
	else if(LsSingleRnMinus.s == 0 && LsSingleRnMinus.size == 0 && LsSingleRnMinus.l == 1)
		index = 1;
	else if(LsSingleRnMinus.s == 1 && LsSingleRnMinus.size == 0 && LsSingleRnMinus.l == 1)
		index = 2;
	else if(LsSingleRnMinus.s == 0 && LsSingleRnMinus.size == 1 && LsSingleRnMinus.l == 1)
		index = 3;
	else if(LsSingleRnMinus.s == 1 && LsSingleRnMinus.size == 1 && LsSingleRnMinus.l == 1)
		index = 4;
	else if(LsSingleRnMinus.s == 0 && LsSingleRnMinus.size == 2 && LsSingleRnMinus.l == 0)
		index = 5;
	else if(LsSingleRnMinus.s == 0 && LsSingleRnMinus.size == 0 && LsSingleRnMinus.l == 0)
		index = 6;
	else if(LsSingleRnMinus.s == 0 && LsSingleRnMinus.size == 1 && LsSingleRnMinus.l == 0)
		index = 7;
	else
		index = 8;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_rnminus[index];
	f_ptr(instruction);

}

void ls_single_rnpri_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnPri)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnPri.rn);
	printf("Rt: 0x%x \n", LsSingleRnPri.rt);
	if(LsSingleRnPri.s == 0 && LsSingleRnPri.size == 2 && LsSingleRnPri.l == 1)
		index = 0;
	else if(LsSingleRnPri.s == 0 && LsSingleRnPri.size == 0 && LsSingleRnPri.l == 1)
		index = 1;
	else if(LsSingleRnPri.s == 1 && LsSingleRnPri.size == 0 && LsSingleRnPri.l == 1)
		index = 2;
	else if(LsSingleRnPri.s == 0 && LsSingleRnPri.size == 1 && LsSingleRnPri.l == 1)
		index = 3;
	else if(LsSingleRnPri.s == 1 && LsSingleRnPri.size == 1 && LsSingleRnPri.l == 1)
		index = 4;
	else if(LsSingleRnPri.s == 0 && LsSingleRnPri.size == 2 && LsSingleRnPri.l == 0)
		index = 5;
	else if(LsSingleRnPri.s == 0 && LsSingleRnPri.size == 0 && LsSingleRnPri.l == 0)
		index = 6;
	else if(LsSingleRnPri.s == 0 && LsSingleRnPri.size == 1 && LsSingleRnPri.l == 0)
		index = 7;
	else
		index = 8;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_rnpri[index];
	f_ptr(instruction);

}

void ls_single_rnpost_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnPost)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnPost.rn);
	printf("Rt: 0x%x \n", LsSingleRnPost.rt);
	if(LsSingleRnPost.s == 0 && LsSingleRnPost.size == 2 && LsSingleRnPost.l == 1)
		index = 0;
	else if(LsSingleRnPost.s == 0 && LsSingleRnPost.size == 0 && LsSingleRnPost.l == 1)
		index = 1;
	else if(LsSingleRnPost.s == 1 && LsSingleRnPost.size == 0 && LsSingleRnPost.l == 1)
		index = 2;
	else if(LsSingleRnPost.s == 0 && LsSingleRnPost.size == 1 && LsSingleRnPost.l == 1)
		index = 3;
	else if(LsSingleRnPost.s == 1 && LsSingleRnPost.size == 1 && LsSingleRnPost.l == 1)
		index = 4;
	else if(LsSingleRnPost.s == 0 && LsSingleRnPost.size == 2 && LsSingleRnPost.l == 0)
		index = 5;
	else if(LsSingleRnPost.s == 0 && LsSingleRnPost.size == 0 && LsSingleRnPost.l == 0)
		index = 6;
	else if(LsSingleRnPost.s == 0 && LsSingleRnPost.size == 1 && LsSingleRnPost.l == 0)
		index = 7;
	else
		index = 8;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_rnpost[index];
	f_ptr(instruction);

}

void ls_single_rnpre_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnPre)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnPre.rn);
	printf("Rt: 0x%x \n", LsSingleRnPre.rt);
	if(LsSingleRnPre.s == 0 && LsSingleRnPre.size == 2 && LsSingleRnPre.l == 1)
		index = 0;
	else if(LsSingleRnPre.s == 0 && LsSingleRnPre.size == 0 && LsSingleRnPre.l == 1)
		index = 1;
	else if(LsSingleRnPre.s == 1 && LsSingleRnPre.size == 0 && LsSingleRnPre.l == 1)
		index = 2;
	else if(LsSingleRnPre.s == 0 && LsSingleRnPre.size == 1 && LsSingleRnPre.l == 1)
		index = 3;
	else if(LsSingleRnPre.s == 1 && LsSingleRnPre.size == 1 && LsSingleRnPre.l == 1)
		index = 4;
	else if(LsSingleRnPre.s == 0 && LsSingleRnPre.size == 2 && LsSingleRnPre.l == 0)
		index = 5;
	else if(LsSingleRnPre.s == 0 && LsSingleRnPre.size == 0 && LsSingleRnPre.l == 0)
		index = 6;
	else if(LsSingleRnPre.s == 0 && LsSingleRnPre.size == 1 && LsSingleRnPre.l == 0)
		index = 7;
	else
		index = 8;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_rnpre[index];
	f_ptr(instruction);

}

void ls_single_rnshift(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnShift)) = instruction;
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnShift.rn);
	printf("Rt: 0x%x \n", LsSingleRnShift.rt);
	if(LsSingleRnShift.s == 0 && LsSingleRnShift.size == 2 && LsSingleRnShift.l == 1)
		index = 0;
	else if(LsSingleRnShift.s == 0 && LsSingleRnShift.size == 0 && LsSingleRnShift.l == 1)
		index = 1;
	else if(LsSingleRnShift.s == 1 && LsSingleRnShift.size == 0 && LsSingleRnShift.l == 1)
		index = 2;
	else if(LsSingleRnShift.s == 0 && LsSingleRnShift.size == 1 && LsSingleRnShift.l == 1)
		index = 3;
	else if(LsSingleRnShift.s == 1 && LsSingleRnShift.size == 1 && LsSingleRnShift.l == 1)
		index = 4;
	else if(LsSingleRnShift.s == 0 && LsSingleRnShift.size == 2 && LsSingleRnShift.l == 0)
		index = 5;
	else if(LsSingleRnShift.s == 0 && LsSingleRnShift.size == 0 && LsSingleRnShift.l == 0)
		index = 6;
	else if(LsSingleRnShift.s == 0 && LsSingleRnShift.size == 1 && LsSingleRnShift.l == 0)
		index = 7;
	else
		index = 8;
	printf("index is %d", index);
	f_ptr=(void *)ls_single_rnsh[index];
	f_ptr(instruction);

}

void ls_single_reserved1(int instruction){
	printf("ls_single_reserved1: 0x%X \n",instruction);

}

void ls_single_reserved2(int instruction){
	printf("ls_single_reserved2: 0x%X \n",instruction);

}

void ls_single_reserved3(int instruction){
	printf("ls_single_reserved3: 0x%X \n",instruction);

}