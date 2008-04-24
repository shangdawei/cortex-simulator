#include "register.h"

static int registers[REG_SIZE]={0};


void set_register(int rn, int value){
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
	registers[REG_SIZE]|=REG_N;
}
void set_flag_z(){
	registers[REG_SIZE]|=REG_Z;
}
void set_flag_c(){
	registers[REG_SIZE]|=REG_C;
}
void set_flag_v(){	
	registers[REG_SIZE]|=REG_V;
}
void set_flag_q(){
	registers[REG_SIZE]|=REG_Q;
}
 
void cle_flag_n(){
	registers[REG_SIZE]&=(~REG_N);

}
void cle_flag_z(){
	registers[REG_SIZE]&=(~REG_Z);

}
void cle_flag_c(){
	registers[REG_SIZE]&=(~REG_C);

}
void cle_flag_v(){
	registers[REG_SIZE]&=(~REG_V);

}
void cle_flag_q(){
	registers[REG_SIZE]&=(~REG_Q);
}

int get_flag_n(){
	int n = registers[REG_SIZE];
	n&=REG_N;
	return n;
}

int get_flag_z(){
	int n = registers[REG_SIZE];
	n&=REG_Z;
	return n;
}


int get_flag_c(){
	int n = registers[REG_SIZE];
	n&=REG_C;
	return n;


}


int get_flag_v(){
	int n = registers[REG_SIZE];
	n&=REG_V;
	return n;

}


int get_flag_q(){
	int n = registers[REG_SIZE];
	n&=REG_Q;
	return n;

}




