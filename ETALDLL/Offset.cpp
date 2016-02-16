#define _DEFINE_VARS
#include "D2Pointers.h"
#include "Offset.h"
#include "Main.h"
#include "Patch.h"

#ifndef ArraySize
#define ArraySize(x) (sizeof((x)) / sizeof((x)[0]))
#endif

DWORD GetDllOffset(char *DllName, int Offset)
{
	HMODULE hMod = GetModuleHandle(DllName);

	if (!hMod)
		hMod = LoadLibrary(DllName);

	if (!hMod)
		return 0;

	if (Offset < 0)
		return (DWORD)GetProcAddress(hMod, (LPCSTR)(-Offset));

	return ((DWORD)hMod) + Offset;
}

DWORD GetDllOffset(int num)
{
	static char *dlls[] = { "D2Client.DLL", "D2Common.dll", "D2gfx.dll", "D2Lang.dll",
		"D2Win.dll", "D2Net.dll", "D2Game.dll", "D2Launch.dll", "Fog.dll", "Bnclient.dll",
		"Storm.dll", "D2CMP.dll", "D2Multi.dll" };
	if ((num & 0xff) > 12)
		return 0;
	return GetDllOffset(dlls[num & 0xff], num >> 8);
}

void InstallConditional()
{
	for (int x = 0; x < ArraySize(Conditional); x++)
	{
		Conditional[x].bOldCode = new BYTE[Conditional[x].dwLen];
		::ReadProcessMemory(GetCurrentProcess(), (void*)Conditional[x].dwAddr, Conditional[x].bOldCode, Conditional[x].dwLen, NULL);
		Conditional[x].pFunc(Conditional[x].dwAddr, Conditional[x].dwFunc, Conditional[x].dwLen);
	}
}

void RemoveConditional()
{
		for (int x = 0; x < ArraySize(Conditional); x++)
		{
			WriteBytes((void*)Conditional[x].dwAddr, Conditional[x].bOldCode, Conditional[x].dwLen);
			delete[] Conditional[x].bOldCode;
		}
}

BOOL WriteBytes(void *pAddr, void *pData, DWORD dwLen)
{
	DWORD dwOld;

	if (!VirtualProtect(pAddr, dwLen, PAGE_READWRITE, &dwOld))
		return FALSE;

	::memcpy(pAddr, pData, dwLen);
	return VirtualProtect(pAddr, dwLen, dwOld, &dwOld);
}

void FillBytes(void *pAddr, BYTE bFill, DWORD dwLen)
{
	BYTE *bCode = new BYTE[dwLen];
	::memset(bCode, bFill, dwLen);

	WriteBytes(pAddr, bCode, dwLen);

	delete[] bCode;
}

void InterceptLocalCode(BYTE bInst, DWORD pAddr, DWORD pFunc, DWORD dwLen)
{
	BYTE *bCode = new BYTE[dwLen];
	::memset(bCode, 0x90, dwLen);
	DWORD dwFunc = pFunc - (pAddr + 5);

	bCode[0] = bInst;
	*(DWORD *)&bCode[1] = dwFunc;
	WriteBytes((void*)pAddr, bCode, dwLen);

	delete[] bCode;
}

void PatchCall(DWORD dwAddr, DWORD dwFunc, DWORD dwLen)
{
	InterceptLocalCode(INST_CALL, dwAddr, dwFunc, dwLen);
}

void PatchJmp(DWORD dwAddr, DWORD dwFunc, DWORD dwLen)
{
	InterceptLocalCode(INST_JMP, dwAddr, dwFunc, dwLen);
}

void PatchBytes(DWORD dwAddr, DWORD dwValue, DWORD dwLen)
{
	BYTE *bCode = new BYTE[dwLen];
	::memset(bCode, (BYTE)dwValue, dwLen);

	WriteBytes((LPVOID)dwAddr, bCode, dwLen);

	delete[] bCode;
}
