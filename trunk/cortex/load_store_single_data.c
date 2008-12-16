#include "stdio.h"
#include "load_store_single_data.h"
#include "memory.h"
#include "instruction.h"

void ls_single_pc_12m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSinglePc)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSinglePc.rn);
	printf("Rt: 0x%x \n", LsSinglePc.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_pc[index];
	f_ptr(instruction);
}

void ls_single_rnadd_12m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnAdd)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnAdd.rn);
	printf("Rt: 0x%x \n", LsSingleRnAdd.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_rnadd[index];
	f_ptr(instruction);

}

void ls_single_rnminus_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnMinus)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnMinus.rn);
	printf("Rt: 0x%x \n", LsSingleRnMinus.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_rnminus[index];
	f_ptr(instruction);

}

void ls_single_rnpri_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnPri)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnPri.rn);
	printf("Rt: 0x%x \n", LsSingleRnPri.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_rnpri[index];
	f_ptr(instruction);

}

void ls_single_rnpost_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnPost)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnPost.rn);
	printf("Rt: 0x%x \n", LsSingleRnPost.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_rnpost[index];
	f_ptr(instruction);

}

void ls_single_rnpre_8m(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnPre)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnPre.rn);
	printf("Rt: 0x%x \n", LsSingleRnPre.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_rnpre[index];
	f_ptr(instruction);

}

void ls_single_rnshift(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LsSingleRnShift)) = instruction;
#if DEBUG
	printf("ls_single_pc_12m: 0x%X \n",instruction);
	printf("Rn: 0x%x \n", LsSingleRnShift.rn);
	printf("Rt: 0x%x \n", LsSingleRnShift.rt);
#endif
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
	//printf("index is %d", index);
	f_ptr=(void *)ls_single_rnsh[index];
	f_ptr(instruction);

}

void ls_single_reserved1(int instruction){
	//printf("ls_single_reserved1: 0x%X \n",instruction);

}

void ls_single_reserved2(int instruction){
	//printf("ls_single_reserved2: 0x%X \n",instruction);

}

void ls_single_reserved3(int instruction){
	//printf("ls_single_reserved3: 0x%X \n",instruction);

}

//Load and store single data PC-relative.

void ldr_lit(int i){
	int rt,imm32,base,address,address1,result;
	*((int *)(&LsSinglePc)) = i;
	rt = LsSinglePc.rt;
	imm32 = LsSinglePc.imm12;
	if(rt == 15 && InITBlock() && !LastInITBlock())
		printf("	it is unpredictable!");
	else{
		base = align(get_pc(),4);
		if(LsSinglePc.u == 1)
			address = base + imm32;
		else{
			if(base<imm32){
				printf("error\n");
				return;
			}
			address = base - imm32;                   
		}
		address1 = address & 0x00000003;
		if(rt == 15)
			if(address1 != 0)
				printf("	it is unpredictable!");
			else
				LoadWritePC(get_MemU(address,4));
		else{
			result = get_MemU(address,4);
			set_general_register(rt,result);
		}
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldr_lit\n");
	}
}

void ldrb_lit(int i){
	int rt,imm32,base,address,result;
	*((int *)(&LsSinglePc)) = i;
	rt = LsSinglePc.rt;
	imm32 = LsSinglePc.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");                //有问题，此处与数据手册上所说的不符
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		base = align(get_pc(),4);
		if(LsSinglePc.u == 1)
			address = base + imm32;
		else{
			if(base<imm32){
				printf("error\n");
				return;
			}
			address = base - imm32;                   
		}
		result = get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrb_lit\n");
	}
}

void ldrsb_lit(int i){
	int rt,imm32,base,address,result,temp;
	*((int *)(&LsSinglePc)) = i;
	rt = LsSinglePc.rt;
	imm32 = LsSinglePc.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");//有问题，此处与数据手册上所说的不符
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		base = align(get_pc(),4);
		if(LsSinglePc.u == 1)
			address = base + imm32;
		else{
			if(base<imm32){
				printf("error\n");
				return;
			}
			address = base - imm32;                   
		}
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSinglePc.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsb_lit\n");
	}
}

void ldrh_lit(int i){
	int rt,imm32,base,address,result;
	*((int *)(&LsSinglePc)) = i;
	rt = LsSinglePc.rt;
	imm32 = LsSinglePc.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");   ////有问题，此处与数据手册上所说的不符
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		base = align(get_pc(),4);
		if(LsSinglePc.u == 1)
			address = base + imm32;
		else{
			if(base<imm32){
				printf("error\n");
				return;
			}
			address = base - imm32;                   
		}
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrh_lit\n");
	}
}

void ldrsh_lit(int i){
	int rt,imm32,base,address,result,temp;
	*((int *)(&LsSinglePc)) = i;
	rt = LsSinglePc.rt;
	imm32 = LsSinglePc.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");       //有问题，此处与数据手册上所说的不符
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		base = align(get_pc(),4);
		if(LsSinglePc.u == 1)
			address = base + imm32;
		else{
			if(base<imm32){
				printf("error\n");
				return;
			}
			address = base - imm32;                   
		}
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSinglePc.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsh_lit\n");
	}
}

//Load and store single data immediate offset.

void ldr_imm(int i){
	int rt,rn,imm32,address,address1,result;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rt == 15 && InITBlock() && !LastInITBlock())
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		address1 = address & 0x00000003;
		if(rt == 15)
			if(address1 != 0)
				printf("	it is unpredictable!");
			else
				LoadWritePC(get_MemU(address,4));
		else{
			result = get_MemU(address,4);
			set_general_register(rt,result);
		}
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldr_imm\n");
	}
}

void ldrb_imm(int i){
	int rt,imm32,rn,address,result;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result =  get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrb_imm\n");
	}
}

void ldrsb_imm(int i){
	int rt,imm32,rn,address,result,temp;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSingleRnAdd.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsb_imm\n");
	}
}

void ldrh_imm(int i){
	int rt,imm32,rn,address,result;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrh_imm\n");
	}
}

void ldrsh_imm(int i){
	int rt,imm32,rn,address,result,temp;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(rt == 13)
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSingleRnAdd.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsh_imm\n");
	}
}

void str_imm(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rn == 15)
		printf("	it is undefined!");
	else if(rt == 15)
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		//printf("	%X",address);
		result = get_general_register(rt);
		//printf("	%X",result);
		set_MemU(address,4,result);
		//printf("	Memory unit is %X",get_MemU(address,4));
		//printf("	******str_imm\n");
	}
}

void strb_imm(int i){
	int rt,rn,imm32,address;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		set_MemU(address,1,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,1));
		//printf("	******strb_imm\n");
	}
}

void strh_imm(int i){
	int rt,rn,imm32,address;
	*((int *)(&LsSingleRnAdd)) = i;
	rt = LsSingleRnAdd.rt;
	rn = LsSingleRnAdd.rn;
	imm32 = LsSingleRnAdd.imm12;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		set_MemU(address,2,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,2));
		//printf("	******strh_imm\n");
	}
}

//Load and store single data negative immediate offset.

void ldr_neg_imm(int i){
	int rt,rn,imm32,address,address1,result;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rt == 15 && InITBlock() && !LastInITBlock())
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		address1 = address & 0x00000003;
		if(rt == 15)
			if(address1 != 0)
				printf("	it is unpredictable!");
			else
				LoadWritePC(get_MemU(address,4));
		else{
			result = get_MemU(address,4);
			set_general_register(rt,result);
		}
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldr_neg_imm\n");
	}
}

void ldrb_neg_imm(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(Bad_Reg(rt) || (LsSingleRnMinus.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		result = get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrb_neg_imm\n");
	}
}

void ldrsb_neg_imm(int i){
	int rt,rn,imm32,address,result,temp;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(Bad_Reg(rt) || (LsSingleRnMinus.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSingleRnMinus.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsb_neg_imm\n");
	}
}

void ldrh_neg_imm(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(Bad_Reg(rt) || (LsSingleRnMinus.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrh_neg_imm\n");
	}
}

void ldrsh_neg_imm(int i){
	int rt,rn,imm32,address,result,temp;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rt == 15)
		printf("	it is error in this situation!");
	else if(Bad_Reg(rt) || (LsSingleRnMinus.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSingleRnMinus.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsh_neg_imm\n");
	}
}

void str_neg_imm(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(rt == 15)
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		result = get_general_register(rt);
		set_MemU(address,4,result);
		//printf("	Memory unit is %X",get_MemU(address,4));
		//printf("	******str_neg_imm\n");
	}
}

void strb_neg_imm(int i){
	int rt,rn,imm32,address;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || (LsSingleRnMinus.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		set_MemU(address,1,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,1));
		//printf("	******strb_neg_imm\n");
	}
}

void strh_neg_imm(int i){
	int rt,rn,imm32,address;
	*((int *)(&LsSingleRnMinus)) = i;
	rt = LsSingleRnMinus.rt;
	rn = LsSingleRnMinus.rn;
	imm32 = LsSingleRnMinus.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || (LsSingleRnMinus.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) - imm32;
		set_MemU(address,2,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,2));
		//printf("	******strh_neg_imm\n");
	}
}

//Load and store single data user privilege. 

void ldrt(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,4);//didn't consider MemU_unpriv!
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrt\n");
	}
}

void ldrbt(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrbt\n");
	}
}

void ldrsbt(int i){
	int rt,rn,imm32,address,result,temp;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSingleRnPri.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsbt\n");
	}
}

void ldrht(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrht\n");
	}
}

void ldrsht(int i){
	int rt,rn,imm32,address,result,temp;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSingleRnPri.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsht\n");
	}
}

void strt(int i){
	int rt,rn,imm32,address,result;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		result = get_general_register(rt);
		set_MemU(address,4,result);
		//printf("	Memory unit is %X",get_MemU(address,4));
		//printf("	******strt\n");
	}
}

void strbt(int i){
	int rt,rn,imm32,address;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		set_MemU(address,1,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,1));
		//printf("	******strbt\n");
	}
}

void strht(int i){
	int rt,rn,imm32,address;
	*((int *)(&LsSingleRnPri)) = i;
	rt = LsSingleRnPri.rt;
	rn = LsSingleRnPri.rn;
	imm32 = LsSingleRnPri.imm8;
	if(Bad_Reg(rt))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + imm32;
		set_MemU(address,2,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,2));
		//printf("	******strht\n");
	}
}

//Load and store single data post-indexed.

void ldr_post(int i){
	int rt,rn,imm32,address,offset_addr,address1,result;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(LsSingleRnPost.pass1 == 1 && rt == rn)
		printf("	it is unpredictable!");
	else if(rt == 15 && InITBlock() && !LastInITBlock())
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		address1 = address & 0x00000003;
		if(rt == 15)
			if(address1 != 0)
				printf("	it is unpredictable!");
			else
				LoadWritePC(get_MemU(address,4));
		else{
			result = get_MemU(address,4);
			set_general_register(rt,result);
		}
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldr_post\n");
	}
}

void ldrb_post(int i){
	int rt,rn,imm32,address,offset_addr,result;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPost.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		result = get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrb_post\n");
	}
}

void ldrsb_post(int i){
	int rt,rn,imm32,address,offset_addr,result,temp;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPost.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSingleRnPost.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsb_post\n");
	}
}

void ldrh_post(int i){
	int rt,rn,imm32,address,offset_addr,result;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPost.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrh_post\n");
	}
}

void ldrsh_post(int i){
	int rt,rn,imm32,address,offset_addr,result,temp;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPost.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSingleRnPost.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsh_post\n");
	}
}

void str_post(int i){
	int rt,rn,imm32,address,offset_addr,result;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(rt == 15 || rn == rt)
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		result = get_general_register(rt);
		set_MemU(address,4,result);
		//printf("	Memory unit is %X",get_MemU(address,4));
		//printf("	******str_post\n");
	}
}

void strb_post(int i){
	int rt,rn,imm32,address,offset_addr;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || rt == rn)
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		set_MemU(address,1,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,1));
		//printf("	******strb_post\n");
	}
}

void strh_post(int i){
	int rt,rn,imm32,address,offset_addr;
	*((int *)(&LsSingleRnPost)) = i;
	rt = LsSingleRnPost.rt;
	rn = LsSingleRnPost.rn;
	imm32 = LsSingleRnPost.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || rt == rn)
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPost.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = get_general_register(rn);
		set_general_register(rn,offset_addr);
		set_MemU(address,2,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,2));
		//printf("	******strh_post\n");
	}
}

//Load and store single data pre-indexed.

void ldr_pre(int i){
	int rt,rn,imm32,address,offset_addr,address1,result;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(LsSingleRnPre.pass1 == 1 && rt == rn)
		printf("	it is unpredictable!");
	else if(rt == 15 && InITBlock() && !LastInITBlock())
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		address1 = address & 0x00000003;
		if(rt == 15)
			if(address1 != 0)
				printf("	it is unpredictable!");
			else
				LoadWritePC(get_MemU(address,4));
		else{
			result = get_MemU(address,4);
			set_general_register(rt,result);
		}
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldr_pre\n");
	}
}

void ldrb_pre(int i){
	int rt,rn,imm32,address,offset_addr,result;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPre.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		result = get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrb_pre\n");
	}
}

void ldrsb_pre(int i){
	int rt,rn,imm32,address,offset_addr,result,temp;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPre.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSingleRnPre.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsb_pre\n");
	}
}

void ldrh_pre(int i){
	int rt,rn,imm32,address,offset_addr,result;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPre.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrh_pre\n");
	}
}

void ldrsh_pre(int i){
	int rt,rn,imm32,address,offset_addr,result,temp;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(Bad_Reg(rt) || (LsSingleRnPre.pass1 == 1 && rt == rn))
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSingleRnPre.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rn = %X",get_general_register(rn));
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsh_pre\n");
	}
}

void str_pre(int i){
	int rt,rn,imm32,address,offset_addr,result;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(rt == 15 || rn == rt)
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		result = get_general_register(rt);
		set_MemU(address,4,result);
		//printf("	Memory unit is %X",get_MemU(address,4));
		//printf("	******str_pre\n");
	}
}

void strb_pre(int i){
	int rt,rn,imm32,address,offset_addr;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || rt == rn)
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		set_MemU(address,1,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,1));
		//printf("	******strb_pre\n");
	}
}

void strh_pre(int i){
	int rt,rn,imm32,address,offset_addr;
	*((int *)(&LsSingleRnPre)) = i;
	rt = LsSingleRnPre.rt;
	rn = LsSingleRnPre.rn;
	imm32 = LsSingleRnPre.imm8;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || rt == rn)
		printf("	it is unpredictable!");
	else{
		if(LsSingleRnPre.pass2 == 1)
			offset_addr = get_general_register(rn) + imm32;
		else
			offset_addr = get_general_register(rn) - imm32;
		address = offset_addr;
		set_general_register(rn,offset_addr);
		set_MemU(address,2,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,2));
		//printf("	******strh_pre\n");
	}
}

//Load and store single data register offset.

void ldr_reg(int i){
	int rt,rn,rm,shift_n,address,address1,result;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(Bad_Reg(rm))
		printf("	it is unpredictable!");
	else if(rt == 15 && InITBlock() && !LastInITBlock())
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		address1 = address & 0x00000003;
		if(rt == 15)
			if(address1 != 0)
				printf("	it is unpredictable!");
			else
				LoadWritePC(get_MemU(address,4));
		else{
			result = get_MemU(address,4);
			set_general_register(rt,result);
		}
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldr_reg\n");
	}
}

void ldrb_reg(int i){
	int rt,rn,rm,shift_n,address,result;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rt == 15)
		printf("	it is unpredictable!");
	else if(rt == 13 || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		result = get_MemU(address,1);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrb_reg\n");
	}
}

void ldrsb_reg(int i){
	int rt,rn,rm,shift_n,address,result,temp;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rt == 15)
		printf("	it is unpredictable!");
	else if(rt == 13 || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		result = get_MemU(address,1);
		temp = result & 0x00000080;
		if(LsSingleRnShift.s && temp)
			result = result | 0xFFFFFF00;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsb_reg\n");
	}
}

void ldrh_reg(int i){
	int rt,rn,rm,shift_n,address,result;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rt == 15)
		printf("	it is unpredictable!");
	else if(rt == 13 || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		result = get_MemU(address,2);
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrh_reg\n");
	}
}

void ldrsh_reg(int i){
	int rt,rn,rm,shift_n,address,result,temp;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rt == 15)
		printf("	it is unpredictable!");
	else if(rt == 13 || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		result = get_MemU(address,2);
		temp = result & 0x00008000;
		if(LsSingleRnShift.s && temp)
			result = result | 0xFFFF0000;
		set_general_register(rt,result);
		//printf("	Rt = %X",get_general_register(rt));
		//printf("	******ldrsh_reg\n");
	}
}

void str_reg(int i){
	int rt,rn,rm,shift_n,address,result;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rn == 15)
		printf("	it is undefined!");
	else if(rt == 15 || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		result = get_general_register(rt);
		set_MemU(address,4,result);
		//printf("	Memory unit is %X",get_MemU(address,4));
		//printf("	******str_reg\n");
	}
}

void strb_reg(int i){
	int rt,rn,rm,shift_n,address;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		set_MemU(address,1,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,1));
		//printf("	******strb_reg\n");
	}
}

void strh_reg(int i){
	int rt,rn,rm,shift_n,address;
	*((int *)(&LsSingleRnShift)) = i;
	rt = LsSingleRnShift.rt;
	rn = LsSingleRnShift.rn;
	rm = LsSingleRnShift.rm;
	shift_n = LsSingleRnShift.shift;
	if(rn == 15)
		printf("	it is undefined!");
	else if(Bad_Reg(rt) || Bad_Reg(rm))
		printf("	it is unpredictable!");
	else{
		address = get_general_register(rn) + lsl(get_general_register(rm),shift_n);
		set_MemU(address,2,get_general_register(rt));
		//printf("	Memory unit is %X",get_MemU(address,2));
		//printf("	******strh_reg\n");
	}
}

