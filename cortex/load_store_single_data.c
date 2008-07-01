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

//Load and store single data PC-relative.

void ldr_lit(int i){
	printf("	******ldr_lit\n");
}

void ldrb_lit(int i){
	printf("	******ldrb_lit\n");
}

void ldrsb_lit(int i){
	printf("	******ldrsb_lit\n");
}

void ldrh_lit(int i){
	printf("	******ldrh_lit\n");
}

void ldrsh_lit(int i){
	printf("	******ldrsh_lit\n");
}

//Load and store single data immediate offset.

void ldr_imm(int i){
	printf("	******ldr_imm\n");
}

void ldrb_imm(int i){
	printf("	******ldrb_imm\n");
}

void ldrsb_imm(int i){
	printf("	******ldrsb_imm\n");
}

void ldrh_imm(int i){
	printf("	******ldrh_imm\n");
}

void ldrsh_imm(int i){
	printf("	******ldrsh_imm\n");
}

void str_imm(int i){
	printf("	******str_imm\n");
}

void strb_imm(int i){
	printf("	******strb_imm\n");
}

void strh_imm(int i){
	printf("	******strh_imm\n");
}

//Load and store single data negative immediate offset.

void ldr_neg_imm(int i){
	printf("	******ldr_neg_imm\n");
}

void ldrb_neg_imm(int i){
	printf("	******ldrb_neg_imm\n");
}

void ldrsb_neg_imm(int i){
	printf("	******ldrsb_neg_imm\n");
}

void ldrh_neg_imm(int i){
	printf("	******ldrh_neg_imm\n");
}

void ldrsh_neg_imm(int i){
	printf("	******ldrsh_neg_imm\n");
}

void str_neg_imm(int i){
	printf("	******str_neg_imm\n");
}

void strb_neg_imm(int i){
	printf("	******strb_neg_imm\n");
}

void strh_neg_imm(int i){
	printf("	******strh_neg_imm\n");
}

//Load and store single data user privilege. 

void ldrt(int i){
	printf("	******ldrt\n");
}

void ldrbt(int i){
	printf("	******ldrbt\n");
}

void ldrsbt(int i){
	printf("	******ldrsbt\n");
}

void ldrht(int i){
	printf("	******ldrht\n");
}

void ldrsht(int i){
	printf("	******ldrsht\n");
}

void strt(int i){
	printf("	******strt\n");
}

void strbt(int i){
	printf("	******strbt\n");
}

void strht(int i){
	printf("	******strht\n");
}

//Load and store single data post-indexed.

void ldr_post(int i){
	printf("	******ldr_post\n");
}

void ldrb_post(int i){
	printf("	******ldrb_post\n");
}

void ldrsb_post(int i){
	printf("	******ldrsb_post\n");
}

void ldrh_post(int i){
	printf("	******ldrh_post\n");
}

void ldrsh_post(int i){
	printf("	******ldrsh_post\n");
}

void str_post(int i){
	printf("	******str_post\n");
}

void strb_post(int i){
	printf("	******strb_post\n");
}

void strh_post(int i){
	printf("	******strh_post\n");
}

//Load and store single data pre-indexed.

void ldr_pre(int i){
	printf("	******ldr_pre\n");
}

void ldrb_pre(int i){
	printf("	******ldrb_pre\n");
}

void ldrsb_pre(int i){
	printf("	******ldrsb_pre\n");
}

void ldrh_pre(int i){
	printf("	******ldrh_pre\n");
}

void ldrsh_pre(int i){
	printf("	******ldrsh_pre\n");
}

void str_pre(int i){
	printf("	******str_pre\n");
}

void strb_pre(int i){
	printf("	******strb_pre\n");
}

void strh_pre(int i){
	printf("	******strh_pre\n");
}

//Load and store single data register offset.

void ldr_reg(int i){
	printf("	******ldr_reg\n");
}

void ldrb_reg(int i){
	printf("	******ldrb_reg\n");
}

void ldrsb_reg(int i){
	printf("	******ldrsb_reg\n");
}

void ldrh_reg(int i){
	printf("	******ldrh_reg\n");
}

void ldrsh_reg(int i){
	printf("	******ldrsh_reg\n");
}

void str_reg(int i){
	printf("	******str_reg\n");
}

void strb_reg(int i){
	printf("	******strb_reg\n");
}

void strh_reg(int i){
	printf("	******strh_reg\n");
}

