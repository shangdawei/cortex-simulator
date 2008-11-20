#include "fetch.h"
#include "decode.h"
#include "elf_loader.h"

int main(){
	int i=0;
//--------------//
//initial the memory, load the target elf file to the memory//
	load_elf("test.elf");
//--------------//
	while(1){
		int instruction = get_MemA(get_pc(),2);
			if(instruction!=0){
				if((instruction & 0xE0000000 == 0xE0000000) && 
							(instruction & 0x18000000)){
					set_pc(get_pc()+4);
					//decode(instruction);
				}
				else{
					set_pc(get_pc()+4);
					thumb_decode((short)instruction);
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

