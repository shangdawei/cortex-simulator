#include "memory.h"
MemoryTranslate* addr_transfer(unsigned int address){
	MemoryTranslate* result = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	if((FLASH_BEGIN <= address)&&(FLASH_END >= address)){
		result->type = FLASH;
		result->offset = address&0x0003FFFF;

		//printf("flash offset:%d access!\n",result->offset);
	}
	else if((SRAM_BEGIN <= address)&&(SRAM_END >= address)){
		result->type = SRAM;
		result->offset = address&0x0000FFFF;

		//printf("sram address:%d access!\n",result->offset);
	}
	else if((SRAM_BB_BEGIN <= address)&&(SRAM_BB_END >= address)){
		result->type = SRAM_BB;
		result->offset = address&0x01FFFFFF;

		//printf("sram bit-binding address:%d access!\n",result->offset);
	}
	else if((PERI_BEGIN <= address)&&(PERI_END >= address)){
		result->type = PERI;
		result->offset = address&0x000FFFFF;

		//printf("peripheral address:%d access!\n",result->offset);
	}
	else if((PERI_BB_BEGIN <= address)&&(PERI_BB_END >= address)){
		result->type = PERI_BB;
		result->offset = address&0x01FFFFFF;
		//printf("peripheral bit-binding address:%d access!\n",result->offset);
	}
	else{
		printf("memory address:%d access error!\n",result->offset);
	}
	return result;
}


int get_memory(int address){
	int result;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	memoryInfo = addr_transfer(address);
	switch(memoryInfo->type){
		case FLASH:
			result = flash[memoryInfo->offset/4];
			printf("get_memory result:%d\n",result);
			break;
		case SRAM:
			result = sram[memoryInfo->offset/4];
			break;
		case SRAM_BB:
			//bit-binding in sram
			break;
		case PERI:
			result = peripheral[memoryInfo->offset/4];
			break;
		case PERI_BB:
			//bit-binding in sram
			break;
		default:
			printf("memory address:%d access error in get_memory!\n",address);
	}
	return result;
	//assert(address < MEM_SIZE);
	//return memory[address];
}

void set_memory(int address, int value){
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	memoryInfo = addr_transfer(address);
	switch(memoryInfo->type){
		case FLASH:
			flash[memoryInfo->offset/4] = value;
			printf("set_memory result:flash[%d] = %d\n",memoryInfo->offset,flash[memoryInfo->offset/4]);
			break;
		case SRAM:
			sram[memoryInfo->offset/4]  = value;
			break;
		case SRAM_BB:
			//bit-binding in sram
			break;
		case PERI:
			peripheral[memoryInfo->offset/4]  = value;
			break;
		case PERI_BB:
			//bit-binding in sram
			break;
		default:
			printf("memory address:%d access error in get_memory!\n",address);
	}
}


//Aligned Memory Access, bytes can only be 4, 2, 1
int get_MemA(int address, int bytes)
{
	int result;
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	address = address & 0xFFFFFFFC;													//make the address aligned
	memoryInfo = addr_transfer(address);
	switch(memoryInfo->type){
		case FLASH:
			ptr = (char*)(&flash[memoryInfo->offset/4]);

			break;
		case SRAM:
			ptr = (char*)(&sram[memoryInfo->offset/4]);
			break;
		case SRAM_BB:
			//bit-binding in sram
			return bit_binding_read(memoryInfo->offset,SRAM_BB);
			break;
		case PERI:
			ptr = (char*)(&peripheral[memoryInfo->offset/4]);
			break;
		case PERI_BB:
			//bit-binding in peripheral
			return bit_binding_read(memoryInfo->offset,PERI_BB);
			break;
		default:
			printf("memory address:%d access error in get_MemA()!\n",address);
	}
	switch(bytes)
	{
	case 4:		
		result = *((int*) ptr);
		break;
	case 2:
		result = *((short*) ptr);
		break;
	case 1:
		result = *((char*) ptr);
		break;
	default:	//invalid bytes
		result = 0x00;			
	}
	printf("get_MemA result:%d\n",result);
	return result;
}

void set_MemA(int address, int bytes, int value)
{
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	address = address & 0xFFFFFFFC;													//make the address aligned
	memoryInfo = addr_transfer(address);
	switch(memoryInfo->type){
		case FLASH:
			ptr = (char*)(&flash[memoryInfo->offset/4]);
			break;
		case SRAM:
			ptr = (char*)(&sram[memoryInfo->offset/4]);
			break;
		case SRAM_BB:
			//bit-binding in sram
			bit_binding_write(memoryInfo->offset,SRAM_BB,value);
			return;
		case PERI:
			ptr = (char*)(&peripheral[memoryInfo->offset/4]);
			break;
		case PERI_BB:
			bit_binding_write(memoryInfo->offset,PERI_BB,value);
			return;
		default:
			printf("memory address:%d access error in set_MemA()!\n",address);
	}
	switch(bytes)
	{
	case 4:
		*((int*) ptr) = value;
		break;
	case 2:
		*((short*) ptr) = value;
		break;
	case 1:
		*((char*) ptr) = value;
		break;
	default:	//invalid bytes
		break;
	}
	printf("set_MemA result:%d\n",*((int*)ptr));
} 



//Unaligned Memory Access, bytes can only be 4, 2, 1
int get_MemU(int address, int bytes)
{
	int result;
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	memoryInfo = addr_transfer(address);
	switch(memoryInfo->type){
		case FLASH:
			ptr = (char*)flash + memoryInfo->offset;
			break;
		case SRAM:
			ptr = (char*)sram + memoryInfo->offset;
			break;
		case SRAM_BB:
			//bit-binding in sram cannot be Unaligned access
			printf("SRAM bit binding in get_MemU() is not permit!");
			return 0;
		case PERI:
			ptr = (char*)peripheral + memoryInfo->offset;
			break;
		case PERI_BB:
			//bit-binding in peripheral cannot be Unaligned access
			printf("PERI bit binding in set_MemU() is not permit");
			return 0;
		default:
			printf("memory address:%d access error in get_MemU()!\n",address);
	}
	switch(bytes)
	{
	case 4:		
		result = *((int*) ptr);
		break;
	case 2:
		result = *((short*) ptr);
		break;
	case 1:
		result = *((char*) ptr);
		break;
	default:	//invalid bytes
		result = 0x00;			
	}
	printf("get_MemU result:%d\n",result);
	return result;
}

void set_MemU(int address, int bytes, int value)
{
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	memoryInfo = addr_transfer(address);
	switch(memoryInfo->type){
		case FLASH:
			ptr = (char*)flash + memoryInfo->offset;
			break;
		case SRAM:
			ptr = (char*)sram + memoryInfo->offset;
			break;
		case SRAM_BB:
			//bit-binding in sram cannot be Unaligned access
			printf("SRAM bit binding in set_MemU() is not permit");
			return;
		case PERI:
			ptr = (char*)peripheral + memoryInfo->offset;
			break;
		case PERI_BB:
			//bit-binding in peripheral cannot be Unaligned access
			printf("peripheral bit binding in set_MemU() is not permit");
			return;
		default:
			printf("memory address:%d access error in get_MemU()!\n",address);
	}
	switch(bytes)
	{
	case 4:
		*((int*) ptr) = value;
		break;
	case 2:
		*((short*) ptr) = value;
		break;
	case 1:
		*((char*) ptr) = value;
		break;
	default:	//invalid bytes
		break;
	}
	printf("set_MemU result:%d\n",*((int*)ptr));
}
//

/*
bitWordOffset = (byteOffset*32) +(bitNum*4)
bitWordAddr = bitBandBase + bitWordOffset
*/
void bit_binding_write(int bitWordOffset, int bitBandBaseType, int value){
	int byteOffset;
	int bitNum;
	char result;
	char* ptr;
	byteOffset = (bitWordOffset&0x01FFFFE0)>>5;
	bitNum = ((bitWordOffset&0x1C)>>2);
	if(SRAM_BB == bitBandBaseType){
		ptr = (char*)sram + byteOffset;
		if(0==(0x1&value)){									//write 0 in sram bit-band
			result = (*ptr)&(~((0x1)<<bitNum));
		}
		else{												//write 1 in sram bit-band
			result = (*ptr)|(0x1<<bitNum);
		}
	}
	else if(PERI_BB == bitBandBaseType){
		ptr = (char*)peripheral + byteOffset;
		if(0==(0x1&value)){									//write 0 in sram bit-band
			result = (*ptr)&(~((0x1)<<bitNum));
		}
		else{												//write 1 in sram bit-band
			result = (*ptr)|(0x1<<bitNum);
		}
	}
	*ptr = result;
}
int bit_binding_read(int bitWordOffset, int bitBandBaseType){
	int byteOffset;
	int bitNum;
	int result;
	char* ptr;
	byteOffset = (bitWordOffset&0x01FFFFE0)>>5;
	bitNum = ((bitWordOffset&0x1C)>>2);
	if(SRAM_BB == bitBandBaseType){
		ptr = (char*)sram + byteOffset;
		result = ((*ptr)&(0x1<<bitNum))>>bitNum;
	}
	else if(PERI_BB == bitBandBaseType){
		ptr = (char*)sram + byteOffset;
		result = ((*ptr)&(0x1<<bitNum))>>bitNum;
	}
	return result;
}



void clear_memory(int target, int  num){
	//int i;
	//for ( i =0; i< num; i++){
	//	assert( target + i < MEM_SIZE);
	//    memory[target+i]=0;
	//}
}

int get_memory_size(){
	return FLASH_SIZE;
}

void memory_copy(int target, int destination, int num){
	//int i;

	//for (i =0; i< num; i++){
	//	assert(destination+i < MEM_SIZE && target + i < MEM_SIZE);
	//	memory[destination+i] = memory[target+i];
	//}
}