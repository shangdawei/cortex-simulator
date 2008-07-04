#include "fetch.h"
int testcase[50]={

	0xEB4878F8,	//1110101 1010 110000111100011111000	adc_reg   
	0xEB48F8F8,	//1110101 1010 010001111100011111000	adc_reg -> unpreditable
	0xEB0878F8,	//11101011000010000111100011111000		add_reg   
	0xEA0878F8,	//11101010000010000111100011111000		and_reg
	0xEA2878F8,	//11101010001010000111100011111000		bic_reg
	0xEB187FF8,	//11101011000110000111111111111000		cmn_reg
	0xEBB87FF8,	//11101011101110000111111111111000		cmp_reg
	0xEA8878F8,	//11101010100010000111100011111000		eor_reg
	0xEA4F78F8,	//11101010010011110111100011111000		mov_reg
	0xEA6F78F8,	//11101010011011110111100011111000		mvn_reg
	0xEA6878F8,	//11101010011010000111100011111000		orn_reg
	0xEA4878F8,	//11101010010010000111100011111000		orr_reg
	0xEBC878F8,	//11101011110010000111100011111000		rsb_reg
	0xEB6878F8,	//11101011011010000111100011111000		sbc_reg
	0xEBA878F8,	//11101011101010000111100011111000		sub_reg
	0xEA9F7FF8,	//11101010100111110111111111111000		teq_reg
	0xEA1F7FF8,	//11101010000111110111111111111000		tst_reg



	0xF43171F0,//11110100001100010111001011110000,
	0xF15172F0,//add with carry
	0xF10172F0,//add
	0xF00172F0,//logical and
	0xF02172F0,//bit clear
	0xF1117F0F,//compare negative
	0xF1B17F0F,//compare
	0xF08172F0,//exclusive or
	0xF05F72F0,//move
	0xF07F4208,//move negative
	0xF07172F0,//logical or not
	0xF05172F0,//logical or
	0xF1C172F0,//reverse subtract
	0xF16172F0,//subtract with carry
	0xF1A172F0,//subtract
	0xF0917F0F,//test equal
	0xF0117F0F,//test
	0xF6CF70F0,//0x11110110110100000111000111110000,
	0xF6A0710F,
	0xF30070DF,//11110011001000100111001011011110


	0xF8DF1001,
};
int fetch(int i){
     return testcase[i];
}

