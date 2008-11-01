#ifndef _MEMORY
#define _MEMORY
#define MEM_SIZE 8192		//bytes
#include <stdio.h>
#include <assert.h>
static int memory[MEM_SIZE / 4]={0,1,2,3,4,5,6,7,8,9,};
void memory_copy(int target, int destination, int num);
int get_memory(int address);
void set_memory(int address, int value);
void clear_momory(int target, int num);
int get_memory_size();

//Aligned Memory Access, bytes can only be 4, 2, 1
int get_MemA(int address, int bytes);
void set_MemA(int address, int bytes, int value);
//

//Unaligned Memory Access, bytes can only be 4, 2, 1
int get_MemU(int address, int bytes);
void set_MemU(int address, int bytes, int value);
//
#endif

