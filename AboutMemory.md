memory.c memory.h已更新，增加对内存的对齐和非对齐访问，建议取代之前的set\_memory, get\_memory, store\_half, store\_byte等函数

新的函数声明如下，bytes表示要访问的字节数，如有bug请尽快说明 <sup>_</sup>

//Aligned Memory Access, bytes can only be 4, 2, 1

int get\_MemA(int address, int bytes);

void set\_MemA(int address, int bytes, int value);

//

//Unaligned Memory Access, bytes can only be 4, 2, 1

int get\_MemU(int address, int bytes);

void set\_MemU(int address, int bytes, int value);

//