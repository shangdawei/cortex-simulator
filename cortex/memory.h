#ifndef _MEMORY
#define _MEMORY
/*
	This file is designed to map the memory address
	modified by Jacky on 08.11.11
*/
#include <stdio.h>
#include <assert.h>
#include <windows.h>

#define FLASH_SIZE		262144			//256K Flash					from 0x00000000 to 0x0003FFFF
#define SRAM_SIZE		65536			//64K SRAM						from 0x20000000 to 0x2000FFFF
#define PERI_SIZE		1048576			//1M peripheral device	 		from 0x40000000	to 0x400FFFFF
#define NVIC_SIZE		128

#define FLASH_BASE		0x00000000
#define SRAM_BASE		0x20000000
#define PERI_BASE		0x40000000

#define FLASH_BEGIN		0x00000000	
#define FLASH_END		0x0003FFFF
#define SRAM_BEGIN		0x20000000		
#define SRAM_END		0x2000FFFF
#define SRAM_BB_BEGIN	0x22000000
#define SRAM_BB_END		0x23FFFFFF
#define	PERI_BEGIN		0x40000000
#define PERI_END		0x400FFFFF
#define	PERI_BB_BEGIN	0x42000000
#define PERI_BB_END		0x43FFFFFF
#define NVIC_BEGIN		0xE000E000
#define NVIC_END		0xE000EFFF

//define that which memory array it access
#define FLASH			0 
#define SRAM			1
#define SRAM_BB			2
#define PERI			3
#define PERI_BB			4
#define NVIC			5

//
int flash[FLASH_SIZE];//={0,1,2,3,4,5,6,7,8,9,};
int sram[SRAM_SIZE/4];// = {0xFFFFFFFF,};
int peripheral[PERI_SIZE/4];// = {0x12345678,};
int nvic[NVIC_SIZE/4];


typedef struct{
	int type;
	int offset;
}MemoryTranslate;


/*
	By given the mapped address, do some memory translation, return the memory infomation: 
	1.which type of memory segment (flash, sram or peripheral) it belongs, 
	2.the offset in the memory segment
*/
void addr_transfer(unsigned int address, MemoryTranslate* result);	//to jugde which memory array the given belongs, 
									//address is the mapped memory address, return value is the address in each memory array

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

/*
The Cortex-M3 memory map has two 32-MB alias regions that map to two 1-MB bit-band regions:
â€?Accesses to the 32-MB SRAM alias region map to the 1-MB SRAM bit-band region.
â€?Accesses to the 32-MB peripheral alias region map to the 1-MB peripheral bit-band region.

Writing to a word in the alias region has the same effect as a read-modify-write
operation on the targeted bit in the bit-band region.
*/
//address is in alias region, value is the to write in the address
void bit_binding_write(int bitWordOffset, int bitBandBaseType, int value);
int bit_binding_read(int bitWordOffset, int bitBandBaseType);





//output the PERI datas to a file
void PeriOut(int pc_reg, int address, int value);
//convert the inner address to device address
//-1: failed other: the address value
int AddConvert(int address);
//0: sucessful 1: failed
int writePeri(int address, int value);
int readPeri(int address);

//Peripherals Address Map

typedef struct{
	int inner_add;
	int inner_len;
	int peri_add;
	int peri_len;
}PAM_item;

#define PAM_SIZE 4
#define SMEM_ID "ShareMem"

#endif

