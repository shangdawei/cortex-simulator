#ifndef _MEMORY
#define _MEMORY
#define MEM_SIZE 8192		//bytes
#include <stdio.h>
#include <assert.h>
void memory_copy(int target, int destination, int num);
int get_memory(int address);
void set_memory(int address, int value);
void clear_momory(int target, int num);
int get_memory_size();

//Aligned Memory Access, byteNR can only be 4, 2, 1
int get_MemA(int address, int byteNR);
void set_MemA(int address, int byteNR, int value);
//

//Unaligned Memory Access, byteNR can only be 4, 2, 1
int get_MemU(int address, int byteNR);
void set_MemU(int address, int byteNR, int value);
//
#endif

