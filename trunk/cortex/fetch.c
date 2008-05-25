#include "fetch.h"
int testcase[21]={
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
	0xF690710F,
	0xF30070DF,//11110011001000100111001011011110
	0,
};
int fetch(int i){
     return testcase[i];
}

