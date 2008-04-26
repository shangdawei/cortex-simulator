#ifndef _REGISTER
#define _REGISTER

#define $R0		0
#define $R1		1
#define $R2		2
#define $R3		3
#define $R4		4
#define $R5		5
#define $R6		6
#define $R7		7
#define $R8		8
#define $R9		9
#define $R10	10
#define $R11	11
#define $R12	12
#define $SP 	13
#define $LR	 	14
#define $PC 	15
#define REG_SIZE 16

#define REG_N	0x80000000
#define REG_Z	0x40000000
#define REG_C	0x20000000
#define REG_V	0x10000000
#define REG_Q	0x08000000



void set_general_register(int Rn, int value);
int get_general_register();
void set_pc(int value);
int get_pc();
void set_sp(int value);
int get_sp();
void set_lp(int value);
int get_lp();

void set_flag_n();
void set_flag_z();
void set_flag_c();
void set_flag_v();
void set_flag_q();

void cle_flag_n();
void cle_flag_z();
void cle_flag_c();
void cle_flag_v();
void cle_flag_q();

int get_flag_n();
int get_flag_z();
int get_flag_c();
int get_flag_v();
int get_flag_q();


#endif