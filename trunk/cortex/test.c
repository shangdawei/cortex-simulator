#include <stdio.h>
#include <stdlib.h>

union wrapper {

		struct {
			unsigned op:8;
			unsigned imm:8;
			unsigned size:8;
			unsigned type:8;
		} test;

		int value;
};

struct A{
	unsigned a:8;
	unsigned b:8;
	unsigned c:8;
	unsigned d:8;
}test1;


union wrapper w;



int main(){
	*((int *)(&test1)) = 0xFAFA08A8;
	w.value = 0xFFAA6600;
  	printf("test--op: 0x%X \n",(int)w.test.op);
	printf("test1--op: 0x%X \n",(int)test1.a);
//	*t1=0xFFAA6600;
//	printf("op : 0x%X \n",(int)t1->op);
//	printf("imm : 0x%X \n",t1->imm);
//	printf("size : 0x%X \n",t1->size);
//	printf("type : 0x%X \n",t1->type);
}

