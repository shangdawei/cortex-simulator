#include "fetch.h"
#include "decode.h"
#include "elf_loader.h"

int main(){
	int i=0;
//--------------//
//initial the memory, load the target elf file to the memory//
	load_elf("0706.elf");
//--------------//
	while(1){
		unsigned int instruction = fetch(flash[get_pc()/4]);
			if(instruction!=0){
				if(instruction & 0xE0000000){//there is a problem,how do thumb instrutions be arranged in memory?
					set_pc(get_pc()+1);
					decode(instruction);
				}
				else
					thumb_decode(instruction);
				printf("------------------------------------------------------------- \n");
				#ifdef bool
				printf("hello world!\n");
				#endif
          }else{
              break;
          }
      }
  }

