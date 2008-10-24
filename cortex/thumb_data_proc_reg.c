
#include <stdio.h>
#include "instruction.h"
#include "helper_procedures.h"
#include "register.h"
#include "thumb_data_proc_reg.h"


void thumb_data_proc_reg(short i)
{
	
	short opc;
	func p;
	*((short *)&DataProcReg)=i;
	opc=(int)DataProcReg.opc;
	if(opc<0 || opc>15)
	{
		thumb_data_proc_reg_err(i);
		return;
	}
	
	p=(func)data_proc_reg_process[opc];
	(p)(i);
}



void thumb_data_proc_reg_err(short i)
{
	printf("data_proc_reg_err: i is %d\n",i);
}
   
void thumb_and_reg(short i)
{
	
	
	int carry=get_flag_c();
	
	unsigned n;
	unsigned m;
	
	unsigned result;
	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register(DataProcReg.Rdn);
	m=(unsigned)get_general_register(DataProcReg.Rm);
	result=n & m;

	set_general_register((int)DataProcReg.Rdn,(int)result);
	
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
	printf("*********thumb_and_reg***********\n");
	
	
}


void thumb_eor_reg(short i)
{
	
	
	unsigned result,m,n,apsr_c;
	
	
	//int carry;
	
	struct RESULTCARRY *rc;
	*((short *)&DataProcReg)=i;
	n = (unsigned)get_general_register((int)DataProcReg.Rdn);
	m = (unsigned)get_general_register((int)DataProcReg.Rm);
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;
	rc=shift_c(m,SRType_None,0,apsr_c);
	//set_general_register((int)DataProcReg.Rdn, rc->result);
	
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
		
	};
	
	//carry=get_flag_c();
	
	//n=(unsigned)get_general_register(DataProcReg.Rdn);
	//m=(unsigned)get_general_register(DataProcReg.Rm);
	
	result = n^rc->result;
	
	set_general_register((int)DataProcReg.Rdn,(int)result);
	
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
			
		if(rc->carry)//whether carry
			set_flag_c();
		else
			cle_flag_c();
	}
	printf("*********thumb_eor_reg***********\n");
	
}



void thumb_lsl_reg(short i)
{
	struct RESULTCARRY *rc;
	
	int result,shift;

	*((short *)&DataProcReg)=i;
	result=get_general_register((int)DataProcReg.Rdn);
	shift=(get_general_register((int)DataProcReg.Rm) & 0xff);
	
	
	rc=lsl_c(result,shift);
	
	set_general_register((int)DataProcReg.Rdn, rc->result);
	
	
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
	printf("*********thumb_lsl_reg***********\n");
}

   
void thumb_lsr_reg(short i)
{
	
	struct RESULTCARRY *rc;
	unsigned result,shift,apsr_c;

	*((short *)&DataProcReg)=i;
	result=(unsigned)get_general_register((int)DataProcReg.Rdn);
	shift=(unsigned)(get_general_register((int)DataProcReg.Rm) & 0xff);
	apsr_c = get_flag_c();
	apsr_c = apsr_c >> 29;	
	
	rc=shift_c(result,SRType_LSR,shift,apsr_c);//lsr_c(result,shift);
	
	set_general_register((int)DataProcReg.Rdn, rc->result);
	
	
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
	printf("*********thumb_lsr_reg***********\n");
}
   
void thumb_asr_reg(short i)
{
	
	struct RESULTCARRY *rc;
	unsigned shift;
	int result;

	*((short *)&DataProcReg)=i;
	result=get_general_register((int)DataProcReg.Rdn);
	shift=(unsigned)(get_general_register((int)DataProcReg.Rm) & 0xff);
	
	
	rc=asr_c(result,shift);
	
	set_general_register((int)DataProcReg.Rdn, rc->result);
	
	
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
	printf("*********thumb_asr_reg***********\n");
}



void thumb_adc_reg(short i)
{
	unsigned m,n,carry;
	
	struct CALCULATECO *result;
	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register((int)DataProcReg.Rdn);
	m=(unsigned)get_general_register((int)DataProcReg.Rm);
	carry=(unsigned)get_flag_c();

	
	result=addwithcarry(m,n,carry);
	
	set_general_register((int)DataProcReg.Rdn,result->result);
	
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
	printf("*********thumb_adc_reg***********\n");
}


void thumb_sbc_reg(short i)
{
	unsigned m,n,carry;
	
	struct CALCULATECO *result;

	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register((int)DataProcReg.Rdn);
	m=(unsigned)get_general_register((int)DataProcReg.Rm);
	carry=(unsigned)get_flag_c();

	
	result=addwithcarry(n,~m,carry);
	
	set_general_register((int)DataProcReg.Rdn,result->result);
	
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
	printf("*********thumb_sbc_reg***********\n");
}


void thumb_ror_reg(short i)
{
	
	struct RESULTCARRY *rc;
	unsigned shift;
	unsigned result;

	*((short *)&DataProcReg)=i;
	result=(unsigned)get_general_register((int)DataProcReg.Rdn);
	shift=(unsigned)(get_general_register((int)DataProcReg.Rm) & 0xff);
	
	
	rc=ror_c(result,shift);
	
	set_general_register((int)DataProcReg.Rdn, rc->result);
	
	
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
	printf("*********thumb_ror_reg***********\n");
} 
   
void thumb_tst_reg(short i)
{
	
	unsigned m,n,result;
	int carry=get_flag_c();

	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register(DataProcReg.Rdn);
	m=(unsigned)get_general_register(DataProcReg.Rm);
	
	result=n & m;
	
	
	
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
	printf("*********thumb_tst_reg***********\n");
}


void thumb_rsb_reg(short i)
{
	
	unsigned n,m;
	struct CALCULATECO *result;

	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register((int)DataProcReg.Rdn);
	m=0;

	
	result=addwithcarry(~n,m,1);
	
	set_general_register((int)DataProcReg.Rdn,result->result);
	
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
	printf("*********thumb_rsb_reg***********\n");
}



void thumb_cmp_reg_t1(short i)
{
	unsigned Rdn,Rm;
	struct CALCULATECO *result;

	*((short *)&DataProcReg)=i;
	Rdn=get_general_register((int)DataProcReg.Rdn);
	Rm=get_general_register((int)DataProcReg.Rm);
	
	
	result=addwithcarry(Rdn,~Rm,1);
	
	if(InITBlock())
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
	printf("*********thumb_cmp_reg_t1***********\n");
}


void thumb_cmn_reg(short i)
{
	unsigned Rdn,Rm;
	struct CALCULATECO *result;

	*((short *)&DataProcReg)=i;
	Rdn=get_general_register((int)DataProcReg.Rdn);
	Rm=get_general_register((int)DataProcReg.Rm);
	
	
	result=addwithcarry(Rdn,Rm,0);
	
	if(InITBlock())
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
	printf("*********thumb_cmn_reg***********\n");
}
   
void thumb_orr_reg(short i)
{
	
	unsigned n,m,result;
	int carry=get_flag_c();
	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register(DataProcReg.Rdn);
	m=(unsigned)get_general_register(DataProcReg.Rm);
	
	result=n | m;
	
	set_general_register((int)DataProcReg.Rdn,(int)result);
	
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
	printf("*********thumb_orr_reg***********\n");
}


void thumb_mul_reg(short i)
{
	
	unsigned n,m,result;
	int carry=get_flag_c();
	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register(DataProcReg.Rdn);
	m=(unsigned)get_general_register(DataProcReg.Rm);
	
	result=n * m;
	
	if(ArchVersion()<6 && result==m)
	{
		printf("mul_reg:unpredictable!\n");
		return;
	}
	
	set_general_register((int)DataProcReg.Rm,result);
	
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
			
		if(ArchVersion()==4)
			printf("mul_reg:flag_c unknow!\n");
	}
	printf("*********thumb_mul_reg***********\n");
}

void thumb_bic_reg(short i)
{
	unsigned n,m,result;
	
	int carry=get_flag_c();
	*((short *)&DataProcReg)=i;
	n=(unsigned)get_general_register(DataProcReg.Rdn);
	m=(unsigned)get_general_register(DataProcReg.Rm);
	
	result=n & (~m);
	
	set_general_register((int)DataProcReg.Rdn,(int)result);
	
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
	printf("*********thumb_bic_reg***********\n");
}

void thumb_mvn_reg(short i)
{
	
	
	unsigned result;
	int carry;
	*((short *)&DataProcReg)=i;
	result=(unsigned)get_general_register(DataProcReg.Rm);
	carry=get_flag_c();
	set_general_register((int)DataProcReg.Rdn,~result);
	
	if(InITBlock())
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
	printf("*********thumb_mvn_reg***********\n");
}


