
/**
 * This file is to define 
 *	1)TranslatorTable
 *	2)int instruction, which means the current processing instruction
 *	3)initialize the table 
 *	4)fetch one 16-bit instruction
 *	5)decode
 * 
 */

#include "thumb_decode.h"
typedef struct {
	int mask;
	int value;
	void *point;
} TranslateTable;

typedef void (*func_ptr)(int);
	

TranslateTable thumbtable[MAXSIZE] = {
	//*************************************************************************************************
	{0xF000,0xB000,(unsigned char*)thumbtable+14*4}, //go to entry 14,which is to define Miscelllaneous
	
	//*************************************************************************************************
	//entry 2: all functions before Miscelllaneous
	{0xFC00,0x1800,(void*)thumb_add_sub_reg},  
	{0xFC00,0x1C00,(void*)thumb_add_sub_imm},
	{0xE000,0x0000,(void*)thumb_shift_move},
	{0xE000,0x2000,(void*)thumb_add_sub_cmp_mov_imm8},
	{0xF000,0x4000,(void*)thumb_data_proc_reg},
	{0xFF00,0x4700,(void*)thumb_sepecial_data_pro},
	{0xF800,0x4800,(void*)thumb_ldr_lit},
	{0xF000,0x5000,(void*)thumb_ld_st_reg_off},
	{0xE000,0x6000,(void*)thumb_ld_st_word_byte_imm_off},
	{0xF000,0x8000,(void*)thumb_ld_st_hw_imm_off},
	{0xF000,0x9000,(void*)thumb_ld_st_stack},
	{0xF000,0xA000,(void*)thumb_add_to_sp_or_pc},

	//entry 14: there should be functions belong to Miscellaneous
	{0xFF00,0xB000,(void*)thumb_adjust_stack_pointer},
	{0xFF00,0xB200,(void*)thumb_sign_zero_extend},
	{0xF500,0xB100,(void*)thumb_compare_and_branch},
	{0xF600,0xB400,(void*)thumb_push_pop_register_list},
	{0xFFEA,0xB662,(void*)thumb_change_processor_state},
	{0xFF00,0xBA00,(void*)thumb_reverse_bytes},
	{0xFF00,0xBE00,(void*)thumb_software_breakpoint},
	{0xFF0F,0xBF00,(void*)thumb_nop_compatible_hints},
	{0xFF00,0xBF00,(void*)thumb_if_then_instruction},

	//entry 23: all functions after Miscelllaneous
	{0xF000,0xC000,(void*)thumb_ld_st_multiple},
	{0xFF00,0xDE00,(void*)thumb_no_operation},
	{0xFF00,0xDF00,(void*)thumb_service_call},
	{0xF000,0xD000,(void*)thumb_conditional_branch},
	{0xF800,0xE000,(void*)thumb_unconditional_branch},
	{0x0000,0x0000,(void*)error_message}
};


/* 1) the function is used to decode the thumb-32 instruction.
 * 2) let the insruction AND with the table's entry's mask. 
 * 3) if it is match the table's entry's value.
 * 	 3.1 if the point is among 0--50, then it means the point is used to skip within the table, set the index == point; 
 *   3.2 if the point is not among 0--50,then it means the point is a function pointer, the use the function to handle the instruction.
 * 4) if it is not match the value, then set the index++, which means continue to match next entry in the table;
 * 5) the instuction would definitely machted, because there is one ErrorHandle entry to handle the exception instruction
 *
 *
 * 2 examples about how to use the function point
		func_ptr p =(func_ptr)table[7].point;
		(*p)(instruction);

		void (*p2)(int)=(void *)table[7].point;
		(*p2)(instruction);
*/
void thumb_decode(unsigned int instruction){
	int index =0;
	while (1){
#if DEBUG
	printf("the instruction to be decode  is %X \n", instruction);
	printf("The table index is %d \n", index);
	printf("The mask  is %X \n", table[index].mask);
	printf("The result after & is %X \n",instruction & table[index].mask);
	printf("The value is %X \n",table[index].value);
	printf("The point is %d \n", table[index].point);
#endif	
		if( (instruction & thumbtable[index].mask) == thumbtable[index].value){
			int* point =(int *) thumbtable[index].point;
			if(point > (int *)thumbtable && point <(int *)(thumbtable +MAXSIZE*4)){ 
				index=(point-(int *)thumbtable);
#if DEBUG
		printf("The point to skip in the table is %d the index is : %d\n", point, index);
#endif
			}else{
				func_ptr p = (func_ptr)point;
				(*p)(instruction);
			break;
			}
		}else {
			index++;
		}
	}
}



