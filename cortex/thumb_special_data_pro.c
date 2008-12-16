#include "stdio.h"
#include "thumb_special_data_pro.h"
#include "memory.h"
#include "instruction.h"
#include <assert.h>

//special data processing
void thumb_sepecial_data_pro(short instruction)
{
	int index;
	func f_ptr;
	*((short*) (&SpecialDataProcessing)) = instruction;
	index  = SpecialDataProcessing.op;
#if DEBUG

	printf("thumb_sepecial_data_pro : 0x%x\n", instruction);
	printf("Rdn : 0x%x, Rm : 0x%x, DN : 0x%x, Op : 0x%x\n",
		SpecialDataProcessing.rdn, SpecialDataProcessing.rm, SpecialDataProcessing.dn, SpecialDataProcessing.op);
#endif
	f_ptr = special_data_processing[index];
	f_ptr(instruction);
}

void thumb_add_reg(short instruction)
{
	int rd, rn, rm;
	//int flag;
	int shift_t, shift_n, shifted;
	struct CALCULATECO* r;
	//flag = 0;
	*((short*) (&SpecialDataProcessing)) = instruction;
	rm = SpecialDataProcessing.rm;
	rd = rn = SpecialDataProcessing.rdn + 8 * SpecialDataProcessing.dn;
	/*if ((rd >= $R8 && rd<= $R12) || rd == $LR || rd == $PC) 
		flag = 1;
	else if ((rm >= $R8 && rm<= $R12) || rm == $LR || rm == $PC) 
		flag = 1;
	if (!flag) {
		printf("condition not pass\n");
	}else{*/
	shift_t = SRType_None;
	shift_n = 0;
	shifted = shift(get_general_register(rm), shift_t, shift_n, get_flag_c());
	if (rd == 13 || rm == 13){						
		r = addwithcarry((unsigned int)get_general_register($SP), (unsigned int)shifted, 0);
		set_general_register(rd, r->result);
		free(r);
	}else{			
		r = addwithcarry((unsigned int)get_general_register(rn), (unsigned int)shifted, 0);
		if (rd == $PC)
			ALUWritePC(r->result);
		else
			set_general_register(rd, r->result);
		free(r);
	}
	//printf("*********thumb_add_reg***********\n");
}

void thumb_cmp_reg(short instruction)
{
	int rn, rm;
	int shift_t, shift_n, shifted;
	struct CALCULATECO* r;
	*((short*) (&SpecialDataProcessing)) = instruction;
	rm = SpecialDataProcessing.rm;
	rn = SpecialDataProcessing.rdn + 8 * SpecialDataProcessing.dn;
	shift_t = SRType_None;
	shift_n = 0;
	if (rn < 8 && rm < 8) 
		printf("    it is unpredictable!\n");
	else if (rn == 15)
		printf("    it is unpredictable!\n");
	else{
		shifted = shift(get_general_register(rm), shift_t, shift_n, get_flag_c());		
		r = addwithcarry((unsigned int)get_general_register(rn), ((unsigned int) ~shifted), 1);
		if (r->result & 0x80000000) set_flag_n(); else cle_flag_n();
		if (!r->result) set_flag_z(); else cle_flag_z();
		if (r->carry_out) set_flag_c(); else cle_flag_c();
		if (r->overflow) set_flag_v(); else cle_flag_v();
	}
	//printf("*********thumb_cmp_reg***********\n");
}

void thumb_mov_reg(short instruction)
{
	int rd, rm, result;	
	*((short*) (&SpecialDataProcessing)) = instruction;
	rm = SpecialDataProcessing.rm;
	rd = SpecialDataProcessing.rdn + 8 * SpecialDataProcessing.dn;
	if (rd == 15 && InITBlock() && !LastInITBlock())
		printf("    it is unpredictable!\n");
	result = get_general_register(rm);
	if (rd == 15){
		ALUWritePC(result);
	}else{
		set_general_register(rd, result);
	}
	//printf("*********thumb_mov_reg***********\n");
}