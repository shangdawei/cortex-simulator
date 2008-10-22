/**
 *
 * This file is to define the function to handle the branch, miscellaneous control instructions
 * these function would be saved as function point
 * in the TranslateTable.point field
 *
 */
#include "branch_misc.h" 
/**
 *
 *To define the struct to handle the instruction
 *
 */ 
void err_branch(int i)
{
	printf("the branch instruction 0x%x is error in this situation!",i);
}

void branch_instr(int instruction)
{
	func f_ptr;
	*((int *)(&branch)) = instruction;
	printf("branch instruction: 0x%x \n",instruction);
	printf("offset1 = %x\n",branch.off1);
	printf("j2 = %x\n",branch.j2);
	printf("pass1 = %x\n",branch.pass1);
	printf("j1 = %x\n",branch.j1);
	printf("pass2 = %x\n",branch.pass2);
	printf("pass3 = %x\n",branch.pass3);
	printf("offset2 = %x\n",branch.off2);
	printf("S = %x\n",branch.s);
	printf("pass4 = %x\n",branch.pass4);
	f_ptr=(void*) branch_i[0];
	f_ptr(instruction);

}

void branch_with_link(int instruction)
{
	func f_ptr;
	*((int*)(&branchWithLink))=instruction;
	printf("branch with link instruction: 0x% \n",instruction);
	printf("offset1 = %x\n",branchWithLink.off1);
	printf("J2 = %x\n",branchWithLink.j2);
	printf("pass1 = %x\n",branchWithLink.pass1);
	printf("J1 = %x\n",branchWithLink.j1);
	printf("pass2 = %x\n",branchWithLink.pass2);
	printf("pass3 = %x\n",branchWithLink.pass3);
	printf("offset2 = %x\n",branchWithLink.off2);
	printf("S = %x\n",branchWithLink.s);
	printf("pass4 = %x\n",branchWithLink.pass4);
	f_ptr=(void*)branch_with_l[0];
    f_ptr(instruction);

}
void conditional_branch(int instruction)
{
	func f_ptr;
	*((int*)(&conditionalBranch))=instruction;
	printf("Conditional Branch instruction: 0x% \n",instruction);
	printf("offset1 = %x\n",conditionalBranch.off1);
	printf("J2 = %x\n",conditionalBranch.j2);
	printf("pass1 = %x\n",conditionalBranch.pass1);
	printf("J1 = %x\n",conditionalBranch.j1);
	printf("pass2 = %x\n",conditionalBranch.pass2);
	printf("offset2 = %x\n",conditionalBranch.off2);
	printf("cond = %x\n",conditionalBranch.cond);
	printf("S = %x\n",conditionalBranch.s);
	printf("pass3 = %x\n",conditionalBranch.pass3);
	f_ptr=(void*)conditional_b[0];
	f_ptr(instruction);

}
void move_to_status(int instruction)
{
	func f_ptr;
	*((int*)(&moveToStatus))=instruction;
	printf("move to status from register instruction: 0x% \n",instruction);
	printf("SYSm = %x\n",moveToStatus.sysm);
	printf("pass1 = %x\n",moveToStatus.pass1);
	printf("pass2 = %x\n",moveToStatus.pass2);
	printf("pass3 = %x\n",moveToStatus.pass3);
	printf("pass4 = %x\n",moveToStatus.pass4);
	printf("Rn = %x\n",moveToStatus.rn);
	printf("pass5 = %x\n",moveToStatus.pass5);
	printf("pass6 = %x\n",moveToStatus.pass6);
	printf("pass7 = %x\n",moveToStatus.pass7);
	printf("pass8 = %x\n",moveToStatus.pass8);
	printf("pass9 = %x\n",moveToStatus.pass9);
	f_ptr=(void*)move_to_s[0];
	f_ptr(instruction);

}
void no_op_hints(int instruction)
{
	int index;
	func f_ptr;
	*((int*)(&noOpHints))=instruction;
	printf("No operation & hints instruction: 0x%\n",instruction);
	printf("hint = %x\n",noOpHints.hint);
	printf("pass1 = %x\n",noOpHints.pass1);
	printf("pass2 = %x\n",noOpHints.pass2);
	printf("pass3 = %x\n",noOpHints.pass3);
	printf("pass4 = %x\n",noOpHints.pass4);
	printf("pass5 = %x\n",noOpHints.pass5);
	printf("pass6 = %x\n",noOpHints.pass6);
	printf("pass7 = %x\n",noOpHints.pass7);
	printf("pass8 = %x\n",noOpHints.pass8);
	printf("pass9 = %x\n",noOpHints.pass9);
	printf("pass10 = %x\n",noOpHints.pass10);
	printf("pass11 = %x\n",noOpHints.pass11);

	if(noOpHints.hint<=4)
		index=noOpHints.hint;
	else if(noOpHints.hint>=240 && noOpHints.hint<=255)
		index=5;
	else
		index=-1;
				
	if(index==-1)
		branch_reserved(instruction);
	else{
		printf("Index is : %d\n",index);
		f_ptr=(void*)no_op_h[index];
		f_ptr(instruction);
	}
}

void special_ctrl_operations(int instruction)
{
	int index;
	func f_ptr;
	*((int*)(&specialCtrlOp))=instruction;
	printf("Special control operations instruction: 0x%x\n",instruction);
	printf("option = %x\n",specialCtrlOp.option);
	printf("opcode = %x\n",specialCtrlOp.opcode);
	printf("pass1 = %x\n",specialCtrlOp.pass1);
	printf("pass2 = %x\n",specialCtrlOp.pass2);
	printf("pass3 = %x\n",specialCtrlOp.pass3);
	printf("pass4 = %x\n",specialCtrlOp.pass4);
	printf("pass5 = %x\n",specialCtrlOp.pass5);
	printf("pass6 = %x\n",specialCtrlOp.pass6);
	printf("pass7 = %x\n",specialCtrlOp.pass7);
	printf("pass8 = %x\n",specialCtrlOp.pass8);
	printf("pass9 = %x\n",specialCtrlOp.pass9);
	printf("pass10 = %x\n",specialCtrlOp.pass10);
	
	index=specialCtrlOp.opcode;
	f_ptr=(void*) special_ctrl_o[index];
	f_ptr(instruction);
}
void move_to_reg(int instruction)
{
	func f_ptr;
	*((int*)(&moveToReg))=instruction;
	printf("Move to register from status instruction:%x\n",instruction);
	printf("SYSm = %x\n",moveToReg.sysm);
	printf("Rd = %x\n",moveToReg.rd);
	printf("pass1 = %x\n",moveToReg.pass1);
	printf("pass2 = %x\n",moveToReg.pass2);
	printf("pass3 = %x\n",moveToReg.pass3);
	printf("pass4 = %x\n",moveToReg.pass4);
	printf("pass5 = %x\n",moveToReg.pass5);
	printf("pass6 = %x\n",moveToReg.pass6);
	printf("pass7 = %x\n",moveToReg.pass7);
	printf("pass8 = %x\n",moveToReg.pass8);
	printf("pass9 = %x\n",moveToReg.pass9);
	f_ptr=(void*)move_to_r[0];
	f_ptr(instruction);

}
void branch_reserved(int instrution)
{
	printf("branch reserved instruction!");
}



void b_t3(int i)
{
/*
imm32 = SignExtend(S:J2:J1:imm6:imm11:'0', 32);
if cond<3:1> == '111' then
SEE Branches, miscellaneous control instructions on page A4-30;
if InITBlock() then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
BranchWritePC(PC + imm32);
*/
	int imm32;
	*((int*)(&conditionalBranch))=i;
	imm32=conditionalBranch.s<<20+conditionalBranch.j2<<19+conditionalBranch.j1>>18+
		  conditionalBranch.off2<<17+conditionalBranch.off1<<1;
	imm32 &= 0xFFFFFFFE;
	//SignExtend
	if(imm32 & 0x00100000)
		imm32 |= 0xFFE00000;
	else
		imm32 &= 0x001FFFFF;

	if(conditionalBranch.cond>=14){
	//question?
		printf("Error!Branch conditonal instruction,con<3:1>=111\n");
		return;
	}
	else if(InITBlock())
		printf("UNPREDICTABLE instruction\n");
	else{
		EncodingSpecificOperations();
		BranchWritePC(get_pc()+imm32);
	}
	


}
void b_t4(int i)
{
/*
I1 = NOT(J1 EOR S); I2 = NOT(J2 EOR S);
imm32 = SignExtend(S:I1:I2:imm10:imm11:'0', 32);
if InITBlock() && !LastInITBlock() then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
BranchWritePC(PC + imm32);
*/
	int imm32,i1,i2;
	*((int *)(&branch)) = i;
	i1=!(branch.j1^branch.s);
	i2=!(branch.j2^branch.s);
	imm32=(branch.s<<24)+(i1<<23)+(i2<<22)+(branch.off2<<12)+(branch.off1<<1);
	imm32 &= 0xFFFFFFFE;
	//SignExtend
	if(imm32 & 0x01000000)
		imm32 |= 0xFE000000;
	else
		imm32 &= 0x01FFFFFF;

	if(InITBlock() && !LastInITBlock())
		printf("UNPREDICTABLE instruction.\n");
	else{
		EncodingSpecificOperations();
		BranchWritePC(get_pc()+imm32);
	}

	
	
}
void bl(int i)
{
/*
I1 = NOT(J1 EOR S); I2 = NOT(J2 EOR S);
imm32 = SignExtend(S:I1:I2:imm10:imm11:'0', 32);
if InITBlock() && !LastInITBlock() then UNPREDICTABLE;
if ConditionPassed() then
EncodingSpecificOperations();
next_instr_addr = PC;
LR = next_instr_addr<31:1> : '1';
SelectInstrSet(InstrSet_Thumb);
BranchWritePC(PC + imm32);
*/
	int i1,i2,imm32,next_instr_addr;
	*((int *)(&branchWithLink)) = i;
	i1=!(branchWithLink.j1^branchWithLink.s);
	i2=!(branchWithLink.j2^branchWithLink.s);
	imm32=(branchWithLink.s<<24)+(i1<<23)+(i2<<22)+(branchWithLink.off2<<12)+(branchWithLink.off1<<1);
	imm32 &= 0xFFFFFFFE;
	//SignExtend
	if(imm32 & 0x01000000)
		imm32 |= 0xFE000000;
	else
		imm32 &= 0x01FFFFFF;
	if(InITBlock() && !LastInITBlock())
		printf("UNPREDICTABLE instruction.\n");
	else{
		EncodingSpecificOperations();
		next_instr_addr=get_pc();
		set_lr(next_instr_addr | 0x00000001);
		//SelectInstrSet(InstrSet_Thumb);           questionhi
		BranchWritePC(get_pc()+imm32);
	}
}
void mrs(int i)
{
/*P463

*/
	unsigned int n,result;
	*((int *)(&moveToReg)) = i;
	n=(unsigned int) moveToReg.rd;
	if(Bad_Reg(n))
		printf("UNPREDICTABLE instruciton\n");
	else{
		unsigned sysmTemp=moveToReg.sysm;
		result=0;
		sysmTemp=sysmTemp>>3;
		sysmTemp&=0x01F;
		if(sysmTemp==0){
			if(moveToReg.sysm&0x1 && CurrentModeIsPrivileged()){  //question
				result=get_ipsr();
				result &= 0x000000FF;
			}
			if(moveToReg.sysm&0x02){
				//result &= 0xF8FF03FF;
			}
			if(moveToReg.sysm&0x04){
				unsigned int temp=0;
				temp=get_apsr();
				temp=temp<<27;
				temp &= 0xF8000000;
				result &= 0x07FFFFFF;
				result = result | temp;
			}
		}
		else if(sysmTemp==1){
			if(CurrentModeIsPrivileged()){
				unsigned temp=moveToReg.sysm;
				temp &= 0x07;
				switch(temp){
					case 0:
						result=get_msp();
						break;
					case 1:
						result=get_psp();
						break;
				}
			}
		}
		else if(sysmTemp==2){
			unsigned temp=(moveToReg.sysm& 0x07);
			switch(temp){
				case 0:
					if(CurrentModeIsPrivileged()){
						result=get_primask();
						result &= 0x01;
					}
					else
						result &= 0x0;
					break;
				case 1:
					if(CurrentModeIsPrivileged()){
						result =get_basepri();
						result &= 0xFF;
					}
					else
						result &= 0x0;
					break;
				case 2:
					if(CurrentModeIsPrivileged()){
						result =get_basepri();
						result &= 0xFF;
					}
					else
						result &= 0x0;
					break;
				case 3:
					if(CurrentModeIsPrivileged()){
						result=get_faultmask();
						result &= 0x01;
					}
					else
						result &=0x0;
					break;
				case 4:
					result=get_control();
					result &= 0x03;
					break;
			}
		}
		
	}
	set_general_register(moveToReg.rd,result);
}
void msr(int i)
{
	unsigned int n; 
	*((int *)(&moveToStatus)) = i;
	n=(unsigned int) moveToStatus.rn;
	if(Bad_Reg(n))
		printf("UNPREDICTABLE instruciton\n");
	else{
		unsigned sysmTemp=moveToStatus.sysm;
		sysmTemp=sysmTemp>>3;
		sysmTemp&=0x01F;
		if(sysmTemp==0){
			if(!(moveToStatus.sysm & 0x04))
				set_apsr(get_general_register(moveToStatus.rn)>>27);
		}
		else if(sysmTemp==1){
			if(CurrentModeIsPrivileged()){
				if((moveToStatus.sysm & 0x07)==0)
					set_msp(get_general_register(moveToStatus.rn));
				else if((moveToStatus.sysm & 0x07)==1)
					set_psp(get_general_register(moveToStatus.rn));

			}
		}
		else if(sysmTemp==2){
			unsigned int temp=(moveToStatus.sysm & 0x07);
			if(temp==0 && CurrentModeIsPrivileged()){
				set_primask(get_general_register(moveToStatus.rn)&0x01);
			}
			else if(temp==1 && CurrentModeIsPrivileged()){
				set_basepri(get_general_register(moveToStatus.rn)&0xFF);
			}
			else if(temp==2 && CurrentModeIsPrivileged()){
				if((get_general_register(moveToStatus.rn)&0xFF)!=0 && ((get_general_register(moveToStatus.rn)&0xFF)!=0) && 
					(((get_general_register(moveToStatus.rn)&0xFF)<get_basepri()) || get_basepri()==0))
					set_basepri(get_general_register(moveToStatus.rn)&0xFF);
			}
			else if(temp==3 && CurrentModeIsPrivileged() && (ExecutionPriority() > -1)){
					set_faultmask(get_general_register(moveToStatus.rn)&0x01);
			}
			else if(temp==4 && CurrentModeIsPrivileged()){
				/* when `100`
						if CurrentModeIsPrivileged() then
						CONTROL<0> = R[n]<1:0>;
						If Mode == Thread then CONTROL<1> = R[n]<1>;

				*/// question
				set_control((get_control()&0xFFFFFFFE)|(get_general_register(moveToStatus.rn)&0x01));
			}
		}

	}
}


/*
 *
 *Table for dealing with no operation and hint instructions
 *
 */
void nop(int i)
{
// Do nothing
	if(ConditionPassed()){
		EncodingSpecificOperations();
		printf("nop\n");
	}
}
void yield(int i)
{
/*
if ConditionPassed() then
EncodingSpecificOperations();
Hint_Yield();
*/
	if(ConditionPassed()){
		EncodingSpecificOperations();
		Hint_Yield();
	}


}
void wfe(int i)
{
/*
if ConditionPassed() then
	EncodingSpecificOperations();
	if EventRegistered() then
		ClearEventRegister();
	else
		WaitForEvent();
*/
	if(ConditionPassed()){
		EncodingSpecificOperations();
		if(EventRegistered())
			ClearEventRegister();
		else
			WaitForEvent();
	}

}
void wfi(int i)
{
	if(ConditionPassed()){
		EncodingSpecificOperations();
		WaitForInterrupt();
	}
}

void sev(int i)
{
	if(ConditionPassed()){
		EncodingSpecificOperations();
		Hint_SendEvent();
	}
}
void dbg(int i)
{
	*((int *)(&specialCtrlOp)) = i;
	if(ConditionPassed()){
		EncodingSpecificOperations();
		Hint_Debug(specialCtrlOp.option);
	}
}


/*
 *
 *Table for dealing with special control operations
 *
 */
void clrex(int i)
{
	if(ConditionPassed()){
		EncodingSpecificOperations();
		ClearExclusiveMonitors();
	}
}
void dsb(int i)
{
	*((int *)(&specialCtrlOp)) = i;
	if(ConditionPassed()){
		EncodingSpecificOperations();
		DataSynchronizationBarrier(specialCtrlOp.option);
	}
}
void dmb(int i)
{
	*((int *)(&specialCtrlOp)) = i;
	if(ConditionPassed()){
		EncodingSpecificOperations();
		DataMemoryBarrier(specialCtrlOp.option);
	}
}
void isb(int i)
{
	*((int *)(&specialCtrlOp)) = i;
	if(ConditionPassed()){
		EncodingSpecificOperations();
		InstructionSynchronizationBarrier(specialCtrlOp.option);
	}
}