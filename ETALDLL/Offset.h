#ifndef _OFFSET_H
#define _OFFSET_H

#define INST_INT3	0xCC
#define INST_CALL	0xE8
#define INST_NOP	0x90
#define INST_JMP	0xE9
#define INST_RET	0xC3


void DefineOffsets();
DWORD GetDllOffset(int num);
DWORD GetDllOffset(char *DllName, int Offset);


#endif