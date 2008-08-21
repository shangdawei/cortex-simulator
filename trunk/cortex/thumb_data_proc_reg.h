#ifndef THUMB_DATA_PROC_REG_H_
#define THUMB_DATA_PROC_REG_H_

typedef void (*func)(short instruction);

struct DATAPROCREG
{
	unsigned short Rdn	:3;
	unsigned short Rm	:3;
	unsigned short opc	:4;
	unsigned short pass	:6;
	
}DataProcReg;

void *data_proc_reg_process[16]=
{
	(void *)thumb_and_reg,//0
	(void *)thumb_eor_reg,
	(void *)thumb_lsl_reg,
	(void *)thumb_lsr_reg,
	
	(void *)thumb_asr_reg,//4
	(void *)thumb_adc_reg,
	(void *)thumb_sbc_reg,
	(void *)thumb_ror_reg,
	
	(void *)thumb_tst_reg,//8
	(void *)thumb_rsb_reg,
	(void *)thumb_cmp_reg_t1,
	(void *)thumb_cmn_reg,
	
	(void *)thumb_orr_reg,//12
	(void *)thumb_mul_reg,
	(void *)thumb_bic_reg,
	(void *)thumb_mvn_reg
};

#endif /*THUMB_DATA_PROC_REG_H_*/
