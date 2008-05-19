#include "register.h"
#include "stdio.h"
static int registers[REG_SIZE]={0};


void set_general_register(int rn, int value){
	registers[rn]=value;
}

int get_general_register(int rn){
	return registers[rn];
}

void set_pc(int value){
	registers[$PC] = value;
}

int get_pc(){
	return registers[$PC];
}
void set_sp(int value){
	registers[$SP] = value;
}

int get_sp(){
	registers[$SP];
}
void set_lp(int value){
	registers[$LR]=value;
} 

int get_lp(){
	registers[$LR];
}

void set_flag_n(){
	registers[$APSR]|=REG_N;
}
void set_flag_z(){
	registers[$APSR]|=REG_Z;
}
void set_flag_c(){
	registers[$APSR]|=REG_C;
}
void set_flag_v(){	
	registers[$APSR]|=REG_V;
}
void set_flag_q(){
	registers[$APSR]|=REG_Q;
}
 
void cle_flag_n(){
	registers[$APSR]&=(~REG_N);

}
void cle_flag_z(){
	registers[$APSR]&=(~REG_Z);

}
void cle_flag_c(){
	registers[$APSR]&=(~REG_C);

}
void cle_flag_v(){
	registers[$APSR]&=(~REG_V);

}
void cle_flag_q(){
	registers[$APSR]&=(~REG_Q);
}

int get_flag_n(){
	int n = registers[$APSR];
	n&=REG_N;
	return n;
}

int get_flag_z(){
	int n = registers[$APSR];
	n&=REG_Z;
	return n;
}


int get_flag_c(){
	int n = registers[$APSR];
	n&=REG_C;
	return n;


}


int get_flag_v(){
	int n = registers[$APSR];
	n&=REG_V;
	return n;

}


int get_flag_q(){
	int n = registers[$APSR];
	n&=REG_Q;
	return n;

}




