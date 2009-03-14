#include "fetch.h"
#include "decode.h"
#include "thumb_decode.h"
#include "elf_loader.h"
#include "device/common/device.h"

int main(){
	unsigned int instruction;
	FILE *file = fopen("system.log", "w");
	int i = 0,pcc;

	load_elf("testelf.elf");
	getchar();
	
	while(1){
		i++;
		if(i == 1000000){
			fclose(file);
			return 0;
		}
		instruction = get_MemU(get_pc()& 0xfffffffe,2);
		pcc = get_pc();
		if(!(i % 100))
			fprintf(file,"%d\t%d\n",i,instruction);
		if(instruction!=0){
			if(((instruction & 0x0E800) == 0x0E800) ||
						((instruction & 0x0F000) == 0x0F000)){
				instruction=(((get_MemU((get_pc()&0xfffffffe),2)<<16)&0xffff0000) | 
					(get_MemU((get_pc()&0xfffffffe)+2,2)&0x0ffff));
				set_pc(get_pc()+4);

				//deal with the IT instruction
				if(InITBlock()){   //in IT Block
					if(ConditionPassed((get_epsr()>>12)&0x0f));
						decode(instruction);
					if(LastInITBlock())
						set_epsr(get_epsr()&0xf9ff03ff);
					else
						set_epsr((((get_epsr()&0x06001c00)<<1)&0x06001c00)|(get_epsr()&0x0100e000)|((get_epsr()>>16)&0x00000400));
				}
				else   //not in IT Block
					decode(instruction);
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

				else  //not in IT Block
					thumb_decode(instruction);
				set_pc(get_pc()-2);
			}
		}
		else{
			printf("Get an error instruction!!!\n");
			break;
		}
	}
}