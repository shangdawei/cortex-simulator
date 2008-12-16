#include <stdio.h>
#include "instruction.h"
#include "helper_procedures.h"
#include "register.h"
#include "thumb_add_sub_reg.h"

void thumb_add_sub_reg(short ins)
{
	func p;
	*((short *)&DataAddSubReg)=ins;
	
	#if DEBUG
	
	printf("shift_move: ins is %d\n",ins);
	printf("shift_move: op is %d\n",DataAddSubReg.opc);
	
	#endif
	
	p=(func)data_add_sub_reg_process[(int)DataAddSubReg.opc];
	p(ins);
}

void thumb_add_sub_reg_err(short ins)
{
	printf("shift_move_err: ins is %d\n",ins);
}

void thumb_add_reg_t1(short ins)
{
	
	

	
	int n;
	int m;
	struct CALCULATECO *result;
	*((short *)&DataAddSubReg)=ins;
	n=get_general_register((int)DataAddSubReg.Rn);
	m=get_general_register((int)DataAddSubReg.Rm);

	result=addwithcarry(m,n,0);
	
	set_general_register((int)DataAddSubReg.Rd,result->result);
	
	if(!InITBlock())
	{
		if((result->result & 0x8000) !=0)
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
	//printf("*********thumb_add_reg_t1***********\n");
}


void thumb_sub_reg(short ins)
{
	
	
	struct CALCULATECO *result;
	
	int n;
	int m;
	*((short *)&DataAddSubReg)=ins;
	n=get_general_register((int)DataAddSubReg.Rn);
	m=get_general_register((int)DataAddSubReg.Rm);

	
	result=addwithcarry(n,~m,1);
	
	set_general_register((int)DataAddSubReg.Rd,result->result);
	
	if(!InITBlock())
	{
		if((result->result & 0x8000) !=0)
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
	//printf("*********thumb_sub_reg***********\n");
}



