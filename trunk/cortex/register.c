#include "register.h"
#include "string.h"
#include "stdio.h"
static int registers[REG_SIZE]={0,1,2,3,0};
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
	registers[$XPSR]|=REG_N;
}
void set_flag_z(){
	registers[$XPSR]|=REG_Z;
}
void set_flag_c(){
	registers[$XPSR]|=REG_C;
}
void set_flag_v(){	
	registers[$XPSR]|=REG_V;
}
void set_flag_q(){
	registers[$XPSR]|=REG_Q;
}
//void set_calculate_carry(){
//	calculate_carry = 1;
//}
//void set_calculate_overflow(){
//	calculate_overflow = 1;
//}

void cle_flag_n(){
	registers[$XPSR]&=(~REG_N);

}
void cle_flag_z(){
	registers[$XPSR]&=(~REG_Z);

}
void cle_flag_c(){
	registers[$XPSR]&=(~REG_C);

}
void cle_flag_v(){
	registers[$XPSR]&=(~REG_V);

}
void cle_flag_q(){
	registers[$XPSR]&=(~REG_Q);
}
//void cle_calculate_carry(){
//	calculate_carry = 0;
//}
//void cle_calculate_overflow(){
//	calculate_overflow = 0;
//}

int get_flag_n(){
	int n = registers[$XPSR];
	n&=REG_N;
	return n;
}

int get_flag_z(){
	int n = registers[$XPSR];
	n&=REG_Z;
	return n;
}


int get_flag_c(){
	int n = registers[$XPSR];
	n&=REG_C;
	return n;


}


int get_flag_v(){
	int n = registers[$XPSR];
	n&=REG_V;
	return n;

}


int get_flag_q(){
	int n = registers[$XPSR];
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


void set_apsr(int value){
	registers[$XPSR] = ((value & REG_APSR) | (registers[$XPSR] & (~REG_APSR)));
}

int get_apsr(){
	return (registers[$XPSR] & REG_APSR);
}

void set_iapsr(int value) {
	registers[$XPSR] = ((value & REG_IAPSR) | (registers[$XPSR] & (~REG_IAPSR)));
}
int get_iapsr() {
	return (registers[$XPSR] & REG_IAPSR);
}
void set_eapsr(int value) {
	registers[$XPSR] = ((value & REG_EAPSR) | (registers[$XPSR] & REG_EAPSR));
}

int get_eapsr() {
	return (registers[$XPSR] & REG_EAPSR);
}

void set_xpsr(int value) {
	registers[$XPSR] = value;
}

int get_xpsr() {
	return registers[$XPSR];
}

void set_ipsr(int value) {
	registers[$XPSR] = ((value & REG_IPSR) | (registers[$XPSR] & (!REG_IPSR)));
}
int get_ipsr() {
	return (registers[$XPSR] & REG_IPSR);
}

void set_epsr(int value) {
	registers[$XPSR] = ((value & REG_EPSR) | (registers[$XPSR] & (~REG_EPSR)));
}

int get_epsr() {
	return (registers[$XPSR] & REG_EPSR);
}

void set_iepsr(int value) {
	registers[$XPSR] = ((value & REG_IEPSR) | (registers[$XPSR] & REG_IEPSR));
}

int get_iepsr() {
	return (registers[$XPSR] & REG_IEPSR);
}

void set_msp(int value) {
	registers[$MSP] = value;
}

int get_msp() {
	return registers[$MSP];
}

void set_psp(int value) {
	registers[$PSP] = value;
}

int get_psp() {
	return registers[$PSP];
}

void set_primask(int value) {
	registers[$PRIMASK] = value;
}

int get_primask() {
	return registers[$PRIMASK];
}

void set_basepri(int value) {
	registers[$BASEPRI] = value;
}

int get_basepri() {
	return registers[$BASEPRI];
}

void set_basepri_max(int value) {
	registers[$BASEPRI_MAX] = value;
}

int get_basepri_max() {
	return registers[$BASEPRI_MAX];
}

void set_faultmask(int value) {
	registers[$FAULTMASK] = value;
}

int get_faultmask() {
	return registers[$FAULTMASK];
}

void set_control(int value) {
	registers[$CONTROL] = value;
}

int get_control() {
	return registers[$CONTROL];
}

