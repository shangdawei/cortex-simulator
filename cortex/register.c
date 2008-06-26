#include "register.h"
#include "string.h"
#include "stdio.h"
static int registers[REG_SIZE]={0};
//static int imm_carry = 0;//ImmExpand will product it. it is a template
//static int calculate_carry = 0;//It is a template carry
//static int calculate_overflow = 0;// It is a template overflow
//static int shift_t = 0;//category of shift
//static int sat = 0;//whether saturated

void set_general_register(int rn, int value){
	registers[rn]=value;
}

int get_general_register(int rn){
	//memset(registers,'2',REG_SIZE*sizeof(int));
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
	return registers[$SP];
}
void set_lr(int value){
	registers[$LR]=value;
} 

int get_lr(){
	return registers[$LR];
}

void set_apsr(int value){
	registers[$APSR]=value;
}

int get_apsr(){
	return registers[$APSR];
}

//void set_carry(int value){
//   imm_carry = value;
//}
//
//int get_carry(){
//   return imm_carry;
//}

//void set_shift_t(int value){
//	shift_t = value;
//}

//int get_shift_t(){
//	return shift_t;
//}
//
//void set_sat(int value){
//	sat = value;
//}
//
//int get_sat(){
//	return sat;
//}

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
//void set_calculate_carry(){
//	calculate_carry = 1;
//}
//void set_calculate_overflow(){
//	calculate_overflow = 1;
//}

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
//void cle_calculate_carry(){
//	calculate_carry = 0;
//}
//void cle_calculate_overflow(){
//	calculate_overflow = 0;
//}

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


//int get_calculate_carry(){
//	return calculate_carry;
//}
//
//
//int get_calculate_overflow(){
//	return calculate_overflow;
//}


