#include "stdio.h"
#include "load_store_multiple.h"
#include "memory.h"
#include "instruction.h"

void ls_multiple(int instruction){
	int index;
	func f_ptr;
	*((int *)(&LdmDbEa)) = instruction;
	//printf("ls_multiple: 0x%X \n",instruction);
	//printf("Rn: 0x%x \n", LdmDbEa.rn);
	if(LdmDbEa.vu == 2 && LdmDbEa.l == 1)
		index = 0;
	else if(LdmDbEa.vu == 1 && LdmDbEa.l == 1 && LdmDbEa.rn != 13)
		index = 1;
	else if(LdmDbEa.vu == 1 && LdmDbEa.l == 1 && LdmDbEa.rn == 13)
		index = 2;
	else if(LdmDbEa.vu == 2 && LdmDbEa.l == 0 && LdmDbEa.rn == 13)
		index = 3;
	else if(LdmDbEa.vu == 2 && LdmDbEa.l == 0 && LdmDbEa.rn != 13)
		index = 4;
	else if(LdmDbEa.vu == 1 && LdmDbEa.l == 0)
		index = 5;
	else
		index = 6;
	//printf("index is %d", index);
	f_ptr=(void *)ls_multi[index];
	f_ptr(instruction);
}

void ls_multiple_reserved(int instruction){
	//printf("ls_multiple_reserved: 0x%X \n",instruction);
}

//Load Multiple Decrement Before (Load Multiple Empty Ascending) loads multiple registers from sequential memory locations using an address from a base register.
void ldm_db_ea(int i){
	int n,rn,j,registers,originalRn,address,loadedvalue;
	*((int *)(&LdmDbEa)) = i;
	n = LdmDbEa.rn;
	rn = get_general_register(n);
	registers = (LdmDbEa.p << 15) + (LdmDbEa.m << 14) + (LdmDbEa.pass1 << 13) + LdmDbEa.mask;
	if(n == 15 || BitCount(registers) < 2)
		printf("	It is unpredictable!");
	else if(LdmDbEa.p == 1 && LdmDbEa.m == 1)
		printf("	It is unpredictable!");
	else if(LdmDbEa.p == 1 &&  InITBlock() && !LastInITBlock())
		printf("	It is unpredictable!");
	else{
		originalRn = rn;
		address = rn - 4 * BitCount(registers);
		if(LdmDbEa.w == 1){
			if(registers & (1<< n))
				set_general_register(n,0);
			else{
				rn = rn - 4 * BitCount(registers);
				set_general_register(n,rn);
			}
		}
		for(j = 0;j <= 14;j++){
			if(registers & (1<< j)){
				loadedvalue = get_MemA(address,4);
				if(!(j == n && LdmDbEa.w == 1))
					set_general_register(j,loadedvalue);
				address = address + 4;
			}
		}
		if(registers & (1<< 15)){
			LoadWritePC(get_MemA(address,4));
			address = address + 4;
		}
		assert(address == originalRn);
		for(j = 0;j <= 12;j++)
			printf("	R[%d] = 0x%X",j,get_general_register(j));
#if DEBUG
		printf("	SP = 0x%X",get_sp());
		printf("	LR = 0x%X",get_lr());
		printf("	PC = 0x%X",get_pc());
		printf("	*****ldm_db_ea\n");
#endif
	}
}

//Load Multiple Increment After loads multiple registers from consecutive memory locations using an address from a base register.
void ldm_ia_fd(int i){
	int n,rn,j,registers,originalRn,address,loadedvalue;
	*((int *)(&LdmIaFd)) = i;
	n = LdmIaFd.rn;
	rn = get_general_register(n);
	registers = (LdmIaFd.p << 15) + (LdmIaFd.m << 14) + (LdmIaFd.pass1 << 13) + LdmIaFd.mask;
	if(n == 15 || BitCount(registers) < 2)
		printf("	It is unpredictable!");
	else if(LdmIaFd.p == 1 && LdmIaFd.m == 1)
		printf("	It is unpredictable!");
	else if(LdmIaFd.p == 1 &&  InITBlock() && !LastInITBlock())
		printf("	It is unpredictable!");
	else{
		originalRn = rn;
		address = rn;
		if(LdmIaFd.w == 1){
			if(registers & (1<< n))
				set_general_register(n,0);
			else{
				rn = rn + 4 * BitCount(registers);
				set_general_register(n,rn);
			}
		}
		for(j = 0;j <= 14;j++){
			if(registers & (1<< j)){
				loadedvalue = get_MemA(address,4);
				if(!(j == n && LdmIaFd.w == 1))
					set_general_register(j,loadedvalue);
				address = address + 4;
			}
		}
		if(registers & (1<< 15)){
			LoadWritePC(get_MemA(address,4));
			address = address + 4;
		}
		assert(address == originalRn + 4*BitCount(registers));
#if DEBUG
		for(j = 0;j <= 12;j++)
			printf("	R[%d] = 0x%X",j,get_general_register(j));
		printf("	SP = 0x%X",get_sp());
		printf("	LR = 0x%X",get_lr());
		printf("	PC = 0x%X",get_pc());
		printf("	*****ldm_ia_fd\n");
#endif
	}
}

//Pop Multiple Registers loads a subset (or possibly all) of the general-purpose registers R0-R12 and the PC or the LR from the stack.
void pop(int i){
	int sp,j,registers,originalSP,address,loadedvalue;
	*((int *)(&Pop)) = i;
	sp = get_sp();
	registers = (Pop.p << 15) + (Pop.m << 14) + (Pop.pass1 << 13) + Pop.mask;
	if(BitCount(registers) < 2){
		printf("	It is unpredictable!");
		return;
	}
	else if(Pop.p == 1 && Pop.m == 1){
		printf("	It is unpredictable!");
		return;
	}
	else{
		originalSP = sp;
		address = sp;
		sp = sp + 4*BitCount(registers);
		set_sp(sp);
		for(j = 0;j <= 14;j++){
			if(registers & (1<< j)){
				loadedvalue = get_MemA(address,4);
				address = address + 4;
			}
		}
		if(registers & (1<< 15)){
			LoadWritePC(get_MemA(address,4));
			address = address + 4;
		}
		assert(address == originalSP + 4*BitCount(registers));
#if DEBUG
		for(j = 0;j <= 12;j++)
			printf("	R[%d] = 0x%X",j,get_general_register(j));
		printf("	SP = 0x%X",get_sp());
		printf("	LR = 0x%X",get_lr());
		printf("	PC = 0x%X",get_pc());
		printf("	*****pop\n");
#endif
	}
}

//Push Multiple Registers stores a subset (or possibly all) of the general-purpose registers R0-R12 and the LR to the stack.
void push(int i){
	int sp,j,registers,originalSP,address;
	*((int *)(&Push)) = i;
	sp = get_sp();
	registers = (Push.p << 15) + (Push.m << 14) + (Push.pass1 << 13) + Push.mask;
	if(BitCount(registers) < 2)
		printf("	It is unpredictable!");
	else{
		originalSP = sp;
		address = sp - 4*BitCount(registers);
		for(j = 0;j <= 14;j++){
			if(registers & (1<< j)){
				set_MemA(address,4,get_general_register(j));
				address = address + 4;
			}
		}
		assert(address == originalSP);
		//for(j = 0;j <= 14;j++){
		//	address = address - 4;
			//printf("	0x%X",get_MemA(address,4));
		//}
		//printf("	*****push\n");
	}
}

//Store Multiple Decrement Before (Store Multiple Full Descending) stores multiple registers to sequential memory locations using an address from a base register.
void stm_db_fd(int i){
	int n,rn,j,registers,originalRn,address;
	*((int *)(&StmDbFd)) = i;
	n = StmDbFd.rn;
	rn = get_general_register(n);
	registers = (StmDbFd.p << 15) + (StmDbFd.m << 14) + (StmDbFd.pass1 << 13) + StmDbFd.mask;
	if(n == 15 || BitCount(registers) < 2)
		printf("	It is unpredictable!");
	else{
		originalRn = rn;
		address = rn - 4*BitCount(registers);
		if(StmDbFd.w == 1){
			rn = rn + 4*BitCount(registers);
			set_general_register(n,rn);
		}
		for(j = 0;j <= 14;j++){
			if(registers & (1<< j)){
				if(j == n && StmDbFd.w == 1){
					if(j == LowestSetBit(registers))
						set_MemA(address,4,originalRn);
					else
						set_MemA(address,4,0);
				}
				else
					set_MemA(address,4,get_general_register(j));
				address = address + 4;
			}
		}
		assert(address == originalRn);
		for(j = 0;j <= 14;j++){
			address = address - 4;
			//printf("	0x%X",get_MemA(address,4));
		}
		//printf("	*****stm_db_fd\n");
	}
}

//Store Multiple Increment After (Store Multiple Empty Ascending) stores multiple registers to consecutive memory locations using an address from a base register.
void stm_ia_ea(int i){
	int n,rn,j,registers,originalRn,address;
	*((int *)(&StmIaEa)) = i;
	n = StmIaEa.rn;
	rn = get_general_register(n);
	registers = (StmIaEa.p << 15) + (StmIaEa.m << 14) + (StmIaEa.pass1 << 13) + StmIaEa.mask;
	if(n == 15 || BitCount(registers) < 2)
		printf("	It is unpredictable!");
	else{
		originalRn = rn;
		address = rn;
		if(StmIaEa.w == 1){
			rn = rn + 4*BitCount(registers);
			set_general_register(n,rn);
		}
		for(j = 0;j <= 14;j++){
			if(registers & (1<< j)){
				if(j == n && StmIaEa.w == 1){
					if(j == LowestSetBit(registers))
						set_MemA(address,4,originalRn);
					else
						set_MemA(address,4,0);
				}
				else
					set_MemA(address,4,get_general_register(j));
				address = address + 4;
			}
		}
		assert(address == originalRn + 4*BitCount(registers));
		for(j = 0;j <= 14;j++){
			address = address - 4;
			//printf("	0x%X",get_MemA(address,4));
		}
		//printf("	*****stm_ia_ea\n");
	}
}