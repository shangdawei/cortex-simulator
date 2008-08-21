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
#define $XPSR	16
// Definitioins of special registers 
#define $MSP	17
#define $PSP	18
#define $PRIMASK	19
#define $BASEPRI	20
#define $BASEPRI_MAX	21
#define $FAULTMASK	22
#define $CONTROL	23
#define REG_SIZE 24

// APSR¡¢IPSR¡¢EPSR
#define REG_APSR	0xF8000000
#define REG_IPSR	0x000001FF
#define REG_EPSR	0x0700FC00
#define REG_IAPSR	(REG_IPSR | REG_APSR)
#define REG_EAPSR	(REG_EPSR | REG_APSR)
#define REG_IEPSR	(REG_IPSR | REG_EPSR)

#define REG_N	0x80000000
#define REG_Z	0x40000000
#define REG_C	0x20000000
#define REG_V	0x10000000
#define REG_Q	0x08000000

#define SRType_None 0
#define SRType_LSL	1
#define SRType_LSR	2
#define SRType_ASR	3
#define SRType_ROR	4
#define SRType_RRX	5

struct RESULTCARRY{
	int result;
	int carry;
};
struct CALCULATECO{
	unsigned int result;
	int carry_out;
	int overflow;
};

//static int registers[REG_SIZE]={0};

void set_general_register(int rn, int value);
int get_general_register(int rn);
void set_pc(int value);
int get_pc();
void set_sp(int value);
int get_sp();
void set_lr(int value);
int get_lr();
void set_carry(int value);
int get_carry();
//void set_shift_t(int value);
//int get_shift_t();
//void set_sat(int value);
//int get_sat();

void set_flag_n();
void set_flag_z();
void set_flag_c();
void set_flag_v();
void set_flag_q();
void set_calculate_carry();
void set_calculate_overflow();

void cle_flag_n();
void cle_flag_z();
void cle_flag_c();
void cle_flag_v();
void cle_flag_q();
void cle_calculate_carry();
void cle_calculate_overflow();

int get_flag_n();
int get_flag_z();
int get_flag_c();
int get_flag_v();
int get_flag_q();
int get_calculate_carry();
int get_calculate_overflow();

// Operations on special registers
void set_apsr(int value);	// APSR = XPSR<31:27>:'000000000000000000000000000'
int get_apsr();
void set_iapsr(int value);	// IAPSR = APSR<31:27>:'000000000000000000':IPSR<8:0>
int get_iapsr();
void set_eapsr(int value);	// EAPSR = APSR<31:27>:EPSR<26:25>:EPSR<24>:'00000000':EPSR<15:10>:'0000000000'
int get_eapsr();
void set_xpsr(int value);	// XPSR = APSR<31:27>:EPSR<26:25>:EPSR<24>:'00000000':EPSR<15:10>:'0':IPSR<8:0>
int get_xpsr();
void set_ipsr(int value);	// IPSR = '00000000000000000000000':XPSR<8:0>
int get_ipsr();
void set_epsr(int value);	// EPSR = '00000':XPSR<26:25>:XPSR<24>:'00000000':XPSR<15:10>:'0000000000'
int get_epsr();
void set_iepsr(int value);	// IEPSR = '00000':EPSR<26:25>:EPSR<24>:'00000000':EPSR<15:10>
int get_iepsr();
void set_msp(int value);
int get_msp();
void set_psp(int value);
int get_psp();
void set_primask(int value);
int get_primask();
void set_basepri(int value);
int get_basepri();
void set_basepri_max(int value);
int get_basepri_max();
void set_faultmask(int value);
int get_faultmask();
void set_control(int value);
int get_control();

#endif
