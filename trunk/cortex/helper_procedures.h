#ifndef _HELPER_PROCEDURES
#define _HELPER_PROCEDURES

#include "register.h"
#include "memory.h"
typedef enum{false=0, true} bool;

struct TWOWORD{
	int word1;
	int word2;
}twoWord;

void ALUWritePC(int value);
int ArchVersion();
bool Bad_Reg(int n);
bool BigEndian();
void BranchWritePC(int value);
void BreakPoint();
void BXWritePC(int value);
void CallSupervisor();
void ClearEventRegister();
void ClearExclusiveMonitors();
bool ConditionPassed();
bool Coproc_Accepted(int cp_num, int instr);
bool Coproc_DoneLoading(int cp_num, int instr);
bool Coproc_DoneStoring(int cp_num, int instr);
int Coproc_GetOneWord(int cp_num, int instr);
struct twoWord* Coproc_GetTwoWords(int cp_num, int instr);
int Coproc_GetWordToStore(int cp_num, int instr);
void Coproc_InternalOperation(int cp_num, int instr);
void Coproc_SendLoadedWord(int word, int cp_num, int instr);
void Coproc_SendOneWord(int word, int cp_num, int instr);
void Coproc_SendTwoWords(int word1, int word2, int cp_num,int instr);
bool CurrentModeIsPrivileged();
void DataMemoryBarrier(char option);
void DataSynchronizationBarrier(char option);
void DecodeImmShift();
void DecodeRegShift();
bool EventRegistered();
void EncodingSpecificOperations();
bool ExclusiveMonitorsPass(int address, int size);
int ExecutionPriority();
void Hint_Debug(char option);
void Hint_PreloadData(int address);
void Hint_PreloadInstr(int address);
void Hint_SendEvent();
void Hint_Yield();
bool InITBlock();
void InstructionSynchronizationBarrier(char option);
bool IntegerZeroDivideTrappingEnabled();
bool LastInITBlock();
void LoadWritePC(int value);
void RaiseCoprocessorException();
void RaiseIntegerZeroDivide();
void SetExclusiveMonitors(int address, int size);
void StartITBlock(int firstcond, int mask);
int ThisInstr();
void WaitForEvent();
void WaitForInterrupt();




#endif