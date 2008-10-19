#include <stdio.h>
#include "instruction.h"
#include "helper_procedures.h"
#include "register.h"
#include "thumb_add_sub_imm.h"

void thumb_add_sub_imm(short ins)
{
	func p;
	*((short *)&DataAddSubImm)=ins;
	
	#if DEBUG
	
	printf("shift_move: ins is %d\n",ins);
	printf("shift_move: op is %d\n",DataAddSubImm.opc);
	
	#endif
	
	

	p=(func)data_add_sub_imm_process[(int)DataAddSubImm.opc];
	(p)(ins);
}

void thumb_add_sub_imm_err(short ins)
{
	printf("shift_move_err: ins is %d\n",ins);
}

void thumb_add_imm(short ins)
{
	
	
	struct CALCULATECO *result;
	
	int n;
	int imm;
	*((short *)&DataAddSubImm)=ins;
	n=get_general_register(DataAddSubImm.Rn);
	imm=(int)(DataAddSubImm.imm3);
	
	result=addwithcarry(n,imm,0);
	
	set_general_register(DataAddSubImm.Rd,result->result);
	
	if(!InITBlock())
	{
		if(result->result & 0x8000 !=0)
			set_flag_n();
		else
			cle_flag_n();
		
		if(result->result == 0)
			set_flag_z();
		else
			cle_flag_z();
			
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
			
		if(result->overflow)
			set_flag_v();
		else
			cle_flag_v();			
	}
	printf("*********thumb_add_reg_t1***********\n");
}


void thumb_sub_imm(short ins)
{
	
	
	struct CALCULATECO *result;
	
	int n;
	int imm;
	*((short *)&DataAddSubImm)=ins;
	n=get_general_register(DataAddSubImm.Rn);
	imm=(int)(DataAddSubImm.Rn);
	result=addwithcarry(n,~imm,1);
	
	set_general_register(DataAddSubImm.Rd,result->result);
	
	if(!InITBlock())
	{
		if(result->result & 0x8000 !=0)
			set_flag_n();
		else
			cle_flag_n();
		
		if(result->result == 0)
			set_flag_z();
		else
			cle_flag_z();
			
		if(result->carry_out)//whether carry
			set_flag_c();
		else
			cle_flag_c();
			
		if(result->overflow)
			set_flag_v();
		else
			cle_flag_v();			
	}
	printf("*********thumb_add_reg_t1***********\n");
}



