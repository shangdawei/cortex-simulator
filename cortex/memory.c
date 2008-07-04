#include "memory.h"
static int memory[MEM_SIZE]={0,1,2,3,4,5,6,7,8,9,};
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
