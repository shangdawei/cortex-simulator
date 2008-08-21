#include "stdio.h"
#include "thumb_load_store.h"
#include "memory.h"
#include "instruction.h"
#include <assert.h>

/* load from literal pool */
void thumb_ldr_lit(short instruction)
{
	int rt, imm32, address, address1, result, base;
	*((short*) (&LdrFromLiteralPool)) = instruction;
	rt = LdrFromLiteralPool.rd;
	imm32 = LdrFromLiteralPool.imm8 << 2;
	base = align(get_pc(), 4);
	address = base + imm32;
	address1 = address & 0x00000003;
	if(rt == $PC)
		if(address1 != 0)
			printf("	it is unpredictable!");
		else
			LoadWritePC(get_MemU(address, 4));
	else{
		result = get_MemU(address, 4);
		set_general_register(rt,result);
	}
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldr_lit\n");
}


/* load/store register offset */
void thumb_ld_st_reg_off(short instruction)
{
	func f_ptr;	
	*((short*) (&LdrStrRegOffset)) = instruction;
	printf("thumb_ld_st_reg_off : 0x%x\n", instruction);
	printf("rt:0x%x; rn:0x%x rm:0x%x op:0x%x\n", 
		LdrStrRegOffset.rt, LdrStrRegOffset.rn, LdrStrRegOffset.rm, LdrStrRegOffset.op);	
	f_ptr = ldr_str_reg_off[LdrStrRegOffset.op];
	f_ptr(instruction);
}

void thumb_str_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	result = get_general_register(rt);
	set_MemU(address, 4, result);
	printf("	Memory unit is %X",get_MemU(address, 4));
	printf("	******thumb_str_reg\n");
}

void thumb_strh_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	set_MemU(address, 2, get_general_register(rt));
	printf("	Memory unit is %X",get_MemU(address, 2));
	printf("	******thumb_strh_reg\n");
}

void thumb_strb_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	set_MemU(address, 1, get_general_register(rt));
	printf("	Memory unit is %X",get_MemU(address, 1));
	printf("	******thumb_strb_reg\n");
}

void thumb_ldrsb_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	result = get_MemU(address,1);
	if (result & 0x00000080) result |= 0xFFFFFF00;
	set_general_register(rt,result);
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldrsb_reg\n");
}

void thumb_ldr_reg(short instruction)
{
	int rt, rn, rm, address, result, address1;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	address1 = address & 0x00000003;
	if(rt == $PC)
		if(address1 != 0)
			printf("	it is unpredictable!");
		else
			LoadWritePC(get_MemU(address, 4));
	else{
		result = get_MemU(address, 4);
		set_general_register(rt,result);
	}
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldr_reg\n");
}

void thumb_ldrh_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	result = get_MemU(address, 2);
	set_general_register(rt,result);
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldrh_reg\n");
}

void thumb_ldrb_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	result = get_MemU(address, 1);
	set_general_register(rt,result);
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldrb_reg\n");
}

void thumb_ldrsh_reg(short instruction)
{
	int rt, rn, rm, address, result;
	*((short*) (&LdrStrRegOffset)) = instruction;
	rt = LdrStrRegOffset.rt;
	rn = LdrStrRegOffset.rn;
	rm = LdrStrRegOffset.rm;
	address = get_general_register(rn) + get_general_register(rm);
	result = get_MemU(address, 2);
	if (result & 0x00008000) result |= 0xFFFF0000;
	set_general_register(rt,result);
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldrsh_reg\n");
}

/* load/store word/byte immediate offset */
void thumb_ld_st_word_byte_imm_off(short instruction)
{
	func f_ptr;
	int index;
	*((short*) (&LdrStrWordByteImmOffset)) = instruction;
	printf("thumb_ld_st_imm_off : 0x%x\n", instruction);
	printf("rt:0x%x; rn:0x%x imm5:0x%x L:0x%x B:0x%x\n", 
		LdrStrWordByteImmOffset.rt, LdrStrWordByteImmOffset.rn, 
		LdrStrWordByteImmOffset.imm5, LdrStrWordByteImmOffset.l, LdrStrWordByteImmOffset.b);	
	index = LdrStrWordByteImmOffset.b * 2 + LdrStrWordByteImmOffset.l;
	f_ptr = ldr_str_word_byte_imm_off[index];
	f_ptr(instruction);
}

void thumb_str_imm(short instruction)
{
	int rt, rn, imm32, address, result;
	*((short*) (&LdrStrWordByteImmOffset)) = instruction;
	rt = LdrStrWordByteImmOffset.rt;
	rn = LdrStrWordByteImmOffset.rn;
	imm32 = LdrStrWordByteImmOffset.imm5 << 2;
	address = get_general_register(rn) + imm32;
	result = get_general_register(rt);		
	set_MemU(address, 4, result);
	printf("	Memory unit is %X",get_MemU(address, 4));
	printf("	******strb_imm\n");
}

void thumb_ldr_imm(short instruction)
{
	int rt, rn, imm32, address, address1, result;
	*((short*) (&LdrStrWordByteImmOffset)) = instruction;
	rt = LdrStrWordByteImmOffset.rt;
	rn = LdrStrWordByteImmOffset.rn;
	imm32 = LdrStrWordByteImmOffset.imm5 << 2;
	address = get_general_register(rn) + imm32;
	address1 = address & 0x00000003;								//
	if(rt == $PC)
		if(address1 != 0)
			printf("	it is unpredictable!");
		else
			LoadWritePC(get_MemU(address, 4));
	else{
		result = get_MemU(address, 4);
		set_general_register(rt,result);
	}
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldr_imm\n");
}

void thumb_strb_imm(short instruction)
{
	int rt, rn, imm32, address, result;
	*((short*) (&LdrStrWordByteImmOffset)) = instruction;
	rt = LdrStrWordByteImmOffset.rt;
	rn = LdrStrWordByteImmOffset.rn;
	imm32 = LdrStrWordByteImmOffset.imm5;
	address = get_general_register(rn) + imm32;
	set_MemU(address, 1, get_general_register(rt));
	printf("	Memory unit is %X",get_MemU(address, 1));
	printf("	******thumb_strb_imm\n");
}

void thumb_ldrb_imm(short instruction)
{
	int rt, rn, imm32, address, result;
	*((short*) (&LdrStrWordByteImmOffset)) = instruction;
	rt = LdrStrWordByteImmOffset.rt;
	rn = LdrStrWordByteImmOffset.rn;
	imm32 = LdrStrWordByteImmOffset.imm5;
	address = get_general_register(rn) + imm32;
	result = get_MemU(address, 1);
	set_general_register(rt, result);
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldrb_imm\n");
}

/* load/store halfword imm offset */
void thumb_ld_st_hw_imm_off(short instruction)
{
	func f_ptr;
	int index;
	*((short*) (&LdrStrHalfwordImmOffset)) = instruction;
	printf("thumb_ld_st_hw_imm_off : 0x%x\n", instruction);
	printf("rt:0x%x; rn:0x%x imm5:0x%x L:0x%x\n", 
		LdrStrHalfwordImmOffset.rt, LdrStrHalfwordImmOffset.rn, 
		LdrStrHalfwordImmOffset.imm5, LdrStrHalfwordImmOffset.l);
	index = LdrStrHalfwordImmOffset.l;
	f_ptr = ldr_str_halfword_imm_off[index];
	f_ptr(instruction);
}

void thumb_strh_imm(short instruction)
{
	int rt, rn, imm32, address;
	*((short*) (&LdrStrHalfwordImmOffset)) = instruction;
	rt  = LdrStrHalfwordImmOffset.rt;
	rn = LdrStrHalfwordImmOffset.rn;
	imm32 = LdrStrHalfwordImmOffset.imm5 << 1;
	address = get_general_register(rn) + imm32;
	set_MemU(address, 1, get_general_register(rt));
	printf("	Memory unit is %X",get_MemU(address, 2));
	printf("	******thumb_strh_imm\n");
}

void thumb_ldrh_imm(short instruction)
{
	int rt, rn, imm32, address, result;
	*((short*) (&LdrStrHalfwordImmOffset)) = instruction;
	rt  = LdrStrHalfwordImmOffset.rt;
	rn = LdrStrHalfwordImmOffset.rn;
	imm32 = LdrStrHalfwordImmOffset.imm5 << 1;
	address = get_general_register(rn) + imm32;
	result = get_MemU(address, 2);
	set_general_register(rt,result);
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_strh_imm\n");
}

//load from / store to stack
void thumb_ld_st_stack(short instruction)
{
	func f_ptr;
	int index;
	*((short*) (&LdrStrStack)) = instruction;
	printf("thumb_ld_st_stack : 0x%x\n", instruction);
	printf("imm8:0x%x; rt:0x%x L:0x%x\n", 
		LdrStrStack.imm8, LdrStrStack.rt, LdrStrStack.l);
	index = LdrStrStack.l;
	f_ptr = ldr_str_stack[index];
	f_ptr(instruction);
}

void thumb_str_sp_imm(short instruction)
{
	int rt, rn, imm32, address;
	*((short*) (&LdrStrStack)) = instruction;
	rt = LdrStrStack.rt;
	rn = $SP;
	imm32 = LdrStrStack.imm8 << 2;
	address = get_general_register(rn) + imm32;
	set_MemU(address, 4, get_general_register(rt));
	printf("	Memory unit is %X",get_MemU(address, 4));
	printf("	******thumb_str_sp_imm\n");
}

void thumb_ldr_sp_imm(short instruction)
{
	int rt, rn, imm32, address, address1, result;
	*((short*) (&LdrStrStack)) = instruction;
	rt = LdrStrStack.rt;
	rn = $SP;
	imm32 = LdrStrStack.imm8 << 2;
	address = get_general_register(rn) + imm32;
	address1 = address & 0x00000003;
	if(rt == $PC)
		if(address1 != 0)
			printf("	it is unpredictable!");
		else
			LoadWritePC(get_MemU(address, 4));
	else{
		result = get_MemU(address, 4);
		set_general_register(rt,result);
	}
	printf("	Rt = %X",get_general_register(rt));
	printf("	******thumb_ldr_sp_imm\n");
}

//load /store multiple
void thumb_ld_st_multiple(short instruction)
{
	func f_ptr;
	int index;
	*((short*) (&LdrStrMultiple)) = instruction;
	printf("thumb_ld_st_multiple : 0x%x\n", instruction);
	printf("reg_list:0b%x; rn:0x%x L:0x%x\n", 
		LdrStrMultiple.reg_list, LdrStrMultiple.rn, LdrStrMultiple.l);
	index = LdrStrMultiple.l;
	f_ptr = ldr_str_multiple[index];
	f_ptr(instruction);
}

void thumb_stm(short instruction)
{
	int rn, registers, originalRn, address, temp;
	int j;
	*((short*) (&LdrStrMultiple)) = instruction;
	rn = LdrStrMultiple.rn;
	registers = LdrStrMultiple.reg_list & 0x000000FF;
	if (BitCount(registers) < 1)
		printf("	it is unpredictable!");
	else {
		temp = address = originalRn = get_general_register(rn);
		temp += 4 * BitCount(registers);
		set_general_register(rn, temp);
		for(j = 0;j <= 14;j++){
			if(registers & (0x01<< j)){
				if(j == rn){
					if(j == LowestSetBit(registers))
						set_MemA(address, 4, originalRn);
					else
						set_MemA(address, 4, 0);
				}
				else
					set_MemA(address, 4, get_general_register(j));
				address = address + 4;
			}
		}
		assert(address == originalRn + 4*BitCount(registers));

		for(j = 0;j <= 14;j++){
			address = address - 4;
			printf("	0x%X",get_MemA(address, 4));
		}
		printf("	*****thumb_stm\n");

	}
}

void thumb_ldm(short instruction)
{
	int rn, registers, originalRn, address, temp, loadvalue;
	int wback, j;	
	*((short*) (&LdrStrMultiple)) = instruction;
	rn = LdrStrMultiple.rn;
	registers = LdrStrMultiple.reg_list & 0x000000FF;
	wback = ((registers & (0x01 << rn)) == 0) ? 1 : 0;
	if (BitCount(registers) < 1)
		printf("	it is unpredictable!");
	else {
		temp = address = originalRn = get_general_register(rn);
		temp += 4 * BitCount(registers);
		set_general_register(rn, temp);
		for (j = 0; j<=14; j++){
			if(registers & (0x01<< j)){
				loadvalue = get_MemA(address, 4);
				if (!(j == rn && wback !=0)) {
					set_general_register(j,loadvalue);
				}
				address = address + 4;
			}
		}
		if(registers & (0x01<< 15)){
			LoadWritePC(get_MemA(address, 4));
			address = address + 4;
		}
		assert(address == originalRn + 4*BitCount(registers));
		for(j = 0;j <= 12;j++)
			printf("	R[%d] = 0x%X",j,get_general_register(j));
		printf("	SP = 0x%X",get_sp());
		printf("	LR = 0x%X",get_lr());
		printf("	PC = 0x%X",get_pc());
		printf("	*****thumb_ldm\n");

	}
}





