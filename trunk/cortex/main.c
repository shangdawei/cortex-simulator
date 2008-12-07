#include "fetch.h"
#include "decode.h"
#include "elf_loader.h"

int main(){
	int i=0;
	getchar();
	//int state=1;//1 stands for the first statement

//--------------//
//initial the memory, load the target elf file to the memory//
	load_elf("testelf.elf");
//--------------//
	while(1){

		unsigned int instruction= get_MemU(get_pc()& 0xfffffffe,2);
		if(get_pc()==0x48d){
			printf("kldssl");
		}

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
						//deal with the IT instruction
					if(InITBlock()){   //in IT Block
						if(ConditionPassed((get_epsr()>>12)&0x0f))
							decode(instruction);

						if(LastInITBlock())
							set_epsr(get_epsr()&0xf9ff03ff);
						else
							set_epsr((((get_epsr()&0x06001c00)<<1)&0x06001c00)|(get_epsr()&0x0100e000)|((get_epsr()>>16)&0x00000400));
					}
					else   //not in IT Block
						decode(instruction);
	//				state=1;

				}
				else{
					set_pc(get_pc()+4);
					if(InITBlock()){   //in IT Block
						if(ConditionPassed((get_epsr()>>12)&0x0f))
							thumb_decode(instruction);

						if(LastInITBlock())
							set_epsr(get_epsr()&0xf9ff03ff);
						else
							set_epsr((((get_epsr()&0x06001c00)<<1)&0x06001c00)|(get_epsr()&0x0100e000)|((get_epsr()>>16)&0x00000400));					}

					else   //not in IT Block
						thumb_decode(instruction);
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

