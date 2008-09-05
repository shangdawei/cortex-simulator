#include "stdio.h"
#include "load_store_double_exclusive.h"
#include "instruction.h"

void ls_exclusive(int instruction){
	opcode_error(instruction);
}

void ls_exbh_tb(int instruction){
	int index;
	func f_ptr;
	*((int *)(&TbB)) = instruction;
	printf("ls_exbh_tb: 0x%X \n",instruction);
	printf("Op: 0x%X \n",TbB.op);
	printf("Rt: 0x%X \n",TbB.rt);
	printf("Rt2: 0x%X \n",TbB.rt2);
	if(TbB.l == 1 && TbB.op == 4)
		index = 0;
	else if(TbB.l == 1 && TbB.op == 5)
		index = 1;
	else if(TbB.l == 0 && TbB.op == 4)
		index = 2;
	else if(TbB.l == 0 && TbB.op == 5)
		index = 3;
	else if(TbB.l == 1 && TbB.op == 0)
		index = 4;
	else if(TbB.l == 1 && TbB.op == 1)
		index = 5;
	else
		index = 6;
	printf("index is %d", index);
	f_ptr=(void *)ls_ex_bh_tb[index];
	f_ptr(instruction);
}

void ls_double(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LdrD)) = instruction;
	printf("ls_double: 0x%X \n",instruction);
	printf("Imm8: 0x%X \n",LdrD.imm8);
	printf("Rt: 0x%X \n",LdrD.rt);
	printf("Rt2: 0x%X \n",LdrD.rt2);
	if(LdrD.l == 1)
		index = 0;
	else if(LdrD.l == 0)
		index = 1;
	else
		index = 2;
	printf("index is %d",index);
	f_ptr=(void *)ls_doub[index];
	f_ptr(instruction);
}

void tbb(int i){
	int n,m,halfwords;
	*((int *)(&TbB)) = i;
	n = TbB.rn;
	m = TbB.rm;
	if(n == 13 || Bad_Reg(m))
		printf("	It is unpredictable!");
	else if(InITBlock() && !LastInITBlock())
		printf("	It is unpredictable!");
	else{
		halfwords = load_byte(get_general_register(n) + get_general_register(m),0);
		halfwords = halfwords << 1;
		BranchWritePC(get_pc() + halfwords);
		printf("	*****tbb");
	}
}

void tbh(int i){
	int n,m,halfwords;
	*((int *)(&TbH)) = i;
	n = TbH.rn;
	m = TbH.rm;
	if(n == 13 || Bad_Reg(m))
		printf("	It is unpredictable!");
	else if(InITBlock() && !LastInITBlock())
		printf("	It is unpredictable!");
	else{
		halfwords = load_half(get_general_register(n) + lsl(get_general_register(m),1),0);
		halfwords = halfwords << 1;
		BranchWritePC(get_pc() + halfwords);
		printf("	*****tbh");
	}
}

void ldrd(int i){
	int t,t2,n,imm32,base,offset_addr,address,temp1,temp2;
	*((int *)(&LdrD)) = i;
	t = LdrD.rt;
	t2 = LdrD.rt2;
	n = LdrD.rn;
	imm32 = LdrD.imm8 << 2;
	if(LdrD.w == 1 && n == 15)
		printf("	It is unpredictable!");
	else if(Bad_Reg(t) || Bad_Reg(t2) || t == t2)
		printf("	It is unpredictable!");
	else{
		if(n == 15)
			base = align(get_pc(),4);
		else
			base = get_general_register(n);
		if(LdrD.u == 1)
			offset_addr = base + imm32;
		else
			offset_addr = base - imm32;
		if(LdrD.p == 1)
			address = offset_addr;
		else
			address = get_general_register(n);
		if(LdrD.w == 1)
			set_general_register(n,offset_addr);
		temp1 = get_memory(address/4);
		set_general_register(t,temp1);
		temp2 = get_memory(address/4 + 1);
		set_general_register(t2,temp2);
		printf("	Rt = 0x%X",get_general_register(t));
		printf("	Rt2 = 0x%X",get_general_register(t2));
		printf("	*****ldrd");
	}
}

void strd(int i){
	int t,t2,n,imm32,offset_addr,address;
	*((int *)(&StrD)) = i;
	t = StrD.rt;
	t2 = StrD.rt2;
	n = StrD.rn;
	imm32 = StrD.imm8 << 2;
	if(StrD.w == 1 && t == n)
		printf("	It is unpredictable!");
	else if(StrD.w == 1 && t2 == n)
		printf("	It is unpredictable!");
	else if(n == 15 || Bad_Reg(t) || Bad_Reg(t2))
		printf("	It is unpredictable!");
	else{
		if(StrD.u == 1)
			offset_addr = get_general_register(n) + imm32;
		else
			offset_addr = get_general_register(n) - imm32;
		if(StrD.p == 1)
			address = offset_addr;
		else
			address = get_general_register(n);
		if(LdrD.w == 1)
			set_general_register(n,offset_addr);
		set_memory(address/4,get_general_register(t));
		set_memory(address/4 + 1,get_general_register(t2));
		printf("	*****strd");
	}
}

