/**
 *
 * 
 * 
 * 
 *
 */
#include "thumb_misc.h" 
#include "instruction.h"
/**
 *
 *
 *
 */ 


void thumb_opcode_error(short i) {
	printf("	The instruction: 0x%x is error in this situation. \n", i);
}

void thumb_branch_exchange_instruction_set(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&branchExchangeInstructionSet)) = instruction;

#if DEBUG
	printf("thumb_branch_exchange_instruction_set: 0x%X \n", instruction);
	printf("L: 0x%x \n", branchExchangeInstructionSet.l);
	printf("Rm: 0x%x \n", branchExchangeInstructionSet.rm);
#endif

	index = branchExchangeInstructionSet.l;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)branch_exchange_instruction_set[index];
	f_ptr(instruction);
}

void thumb_add_to_sp_or_pc(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&addToSpOrPc)) = instruction;

#if DEBUG
	printf("thumb_add_to_sp_or_pc: 0x%X \n", instruction);
	printf("SP: 0x%x \n", addToSpOrPc.sp);
	printf("Rd: 0x%x \n", addToSpOrPc.rd);
	printf("imm8: 0x%x \n", addToSpOrPc.imm8);
#endif
	index = addToSpOrPc.sp;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)add_to_sp_or_pc[index];
	f_ptr(instruction);
}

void thumb_adjust_stack_pointer(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&adjustStackPointer)) = instruction;
#if DEBUG
	printf("thumb_adjust_stack_pointer: 0x%X \n", instruction);
	printf("Operate Code: 0x%x \n", adjustStackPointer.opc);
	printf("imm7: 0x%x \n", adjustStackPointer.imm7);
#endif
	index = adjustStackPointer.opc;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)adjust_stack_pointer[index];
	f_ptr(instruction);
}

void thumb_sign_zero_extend(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&signZeroExtend)) = instruction;
#if DEBUG
	printf("thumb_sign_zero_extend: 0x%X \n", instruction);
	printf("Operate Code: 0x%x \n", signZeroExtend.opc);
	printf("Rm: 0x%x \n", signZeroExtend.rm);
	printf("Rd: 0x%x \n", signZeroExtend.rd);
#endif
	index = signZeroExtend.opc;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)sign_zero_extend[index];
	f_ptr(instruction);
}

void thumb_compare_and_branch(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&compareAndBranch)) = instruction;
#if DEBUG
	printf("thumb_compare_and_branch: 0x%X \n", instruction);
	printf("N: 0x%x \n", compareAndBranch.n);
	printf("i: 0x%x \n", compareAndBranch.i);
	printf("imm5: 0x%x \n", compareAndBranch.imm5);
	printf("Rn: 0x%x \n", compareAndBranch.rn);
#endif
	index = compareAndBranch.n;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)compare_and_branch[index];
	f_ptr(instruction);
}

void thumb_push_pop_register_list(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&pushPopRegisterList)) = instruction;
#if DEBUG
	printf("thumb_push_pop_register_list: 0x%X \n", instruction);
	printf("L: 0x%x \n", pushPopRegisterList.l);
	printf("R: 0x%x \n", pushPopRegisterList.r);
	printf("register list: 0x%x", pushPopRegisterList.regList);
#endif
	index = pushPopRegisterList.l;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)push_pop_register_list[index];
	f_ptr(instruction);
}

/*
	Branch and Exchange causes a branch to an address and instruction set specified by a register. ARMv7-M 
	only supports the Thumb instruction set. An attempt to change the instruction execution state causes an 
	exception.
*/
void thumb_branch_and_exchange(short i) {
	int m;
	*((short *)(&branchExchangeInstructionSet)) = i;	// EncodingSpecificOperations();

	m = branchExchangeInstructionSet.rm;			// m = UInt(Rm);
	if (InITBlock() && !LastInITBlock())
		printf("	it is unpredictable! \n");
	else {											// if ConditionPassed() then
		BXWritePC(get_general_register(m));			// BXWritePC(R[m]);
		set_pc(get_pc()+2);//modified

	}
}

/*
	Branch and Exchange calls a subroutine at an address and instruction set specified by a register. ARMv7-M
	only supports the Thumb instruction set. An attempt to change the instruction execution state causes an 
	exception.
*/
void thumb_branch_with_link_and_exchange(short i) {
	int m, next_instr_addr;
	*((short *)(&branchExchangeInstructionSet)) = i;

	m = branchExchangeInstructionSet.rm;					// m = UInt(Rm);
	if (m == 15) {											// if m == 15 then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else if (InITBlock() && LastInITBlock()) {			// if InITBlock() && !LastInITBlock() then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else {												// if ConditionPassed() then
		next_instr_addr = get_pc() - 2;						// next_instr_addr = PC - 2;
		set_lr(next_instr_addr & 0xfffffffe | 0x00000001);	// LR = next_instr_addr<31:1> : '1';
		BXWritePC(get_general_register(m));					// BXWritePC(R[m]);
		set_pc(get_pc()+2);//modified
		
	}
}

/*
	Address to Register adds an immediate value to the PC value, and writes the result to the destination register.
*/
void thumb_add_to_pc(short i) {
	int d, imm32, base;
	*((short *)(&addToSpOrPc)) = i;

	d = addToSpOrPc.rd;												// d = UInt(Rd);  
	imm32 = addToSpOrPc.imm8<<2;									// imm32 = ZeroExtend(imm8:'00', 32);
	base = align(get_pc(), 4);										// base = Align(PC, 4);     // Word-aligned PC
	set_general_register(d, base + imm32);							// R[d] = if add then (base + imm32) else (base - imm32);
}

/*
	This instruction adds an immediate value to the SP value, and writes the result to the destination register.
*/
void thumb_add_to_sp(short i) {
	int d, imm32;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((short *)(&addToSpOrPc)) = i;

	d = addToSpOrPc.rd;							// d = UInt(Rd);
	imm32 = addToSpOrPc.imm8<<2;				// imm32 = ZeroExtend(imm8:'00', 32);
	addwithcarry(get_sp(), imm32, 0,result);	// (result, carry, overflow) = AddWithCarry(SP, imm32, '0');
	set_general_register(d, result->result);	//  R[d] = result;
	free(result);
}

/*
	This instruction adds an immediate value to the SP value, and writes the result to the destination register.
*/
void thumb_increment_stack_pointer(short i) {
	int d, imm32;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((short *)(&adjustStackPointer)) = i;

	d = 13;										// d = 13;
	imm32 = adjustStackPointer.imm7<<2;			// imm32 = ZeroExtend(imm7:'00', 32);
	addwithcarry(get_sp(), imm32, 0,result);	// (result, carry, overflow) = AddWithCarry(SP, imm32, '0');
	set_general_register(d, result->result);	// R[d] = result;
	free(result);
}

/*
	This instruction subtracts an immediate value from the SP value, and writes the result to the destination 
	register.
*/
void thumb_decrement_stack_pointer(short i) {
	int d, imm32;
	struct CALCULATECO *result = (struct CALCULATECO*)malloc(sizeof(struct CALCULATECO));
	*((short *)(&adjustStackPointer)) = i;

	d = 13;										// d = 13;
	imm32 = adjustStackPointer.imm7<<2;			// imm32 = ZeroExtend(imm7:'00', 32);
	addwithcarry(get_sp(), ~imm32, 1,result);	// (result, carry, overflow) = AddWithCarry(SP, NOT(imm32), '1');
	set_general_register(d, result->result);	// R[d] = result;
	free(result);
}

/*
	Signed Extend Halfword extracts a 16-bit value from a register, sign extends it to 32 bits, and writes the 
	result to the destination register. You can specify a rotation by 0, 8, 16, or 24 bits before extracting the 16-bit 
	value.
*/
void thumb_signed_extend_halfword(short i) {
	int d, m, rotation, rotated;
	*((short *)(&signZeroExtend)) = i;

	d = signZeroExtend.rd;								// d = UInt(Rd); 
	m = signZeroExtend.rm;								// m = UInt(Rm); 
	rotation = 0;										// rotation = 0;
	rotated = ror(get_general_register(m), rotation);	// rotated = ROR(R[m], rotation);
	
	//SignExtend
	if (rotated & 0x00008000) {
		rotated |= 0xffff0000;
	} else {
		rotated &= 0x0000ffff;
	}

	set_general_register(d, rotated);					// R[d] = SignExtend(rotated<15:0>, 32);
}


/*
	Signed Extend Byte extracts an 8-bit value from a register, sign extends it to 32 bits, and writes the result to 
	the destination register. You can specify a rotation by 0, 8, 16, or 24 bits before extracting the 8-bit value.
*/
void thumb_signed_extend_byte(short i) {
	int d, m, rotation, rotated;
	*((short *)(&signZeroExtend)) = i;

	d = signZeroExtend.rd;								// d = UInt(Rd); 
	m = signZeroExtend.rm;								// m = UInt(Rm); 
	rotation = 0;										// rotation = 0;
	rotated = ror(get_general_register(m), rotation);	// rotated = ROR(R[m], rotation);
	
	// SignExtend
	if (rotated & 0x00000080) {
		rotated |= 0xffffff00;
	} else {
		rotated &= 0x000000ff;
	}

	set_general_register(d, rotated);					// R[d] = SignExtend(rotated<7:0>, 32);
}

/*
	Unsigned Extend Halfword extracts a 16-bit value from a register, zero extends it to 32 bits, and writes the 
	result to the destination register. You can specify a rotation by 0, 8, 16, or 24 bits before extracting the 16-bit 
	value.
*/
void thumb_unsigned_extend_halfword(short i) {
	int d, m, rotation, rotated; 
	*((short *)(&signZeroExtend)) = i;

	d = signZeroExtend.rd;								// d = UInt(Rd); 
	m = signZeroExtend.rm;								// m = UInt(Rm); 
	rotation = 0;										// rotation = 0;
	rotated = ror(get_general_register(m), rotation);	// rotated = ROR(R[m], rotation);
	set_general_register(d, rotated);					// R[d] = ZeroExtend(rotated<15:0>, 32);
}

/*
	Unsigned Extend Byte extracts an 8-bit value from a register, zero extends it to 32 bits, and writes the result 
	to the destination register. You can specify a rotation by 0, 8, 16, or 24 bits before extracting the 8-bit value.
*/
void thumb_unsigned_extned_byte(short i) {
	int d, m, rotation, rotated;
	*((short *)(&signZeroExtend)) = i;

	d = signZeroExtend.rd;								// d = UInt(Rd); 
	m = signZeroExtend.rm;								// m = UInt(Rm); 
	rotation = 0;										// rotation = 0;
	rotated = ror(get_general_register(m), rotation);	// rotated = ROR(R[m], rotation);
	set_general_register(d, rotated);					// R[d] = ZeroExtend(rotated<7:0>, 32);
}

/*
	Compare and Branch on Zero compares the value in a register with zero, and conditionally branches forward 
	a constant value. It does not affect the condition flags.
*/
void thumb_compare_and_branch_on_zero(short i) {
	int n, imm32;	
	*((short *)(&compareAndBranch)) = i;

	n = compareAndBranch.n;											// n = UInt(Rn); 
	imm32 = (compareAndBranch.i<<6) | (compareAndBranch.imm5<<1);	// imm32 = ZeroExtend(i:imm5:'0', 32);
	if (InITBlock()) {												// if InITBlock() then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else {
		if (get_general_register(n) == 0) {							// if IsZeroBit(R[n]) == '1' then
			BranchWritePC(get_pc() + imm32);						// BranchWritePC(PC + imm32);
	    	set_pc(get_pc()+2);//modified

		}
	}
}

/*
	Compare and Branch on Non-Zero compares the value in a register with zero, and conditionally branches 
	forward a constant value. It does not affect the condition flags.
*/
void thumb_compare_and_branch_on_nonzero(short i) {
	int n, imm32;
	*((short *)(&compareAndBranch)) = i;
	
	n = compareAndBranch.n;											// n = UInt(Rn); 
	imm32 = (compareAndBranch.i<<6) | (compareAndBranch.imm5<<1);	// imm32 = ZeroExtend(i:imm5:'0', 32);
	if (InITBlock()) {												// if InITBlock() then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else {
		/*
		EncodingSpecificOperations();
		if IsZeroBit(R[n]) == '0' then
			BranchWritePC(PC + imm32);
		*/
		EncodingSpecificOperations();
		if (get_general_register(n) != 0) {							// if IsZeroBit(R[n]) == '0' then
			BranchWritePC(get_pc() + imm32);						// BranchWritePC(PC + imm32);
			set_pc(get_pc()+2);//modified

		}
	}
}

/*
	Push Multiple Registers stores a subset (or possibly all) of the general-purpose registers R0-R12 and the LR
	to the stack.
*/
void thumb_push_register(short i) {
	int registers, originalSP, address;
	int j, mask;
	*((short *)(&pushPopRegisterList)) = i;

	registers = (pushPopRegisterList.r<<14) | (pushPopRegisterList.regList);	// registers = '0':M:'000000':register_list;
	if (BitCount(registers) < 1) {												// if BitCount(registers) < 1 then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else {
		/*
		if ConditionPassed() then
			EncodingSpecificOperations();
			originalSP = SP;
			address = SP - 4*BitCount(registers);
			SP = SP - 4*BitCount(registers);
			for i = 0 to 14
				if registers<i> == '1' then
					MemA[address,4] = R[i];
					address = address + 4;
			assert address == originalSP;
		*/
		if (ConditionPassed(15)) {
			EncodingSpecificOperations();
			originalSP = get_sp();
			address = get_sp() - 4 * BitCount(registers);
			set_sp(get_sp() - 4 * BitCount(registers));
			for (j = 0; j <= 14; j++) {
				mask = 1;
				if (registers & (mask<<j)) {
					set_MemA(address, 4, get_general_register(j));
					address += 4;
				}
			}
			assert(address == originalSP);
		}
	}
}

/*
	Pop Multiple Registers loads a subset (or possibly all) of the general-purpose registers R0-R12 and the PC 
	or the LR from the stack.
	If the registers loaded include the PC, the word loaded for the PC is treated as an address or an exception 
	return value and a branch occurs. Bit[0] complies with the ARM architecture interworking rules for 
	branches to Thumb state execution and must be 1. If bit[0] is 0, a UsageFault exception occurs.
*/
void thumb_pop_register(short i) {
	int registers, originalSP, address, loadedvalue;	
	int j, mask;
	*((short *)(&pushPopRegisterList)) = i;

	registers = (pushPopRegisterList.r<<15) | (pushPopRegisterList.regList);	// registers = P:'0000000':register_list;
	if (BitCount(registers) < 1) {												// if BitCount(registers) < 1 then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else {
		/*
		if ConditionPassed() then
			EncodingSpecificOperations();
			originalSP = SP;
			address = SP;
			SP = SP + 4*BitCount(registers);
			for i = 0 to 14
				if registers<i> == '1' then
					loadedvalue = MemA[address,4];
					address = address + 4;
			if registers<15> == '1' then
				LoadWritePC(MemA[address,4]);
				address = address + 4;
			assert address == originalSP + 4*BitCount(registers);
		*/
		if (ConditionPassed(15)) {
			EncodingSpecificOperations();
			originalSP = get_sp();
			address = get_sp();
			set_sp(get_sp() + 4 * BitCount(registers));
			for (j = 0; j <= 14; j++) {
				mask = 1;
				if (registers & (mask<<j)) {
					loadedvalue = get_MemA(address, 4);
					set_general_register(j, loadedvalue);
					address += 4;
				}
			}
			if (registers & 0x8000) {
				LoadWritePC(get_MemA(address, 4)+2);
				address += 4;
			}
			assert(address == originalSP + 4 * BitCount(registers));
		}
	}
}

/*
	Change Processor State. The instruction modifies the PRIMASK and FAULTMASK special-purpose
	register values.
*/
void thumb_change_processor_state(short instruction) {
	bool enable, disable, affectPRI, affectFAULT;
	*((short *)(&changeProcessorState)) = instruction;

	enable = (changeProcessorState.im == 0);		// enable = (im == '0'); 
	disable = (changeProcessorState.im == 1);		// disable = (im == '1');
	affectPRI = (changeProcessorState.i == 1);		// affectPRI = (I == '1'); 
	affectFAULT = (changeProcessorState.f == 1);	// affectFAULT = (F == '1');
	if (InITBlock()) {								// if InITBlock() then UNPREDICTABLE;
		printf("	it is unpredictable! \n");
	} else {
		/*
		EncodingSpecificOperations();
		if CurrentModeIsPrivileged() then
		    if enable then
		        if affectPRI then PRIMASK = '0';
		        if affectFAULT then FAULTMASK = '0';
		    if disable then 
		        if affectPRI then PRIMASK = '1';
		        if affectFAULT and ExecutionPriority > -1 then FAULTMASK = '1';
		*/
		EncodingSpecificOperations();
		if (CurrentModeIsPrivileged()) {
			if (enable) {
				if (affectPRI) set_primask(0);
				if (affectFAULT) set_faultmask(0);
			}
			if (disable) {
				if (affectPRI) set_primask(1);
				if (affectFAULT && ExecutionPriority()) set_faultmask(1);
			}
		}
	}
}

void thumb_reverse_bytes(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&reverseBytes)) = instruction;
#if DEBUG
	printf("reverse_bytes: 0x%X \n", instruction);
	printf("Operate Code: 0x%x \n", reverseBytes.opc);
	printf("Rm: 0x%x \n", reverseBytes.rm);
	printf("Rd: 0x%x \n", reverseBytes.rd);
#endif
	index = reverseBytes.opc;
#if DEBUG
	printf("index is %d \n", index);
#endif

	f_ptr = (void *)reverse_bytes[index];
	f_ptr(instruction);
}

void thumb_nop_compatible_hints(short instruction) {
	int index;
	func f_ptr;
	*((short *)(&nopCompatibleHints)) = instruction;
#if DEBUG
	printf("nop_compatible_hints: 0x%X \n", instruction);
	printf("hint: 0x%x \n", nopCompatibleHints.hint);
#endif
	index = nopCompatibleHints.hint;
#if DEBUG
	printf("index is %d \n", index);
#endif
	f_ptr = (void *)nop_compatible_hints[index];
	f_ptr(instruction);
}

/*
	Byte-Reverse Word reverses the byte order in a 32-bit register.
*/
void thumb_byte_reverse_word(short i) {
	int d, m, result;
	int source;
	*((short *)(&reverseBytes)) = i;

	d = reverseBytes.rd;	// d = UInt(Rd); 
	m = reverseBytes.rm;	// m = UInt(Rm);
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		bits(32) result;
		result<31:24> = R[m]<7:0>;
		result<23:16> = R[m]<15:8>;
		result<15:8>  = R[m]<23:16>;
		result<7:0>   = R[m]<31:24>;
		R[d] = result;
	*/
	if (ConditionPassed(15)) {
		EncodingSpecificOperations();
		result = 0;
		source = get_general_register(m);
		result |= (source & 0x000000ff)<<24;
		result |= (source & 0x0000ff00)<<8;
		result |= (source & 0x00ff0000)>>8;
		result |= (source & 0xff000000)>>24;
		set_general_register(d, result);
	}
}

/*
	Byte-Reverse Packed Halfword reverses the byte order in each 16-bit halfword of a 32-bit register.
*/
void thumb_byte_reverse_packed_halfword(short i) {
	int d, m, result;
	int source;
	*((short *)(&reverseBytes)) = i;

	d = reverseBytes.rd;	// d = UInt(Rd); 
	m = reverseBytes.rm;	// m = UInt(Rm);
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		bits(32) result;
		result<31:24> = R[m]<23:16>;
		result<23:16> = R[m]<31:24>;
		result<15:8>  = R[m]<7:0>;
		result<7:0>   = R[m]<15:8>;
		R[d] = result;
	*/
	if (ConditionPassed(15)) {
		EncodingSpecificOperations();
		source = get_general_register(m);
		result = 0;
		result |= (source & 0x00ff0000)<<8;
		result |= (source & 0xff000000)>>8;
		result |= (source & 0x000000ff)<<8;
		result |= (source & 0x0000ff00)>>8;
		set_general_register(d, result);
	}
}

/*
	Byte-Reverse Signed Halfword reverses the byte order in the lower 16-bit halfword of a 32-bit register, and 
	sign extends the result to 32 bits.
*/
void thumb_byte_reverse_signed_halfword(short i) {
	int d, m, result;
	int source, temp;
	*((short *)(&reverseBytes)) = i;

	d = reverseBytes.rd;	// d = UInt(Rd); 
	m = reverseBytes.rm;	// m = UInt(Rm);
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		bits(32) result;
		result<31:8>  = SignExtend(R[m]<7:0>, 24);
		result<7:0>   = R[m]<15:8>;
		R[d] = result;
	*/
	if (ConditionPassed(15)) {
		EncodingSpecificOperations();
		source = get_general_register(m);
		result = 0;
		
		// SignExtend
		temp = 0;
		if (source & 0x00000080) {
			temp = source & 0x000000ff;
			temp |= 0x00ffff00;
		} else {
			temp = source & 0x000000ff;
		}

		result |= temp << 8;
		result |= (source & 0x0000ff00)>>8;
		set_general_register(d, result);
	}
}

/*
	Breakpoint causes a DebugMonitor exception or a debug halt to occur depending on the configuration of the 
	debug support.
*/
void thumb_software_breakpoint(short i) {
	int imm32;
	*((short *)(&softwareBreakpoint)) = i;

	imm32 = softwareBreakpoint.imm8;	// imm32 = ZeroExtend(imm8, 32);	// imm32 is for assembly/disassembly only and is ignored by hardware.
	/*
	EncodingSpecificOperations();
	Breakpoint();
	*/
	EncodingSpecificOperations();
	BreakPoint();
}

/*
	If Then makes up to four following instructions (the IT block) conditional. The conditions for the 
	instructions in the IT block can be the same, or some of them can be the inverse of others.
	IT does not affect the condition code flags. Branches to any instruction in the IT block are not permitted, 
	apart from those performed by exception returns.
	16-bit instructions in the IT block, other than CMP, CMN and TST, do not set the condition code flags. The 
	AL condition can be specified to get this changed behavior without conditional execution.
*/
void thumb_if_then_instruction(short i) {
	*((short *)(&ifThenInstruction)) = i;
	/*
	if mask == '0000' then see NOP-compatible hints on page A5-15
	if firstcond == '1111' then UNPREDICTABLE; 
	if firstcond == '1110' && BitCount(mask) != 1 then UNPREDICTABLE; 
	if InITBlock() then UNPREDICTABLE;
	*/
	if (ifThenInstruction.mask == 0x00) {
		thumb_nop_compatible_hints(i);
	}
	else if (ifThenInstruction.cond == 0x0F) {
		printf("	it is unpredictable! \n");
	}
	else if (ifThenInstruction.cond == 0x0E && BitCount(ifThenInstruction.mask) != 1) {
		printf("	it is unpredictable! \n");
	}
	else if (InITBlock()) {
		printf("	it is unpredictable! \n");
	}
	/*
	EncodingSpecificOperations();
	StartITBlock(firstcond, mask);
	*/
	else{
		EncodingSpecificOperations();
		StartITBlock(ifThenInstruction.cond, ifThenInstruction.mask);
	}
}

/*
	No Operation does nothing.
*/
void thumb_no_operation(short i) {
	return;	// Do nothing
}

/*
	YIELD is a hint instruction. It allows software with a multithreading capability to indicate to the hardware
	that it is performing a task, for example a spinlock, that could be swapped out to improve overall system 
	performance. Hardware can use this hint to suspend and resume multiple code threads if it supports the 
	capability.
*/
void thumb_yield(short i) {
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		Hint_Yield();
	*/
	if (ConditionPassed(15)) {
		EncodingSpecificOperations();
		Hint_Yield();
	}
}

/*
	Wait For Event is a hint instruction. If the Event Register is clear, it suspends execution in the lowest power 
	state available consistent with a fast wakeup without the need for software restoration, until a reset, 
	exception or other event occurs. See WaitForEvent() on page AppxA-29 for more details.
*/
void thumb_wait_for_event(short i) {
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		if EventRegistered() then
			ClearEventRegister();
		else
			WaitForEvent();
	*/
	if (ConditionPassed(15)) {
		EncodingSpecificOperations();
		if (EventRegistered()) {
			ClearEventRegister();
		} else {
			WaitForEvent();
		}
	}
}

/*
	Wait For Interrupt is a hint instruction. It suspends execution, in the lowest power state available consistent 
	with a fast wakeup without the need for software restoration, until a reset, asynchronous exception or other  
	event occurs. See WaitForInterrupt() on page AppxA-29 for more details.
*/
void thumb_wait_for_interrupt(short i) {
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		WaitForInterrupt();
	*/
	if (ConditionPassed(15)) {
		EncodingSpecificOperations();
		WaitForInterrupt();
	}
}

/*
	Send Event is a hint instruction. It causes an event to be signaled to all CPUs within the multiprocessor 
	system.
*/
void thumb_send_event(short i) {
	/*
	if ConditionPassed() then
	    EncodingSpecificOperations();
	    Hint_SendEvent();
	*/
	if (ConditionPassed(15)) {
	    EncodingSpecificOperations();
		Hint_SendEvent();
	}
}

/*
	Branch causes a branch to a target address.
*/
void thumb_conditional_branch(short i) {
	int imm32;
	*((short *)(&conditionalBranch)) = i;

	/*
	imm32 = SignExtend(imm8:'0', 32);
	if cond == '1110' then SEE Permanently undefined space on page A4-37;
	if cond == '1111' then SEE SVC (formerly SWI) on page A5-285;
	if InITBlock() then UNPREDICTABLE;
	*/

	// SignExtend
	if (conditionalBranch.imm8 & 0x80) {
		imm32 = (0xffffff00 | conditionalBranch.imm8)<<1;
	} else {
		imm32 = conditionalBranch.imm8<<1;
	}

	if (conditionalBranch.cond == 0xE) {
		printf("	Undefined instruction: 0x%x! \n", i);
	}
	else if (conditionalBranch.cond == 0xF) {
		thumb_service_call(i);
	}
	else if (InITBlock()) {
		printf("	it is unpredictable! \n");
	}
	/*
	if ConditionPassed() then
		EncodingSpecificOperations();
		BranchWritePC(PC + imm32);
	*/
	else if (ConditionPassed(conditionalBranch.cond)) {
		EncodingSpecificOperations();
		BranchWritePC(get_pc() + imm32);
     	set_pc(get_pc()+2);//modified

	}
}

/*
	Branch causes a branch to a target address.
*/
void thumb_unconditional_branch(short i) {
	int imm32;
	*((short *)(&unconditionalBranch)) = i;
	
	/*
	imm32 = SignExtend(imm11:'0', 32);
	if InITBlock() && !LastInITBlock() then UNPREDICTABLE;
	*/
	
	// SignExtend
	if (unconditionalBranch.imm11 & 0x00000400) {
		imm32 = 0xfffff000 | unconditionalBranch.imm11<<1;
	} else {
		imm32 = unconditionalBranch.imm11<<1;
	}

	if (InITBlock() && !LastInITBlock()) {
		printf("	it is unpredictalbe! \n");
	}

	/*
	if ConditionPassed(15) then
		EncodingSpecificOperations();
		BranchWritePC(PC + imm32);
	*/
	else if (true) {
		EncodingSpecificOperations();
		BranchWritePC(get_pc() + imm32);
		set_pc(get_pc()+2);//modified

	}
}

void thumb_service_call(short instruction)
{
	int imm32;
	*((short*) (&SVCall)) = instruction;
	imm32 = SVCall.imm8;
#if DEBUG
	printf("thumb_service_call : 0x%x\n",instruction);
	printf("imm8 : 0x%x\n", SVCall.imm8);
#endif
	CallSupervisor();
}