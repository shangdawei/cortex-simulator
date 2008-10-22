#include "memory.h"
static int memory[MEM_SIZE / 4]={0,1,2,3,4,5,6,7,8,9,};
void memory_copy(int target, int destination, int num){
	int i;
	for (i =0; i< num; i++){
		assert(destination+i < MEM_SIZE && target + i < MEM_SIZE);
		memory[destination+i] = memory[target+i];
	}
}

int get_memory(int address){
	assert(address < MEM_SIZE);
	return memory[address];
}

void set_memory(int address, int value){
	assert(address < MEM_SIZE);
	memory[address] = value;
}

void clear_memory(int target, int  num){
	int i;
	for ( i =0; i< num; i++){
		assert( target + i < MEM_SIZE);
	    memory[target+i]=0;
	}
}

int get_memory_size(){
	return MEM_SIZE;
}

//Aligned Memory Access, bytes can only be 4, 2, 1
int get_MemA(int address, int bytes)
{
	int result;
	char* ptr;		
	assert(address < MEM_SIZE);
	ptr = (char*) (&memory[address / 4]);
	switch(bytes)
	{
	case 4:		
		result = *((int*) ptr);
		return result;
	case 2:
		result = *((short*) ptr);
		return result;
	case 1:
		result = *((char*) ptr);
		return result;
	default:	//invalid bytes
		return 0x00;			
	}
}

void set_MemA(int address, int bytes, int value)
{
	char* ptr;	
	assert(address < MEM_SIZE);
	ptr = (char*) (&memory[address / 4]);
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
} 



//Unaligned Memory Access, bytes can only be 4, 2, 1
int get_MemU(int address, int bytes)
{
	int result;
	char* ptr;
	assert(address + bytes< MEM_SIZE);
	ptr = (char*)memory + address;

	switch(bytes)
	{
	case 4:		
		result = *((int*) ptr);
		return result;
	case 2:
		result = *((short*) ptr);
		return result;
	case 1:
		result = *((char*) ptr);
		return result;
	default:	//invalid bytes
		return 0x00;			
	}
}

void set_MemU(int address, int bytes, int value)
{
	char* ptr;	
	assert(address + bytes < MEM_SIZE);
	ptr = (char*)memory + address;
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
}
//



