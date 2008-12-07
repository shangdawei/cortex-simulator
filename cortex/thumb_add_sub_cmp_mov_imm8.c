
#include <stdio.h>
#include "instruction.h"
#include "helper_procedures.h"
#include "register.h"
#include "thumb_add_sub_cmp_mov_imm8.h"

void thumb_add_sub_cmp_mov_imm8(short ins)
{
	func p;
	*((short *)&DataAddSubCmpMovImm8)=ins;	
	
	p=(func)data_add_sub_cmp_mov_imm8_process[(int)DataAddSubCmpMovImm8.opc];
	(p)(ins);
	
	
}

void thumb_add_sub_cmp_mov_imm8_err(short ins)
{
	
	printf("add_sub_cmp_mov_imm8_err: ins is %d\n",ins);
}

void thumb_mov_imm8(short ins)
{
	unsigned result=(unsigned)DataAddSubCmpMovImm8.imm8;
	int carry=get_flag_c();
	*((short *)&DataAddSubCmpMovImm8)=ins;
			
	set_general_register((int)DataAddSubCmpMovImm8.Rdn,result);
	
	if(!InITBlock())
	{
		if(result & 0x8000 !=0)
			set_flag_n();
		else
			cle_flag_n();
		
		if(result == 0)
			set_flag_z();
		else
			cle_flag_z();
			
		if(carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
	printf("*********thumb_mov_imm8***********\n");
}


void thumb_cmp_imm8(short ins)
{
	struct CALCULATECO *result;
	unsigned imm;
	unsigned Rdn;
	*((short *)&DataAddSubCmpMovImm8)=ins;
	imm =(unsigned)DataAddSubCmpMovImm8.imm8;
	Rdn=(unsigned)get_general_register(DataAddSubCmpMovImm8.Rdn);		
	result=(struct CALCULATECO *)addwithcarry(Rdn,~imm,1);
	
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
	printf("*********thumb_cmp_imm8***********\n");
}

void thumb_add_imm8(short ins)
{
	
	struct CALCULATECO *result;
	unsigned imm;
	unsigned Rdn;
	*((short *)&DataAddSubCmpMovImm8)=ins;
	imm=(unsigned)DataAddSubCmpMovImm8.imm8;
	Rdn=(unsigned)get_general_register(DataAddSubCmpMovImm8.Rdn);
	result=(struct CALCULATECO *)addwithcarry(Rdn,imm,0);
	
	set_general_register((int)DataAddSubCmpMovImm8.Rdn,result->result);
	
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
	printf("*********thumb_add_imm8***********\n");
	
}

void thumb_sub_imm8(short ins)
{
	
	struct CALCULATECO *result;
	unsigned imm;
	unsigned Rdn;
	*((short *)&DataAddSubCmpMovImm8)=ins;
	imm=(unsigned)DataAddSubCmpMovImm8.imm8;
	Rdn=(unsigned)get_general_register(DataAddSubCmpMovImm8.Rdn);
	
	result=(struct CALCULATECO *)addwithcarry(Rdn,~imm,1);
	
	set_general_register((int)DataAddSubCmpMovImm8.Rdn,result->result);
	
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
	printf("*********thumb_sub_imm8***********\n");
	
}



