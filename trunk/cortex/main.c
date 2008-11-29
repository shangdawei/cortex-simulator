#include "fetch.h"
#include "decode.h"
#include "elf_loader.h"

int main(){
	int i=0;
	//int state=1;//1 stands for the first statement

//--------------//
//initial the memory, load the target elf file to the memory//
	load_elf("test.elf");
//--------------//
	while(1){
		unsigned int instruction= get_MemU(get_pc()& 0xfffffffe,2);
	//	instruction &= 0x0ffff;
	//	if(state==1){
	//		set_pc(get_pc()+2);
	//		state=0;
	//	}
			if(instruction!=0){
				if(((instruction & 0x0E800) == 0x0E800) || 
							((instruction & 0x0F000)==0x0F000)){
					instruction=(((get_MemU((get_pc()&0xfffffffe),2)<<16)&0xffff0000) | (get_MemU((get_pc()&0xfffffffe)+2,2)&0x0ffff));
					set_pc(get_pc()+4);
					decode(instruction);
	//				state=1;

				}
				else{
					set_pc(get_pc()+4);
					thumb_decode((short)instruction);
					set_pc(get_pc()-2);
//					if(state==1)
//						set_pc(get_pc()+2);
//					state=0;
				}
				printf("------------------------------------------------------------- \n");
				#ifdef bool
				printf("hello world!\n");
				#endif
          }else{
              break;
          }
      }
  }

