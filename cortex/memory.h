#ifndef _MEMORY
#define _MEMORY
#define MEM_SIZE 8192
#include <stdio.h>
#include <assert.h>
void memory_copy(int target, int destination, int num);
int get_memory(int address);
void set_memory(int address, int value);
void clear_momory(int target, int num);
int get_memory_size();

#endif

