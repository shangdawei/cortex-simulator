#include "memory.h"
#include "register.h"

PAM_item cortex_PAM[4] = {
	{0x400263c0,0x00000001,0x00000000,0x00000001},//wheel
	{0x400063c0,0x00000001,0x00000001,0x00000001},//wheel
	{0x40024004,0x00000001,0x00000002,0x00000001},//led
	{0x40024008,0x00000001,0x00000003,0x00000001},//led
};


void addr_transfer(unsigned int address, MemoryTranslate* result){
	if((FLASH_BEGIN <= address)&&(FLASH_END >= address)){
		result->type = FLASH;
		result->offset = address&0x0003FFFF;
	}
	else if((SRAM_BEGIN <= address)&&(SRAM_END >= address)){
		result->type = SRAM;
		result->offset = address&0x0000FFFF;
	}
	else if((SRAM_BB_BEGIN <= address)&&(SRAM_BB_END >= address)){
		result->type = SRAM_BB;
		result->offset = address&0x01FFFFFF;
	}
	else if((PERI_BEGIN <= address)&&(PERI_END >= address)){
		result->type = PERI;
		result->offset = address&0x000FFFFF;
	}
	else if((PERI_BB_BEGIN <= address)&&(PERI_BB_END >= address)){
		result->type = PERI_BB;
		result->offset = address&0x01FFFFFF;
	}
	else if((NVIC_BEGIN <= address)&&(NVIC_END >= address)){
		result->type = NVIC;
		result->offset = address&0x00000fff;
	}
	else{
		printf("memory address:%d access error!\n",result->offset);
	}
}


int get_memory(int address){
	int result;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	addr_transfer(address, memoryInfo);
	switch(memoryInfo->type){
		case FLASH:
			result = flash[memoryInfo->offset/4];
			break;
		case SRAM:
			result = sram[memoryInfo->offset/4];
			break;
		case SRAM_BB:
			break;
		case PERI:
			result = readPeri(AddConvert(address));
			break;
		case PERI_BB:
			break;
		case NVIC:
			result = nvic[memoryInfo->offset/4];
			break;
		default:
			printf("memory address:%d access error in get_memory!\n",address);
	}
	free(memoryInfo);
	return result;
}

void set_memory(int address, int value){
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	addr_transfer(address, memoryInfo);
	switch(memoryInfo->type){
		case FLASH:
			flash[memoryInfo->offset/4] = value;
			break;
		case SRAM:
			sram[memoryInfo->offset/4]  = value;
			break;
		case SRAM_BB:
			break;
		case PERI:
			peripheral[memoryInfo->offset/4]  = value;
			PeriOut(get_pc(),address,value);
			writePeri(AddConvert(address),value);
			break;
		case PERI_BB:
			break;
		case NVIC:
			nvic[memoryInfo->offset/4] = value;
			break;
		default:
			printf("memory address:%d access error in get_memory!\n",address);
	}
	free(memoryInfo);
}


//Aligned Memory Access, bytes can only be 4, 2, 1
int get_MemA(int address, int bytes)
{
	int result;
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	address = address & 0xFFFFFFFC;													//make the address aligned
	addr_transfer(address, memoryInfo);
	switch(memoryInfo->type){
		case FLASH:
			ptr = (char*)(&flash[memoryInfo->offset/4]);
			break;
		case SRAM:
			ptr = (char*)(&sram[memoryInfo->offset/4]);
			break;
		case SRAM_BB:
			return bit_binding_read(memoryInfo->offset,SRAM_BB);
		case PERI:
			peripheral[memoryInfo->offset/4] = readPeri(AddConvert(address));
			ptr = (char*)(&peripheral[memoryInfo->offset/4]);
			break;
		case PERI_BB:
			return bit_binding_read(memoryInfo->offset,PERI_BB);
		case NVIC:
			ptr = (char*)(&nvic[memoryInfo->offset/4]);
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
#if DEBUG
	printf("get_MemA result:%d\n",result);
#endif
	free(memoryInfo);
	return result;
}

void set_MemA(int address, int bytes, int value)
{
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	address = address & 0xFFFFFFFC;													//make the address aligned
	addr_transfer(address, memoryInfo);
	switch(memoryInfo->type){
		case FLASH:
			ptr = (char*)(&flash[memoryInfo->offset/4]);
			break;
		case SRAM:
			ptr = (char*)(&sram[memoryInfo->offset/4]);
			break;
		case SRAM_BB:
			bit_binding_write(memoryInfo->offset,SRAM_BB,value);
			return;
		case PERI:
			ptr = (char*)(&peripheral[memoryInfo->offset/4]);
			PeriOut(get_pc(),address,value);
			writePeri(AddConvert(address),value);
			break;
		case PERI_BB:
			bit_binding_write(memoryInfo->offset,PERI_BB,value);
			return;
		case NVIC:
			ptr = (char*)(&nvic[memoryInfo->offset/4]);
			break;
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
	free(memoryInfo);
#if DEBUG
	printf("set_MemA result:%d\n",*((int*)ptr));
#endif
} 



//Unaligned Memory Access, bytes can only be 4, 2, 1
int get_MemU(int address, int bytes)
{
	int result;
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	addr_transfer(address, memoryInfo);
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
			peripheral[memoryInfo->offset/4] = readPeri(AddConvert(address));
			ptr = (char*)peripheral + memoryInfo->offset;
			break;
		case PERI_BB:
			//bit-binding in peripheral cannot be Unaligned access
			printf("PERI bit binding in set_MemU() is not permit");
			return 0;
		case NVIC:
			ptr = (char*)nvic + memoryInfo->offset;
			break;
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
		result &= 0x0ffff;
		break;
	case 1:
		result = *((char*) ptr);
		result &= 0x0ff;
		break;
	default:	//invalid bytes
		result = 0x00;			
	}
#if DEBUG
	printf("get_MemU result:%d\n",result);
#endif
	free(memoryInfo);
	return result;
}

void set_MemU(int address, int bytes, int value)
{
	char* ptr;
	MemoryTranslate* memoryInfo = (MemoryTranslate*)malloc(sizeof(MemoryTranslate));
	addr_transfer(address, memoryInfo);
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
			writePeri(AddConvert(address),value);
			PeriOut(get_pc(),address,value);
			break;
		case PERI_BB:
			//bit-binding in peripheral cannot be Unaligned access
			printf("peripheral bit binding in set_MemU() is not permit");
			return;
		case NVIC:
			ptr = (char*)nvic + memoryInfo->offset;
			break;
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
	free(memoryInfo);
#if DEBUG
	printf("set_MemU result:%d\n",*((int*)ptr));
#endif
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

/*
this function is just for testing
It append some logs to a txt file,when the program modifies some special memory,sush as GPIO,UARTR,etc.

*/
void PeriOut(int pc_reg, int address, int value)
{
	FILE *file = fopen("periout.dat", "a+");
	fprintf(file, "PC : 0x%x\tADD : 0x%x\tVAL : 0x%x\n", pc_reg, address, value);
	fclose(file);
}

int AddConvert(int address)
{
	int i;

	for(i=0; i < PAM_SIZE; i++){
		if(address >= cortex_PAM[i].inner_add && address < cortex_PAM[i].inner_add + cortex_PAM[i].inner_len)
			return cortex_PAM[i].peri_add + (address - cortex_PAM[i].inner_add);
	}

	return -1;
}

int writePeri(int address, int value)
{
	HANDLE hMemMap = OpenFileMapping(FILE_MAP_WRITE, FALSE, SMEM_ID);
	LPBYTE pMemView;
	if(address == -1){
		CloseHandle(hMemMap);
		return 1;
	}

	if(hMemMap != NULL){
		pMemView = (LPBYTE)MapViewOfFile(hMemMap,FILE_MAP_WRITE,0,0,0);
		if(pMemView == NULL){
			CloseHandle(hMemMap);
			return 1;
		}
	}
	else
		return 1;

	pMemView[address] = (char)value;
	pMemView[address+PAM_SIZE]++;
	if(pMemView[address+PAM_SIZE] > 250)
		pMemView[address+4] = 1;

	return 0;
}

int readPeri(int address)
{
	HANDLE hMemMap = OpenFileMapping(FILE_MAP_READ, FALSE, SMEM_ID);
	LPBYTE pMemView;
	if(address == -1){
		CloseHandle(hMemMap);
		return 0;
	}
	if(hMemMap != NULL){
		pMemView = (LPBYTE)MapViewOfFile(hMemMap,FILE_MAP_READ,0,0,0);
		if(pMemView == NULL){
			CloseHandle(hMemMap);
			return 0;
		}
	}
	else
		return 0;
	return pMemView[address];
}