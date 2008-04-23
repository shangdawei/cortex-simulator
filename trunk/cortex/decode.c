
/**
 * This file is to define 
 *	1)TranslatorTable
 *	2)int instruction, which means the current processing instruction
 *	3)initialize the table 
 *	4)fetch one 32-bit instruction
 *	5)decode
 * 
 */

#include "decode.h"
typedef struct {
	int mask;
	int value;
	void *point;
} TranslateTable;

typedef void (*func_ptr)(int);
	

TranslateTable table[MAXSIZE] = {
	//*************************************************************************************************
          {0xF8008000,0xF0000000,(void *)table+8*4},	//go to entry 8,  which is to define Data Processing :immediate
          {0xEE000000,0xEA000000,(void *)table+13*4},   //go to entry 13, which is to define Data Processing :no immdiate
          {0xFE000000,0xF8000000,(void *)table+21*4},	//go to entry 21, which is to define Load & Store signle data item 
          {0xEF400000,0xE8400000,(void *)table+31*4},	//go to entry 31, which is to define Load & Store Double and Exclusive
          {0xEF400000,0xE8000000,(void *)table+34*4},	//go to entry 34, which is to define Load & Store Multible
          {0xF8008000,0xF0008000,(void *)table+36*4},	//go to entry 36, which is to define Brnaches, Miscellaneous control
          {0xEF000000,0xF0000000,(void *)table+44*4},	//go to entry 44, which is to define Coprocessor
	      //these 7 entries is to define the 7 types in the Thumb-2 Instruction Architectur, which is on the Page 74
         
		 {0xFA000000,0xF0000000,(void *)error_message}, //no entries is matched, go the function to handle error; 

	//*************************************************************************************************
	//Entry 8: there should be 5 functions
		{0xFA000000,0xF0000000,(void *)data_pro_modified_12m}, // entry 8
		{0xFB400000,0xF2000000,(void *)data_pro_add_12m},
		{0xFB400000,0xF2400000,(void *)data_pro_mov_16m},
		{0xFB100000,0xF3000000,(void *)data_pro_bitoperation},
		{0xFB100000,0xF3100000,(void *)data_pro_reserved},
    	//these 5 entries is to define Data Processing :immediate, which is on Page 75
	//*************************************************************************************************
	//Entry 13: there should be 8 functions

    	//these 8 entries is to define Data Processing :no immdiate, which is on Page 80
	//*************************************************************************************************
	//Entry 21: there should be 10 functions

    	//these 10 entries is to define Load & Store single data item,which is on Page 87
	//*************************************************************************************************
	//Entry 31: there should be 3 functions

    	//these 3 entries is to define Load & Store, Double and Exclusive, which is on Page 89
	//*************************************************************************************************
	//Entry 34: there should be 2 functions

    	//these 2 entries is to define Load & Store Multible, which is on Page 91
   	//***********************************************************j**************************************
	//Entry 36: there should be 8 functions
	
	
    	//these 8 entries is to define Branches, miscellaneous control, which is on Page 92
	//*************************************************************************************************
	//Entry 44: there should be 5 functions
	
    	//these 5 entries is to define Coprocessor, which is on Page 94

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
void decode(unsigned int instruction){
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
		if( (instruction & table[index].mask) == table[index].value){
			int* point =(int *) table[index].point;
			if(point > (int *)table && point <(int *)(table +MAXSIZE*4)){ 
				index=(point-(int *)table);
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



