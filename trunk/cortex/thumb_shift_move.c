

#include <stdio.h>
#include "instruction.h"
#include "thumb_shift_move.h"
#include "helper_procedures.h"
#include "register.h"



void thumb_shift_move(short ins)
{
	func p;
	int index;
	*((short*)&DataShiftMove)=ins;
	
	#if DEBUG
	
	printf("shift_move: ins is %d\n",ins);
	printf("shift_move: op is %d\n",DataShiftMove.op);
	
	#endif

	if(DataShiftMove.op==0 && DataShiftMove.imm5 ==0)
	{
		index =0;
	}
	else if(DataShiftMove.op==0 && DataShiftMove.imm5 !=0)
	{
		index=1;
	}
	else if(DataShiftMove.op ==1)
	{
		index =2;
	}
	else if(DataShiftMove.op==2)
	{
		index =3;
	}
	else if(DataShiftMove.op ==3 && ((DataShiftMove.imm5&0x10)==0x00))
	{
		thumb_add_sub_reg(ins);
		return ;
	}
	else if(DataShiftMove.op=3 && ((DataShiftMove.imm5&0x10)==0x10))
	{
		thumb_add_sub_imm(ins);
		return ;
	}
	else 
	{
		thumb_shift_move_err(ins);
		return ;
	}
	
	p=(func)data_shift_move_process[index];
	p(ins);
	
	
	
}

void thumb_shift_move_err(short ins)
{
	printf("shift_move_err: ins is %d\n",ins);
}


void thumb_mov_reg_t2(short ins)
{
	int result;
	int apsr_c;
	*((short*)&DataShiftMove)=ins;
	
	if(InITBlock())
	{
		printf("mov_reg: unpredictable!\n");
		return ;
		
	}
		
	apsr_c = get_flag_c();
	
	result=get_general_register((int)DataShiftMove.Rm);
	set_general_register((int)DataShiftMove.Rd, result);
	
	/************* set or cle flags **********/
	
	if(result & 0x8000 !=0)
		set_flag_n();
	else
		cle_flag_n();
	
	if(result == 0)
		set_flag_z();
	else
		cle_flag_z();
		
	if(apsr_c)//whether carry
		set_flag_c();
	else
		cle_flag_c();
	printf("*********thumb_mov_reg_t2***********\n");
				
}

void thumb_lsl_imm5(short ins)
{
	int result;
	struct RESULTCARRY *rc;//=lsl_c(result,(int)DataShiftMove.imm5);

	*((short*)&DataShiftMove)=ins;	
	
	result=get_general_register((int)DataShiftMove.Rm);
	rc = lsl_c(result,(int)DataShiftMove.imm5);
	set_general_register((int)DataShiftMove.Rd, rc->result);
	
	
	if(!InITBlock())
	{
		/********* set or cle flags ************/
		if(rc->result & 0x8000 !=0)
			set_flag_n();
		else
			cle_flag_n();
		
		if(rc->result == 0)
			set_flag_z();
		else
			cle_flag_z();
			
		if(rc->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		
	}
	printf("*********thumb_lsl_imm5***********\n");
	
}

void thumb_lsr_imm5(short ins)
{
	unsigned int result;
	struct RESULTCARRY *rc;

	*((short *)&DataShiftMove)=ins;		
	result=(unsigned)get_general_register((int)DataShiftMove.Rm);			
	rc = lsr_c(result,(unsigned)DataShiftMove.imm5);
	set_general_register((int)DataShiftMove.Rd, (int)rc->result);
	
	
	if(!InITBlock())
	{
		/********* set or cle flags ************/
		if(rc->result & 0x8000 !=0)
			set_flag_n();
		else
			cle_flag_n();
		
		if(rc->result == 0)
			set_flag_z();
		else
			cle_flag_z();
			
		if(rc->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		
	}
	printf("*********thumb_lsr_imm5***********\n");
	
}

void thumb_asr_imm5(short ins)
{
	int result;
	struct RESULTCARRY *rc;
	*((short *)&DataShiftMove)=ins;
		
	result=get_general_register((int)DataShiftMove.Rm);
	rc = asr_c(result,(unsigned)DataShiftMove.imm5);
	set_general_register((int)DataShiftMove.Rd, rc->result);
	
	
	if(!InITBlock())
	{
		/********* set or cle flags ************/
		if(rc->result & 0x8000 !=0)
			set_flag_n();
		else
			cle_flag_n();
		
		if(rc->result == 0)
			set_flag_z();
		else
			cle_flag_z();
			
		if(rc->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
		
	}
	printf("*********thumb_asr_imm5***********\n");
}


