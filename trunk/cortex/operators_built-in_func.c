/*
 * This file includes these sections:
 * Operations on generic types
 * Operations on booleans
 * Bitstring manipulation
 * Arithmetic
*/
#include "operators_built-in_func.h"

int HighestSetBit(int i)
{
/*
HighestSetBit(x) is the maximum bit number of any of its bits that are ones. If all of its bits
are zeros, HighestSetBit(x) = -1.
*/
	int bit,mask;
	for(bit=31;bit>=0;bit--)
	{
		mask = 1<<bit;
		if(mask&i)
		{
			return bit;
		}
	}
	return -1;
}

int LowestSetBit(int i)
{
/*
LowestSetBit(x) is the minimum bit number of any of its bits that are ones. If all of its bits are
zeros, LowestSetBit(x) = Len(x).
*/
	int bit,mask;
	for(bit = 0;bit<=31;bit++)
	{
		mask = 1<<bit;
		if(mask&i)
		{
			return bit;
		}
	}
	return 32;
}