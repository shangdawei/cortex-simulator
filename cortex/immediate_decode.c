#ifndef _IMMEDIATEDECODE
#define _IMMEDIATEDECODE
#include "instruction.h"
#include "stdio.h"
//#include "register.h"
int decode_imm12(int i1,int i3,int i8){
	int i = (i1<<11)+(i3<<8)+i8;
	return i;
}
int decode_imm16(int i1,int i4,int i3,int i8){
	int i =(i4<<12)+(i1<<11)+(i3<<8)+i8;
	return i;
}

int decode_bitOperation(int i3,int i2,int i5){
	int i=(i3<<7)+(i2<<5)+i5;
	return i;
}

int decode_shift(int i3,int i2){
	int i=(i3<<2)+i2;
	return i;
}

struct IMM12{
  unsigned seg1 :8;
  unsigned seg2 :2;
  unsigned seg3 :2;
  unsigned seg4 :20;
}imm12;

//immediate expand with Carry
int ThumbExpandImm12WithC(int i1,int i3,int i8){
   int imm32;
   int temp;
   int i = decode_imm12(i1,i3,i8);
   *((int *)(&imm12)) = i;
   if(imm12.seg3==0)
      {switch(imm12.seg2){
         case 0: imm32 = imm12.seg1; break;
         case 1:
           {if(imm12.seg1==0)
              printf("the imm32 is UNPREDICTABLE.");
            else
              imm32 = (imm12.seg1<<16)+imm12.seg1;
           }break;
         case 2:
           {if(imm12.seg1==0)
              printf("the imm32 is UNPREDICTABLE.");
            else
              imm32 = (imm12.seg1<<24)+(imm12.seg1<<8);
           }break;
         case 3:
           {if(imm12.seg1==0)
              printf("the imm32 is UNPREDICTABLE.");
            else
              imm32 = (imm12.seg1<<24)+(imm12.seg1<<16)+(imm12.seg1<<8)+imm12.seg1;
           }break;
                        }
      temp = get_flag_c();
      set_carry(temp);
                } 
   else
		{int m = ((i & 0x00000F80) >> 7);
       //printf(" m = %x",m);
		int n = ((i & 0x000000FF)|0x00000080);
       //printf(" n = %x",n);
		imm32 = ror_c(n,m);
		} 
   //printf(" imm32 = %x",imm32);
	return imm32;
}

//immediate expand with Carry
int ThumbExpandImm12(int i1,int i3,int i8){
   int imm32 = ThumbExpandImm12WithC(i1,i3,i8);
   return imm32;
}
#endif
