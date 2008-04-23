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
	return state_register.n;
}

int get_flag_z(){
	return state_register.z;
}


int get_flag_c(){
	return state_register.c;
}


int get_flag_v(){
	return state_register.v;
}


int get_flag_q(){
	return state_register.q;
}




