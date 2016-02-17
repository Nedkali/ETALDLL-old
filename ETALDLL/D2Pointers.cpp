//////////////////////////////////////////////////////////////////////
// Pointers.cpp
//////////////////////////////////////////////////////////////////////
#define DEFINE_POINTERS
#include "D2Pointers.h"
#include "Patch.h"

#ifndef ArraySize
#define ArraySize(x) (sizeof((x)) / sizeof((x)[0]))
#endif

Pointer::Pointer()
{

}

Pointer::~Pointer()
{

}

DWORD Pointer::GetDllOffset(const char* DLL_NAME, int OFFSET)
{
	HMODULE hMod = GetModuleHandle(DLL_NAME);
	if (!hMod)
	{
		hMod = LoadLibrary(DLL_NAME);
		if (!hMod)
		{
			return 0;
		}
	}
	if (OFFSET < 0)
	{
		return (DWORD)GetProcAddress(hMod, (LPCSTR)(-OFFSET));
	}
	return (DWORD)hMod + OFFSET;
}

DWORD Pointer::GetDllOffset(int num)
{
	static char *dlls[] = { "D2Client.DLL", "D2Common.dll", "D2gfx.dll", "D2Lang.dll",
		"D2Win.dll", "D2Net.dll", "D2Game.dll", "D2Launch.dll", "Fog.dll", "Bnclient.dll",
		"Storm.dll", "D2CMP.dll", "D2Multi.dll" };
	if ((num & 0xff) > 12)
		return 0;
	return Pointer::GetDllOffset(dlls[num & 0xff], num >> 8);
}
BOOL Pointer::ADDRawKeys(const char* classic, const char* lod)
{
	strncat_s(Vars.szClassic, classic, strlen(classic));
	strncat_s(Vars.szLod, lod, strlen(lod));

	if (classic && lod != NULL) {
		Pointer::InstallConditional();
		return true;
	}
	return false;
}
void Pointer::InstallConditional()
{
	for (int x = 0; x < ArraySize(Conditional); x++)
	{
		Conditional[x].bOldCode = new BYTE[Conditional[x].dwLen];
		::ReadProcessMemory(GetCurrentProcess(), (void*)Conditional[x].dwAddr, Conditional[x].bOldCode, Conditional[x].dwLen, NULL);
		Conditional[x].pFunc(Conditional[x].dwAddr, Conditional[x].dwFunc, Conditional[x].dwLen);
	}
}

void Pointer::RemoveConditional()
{
	for (int x = 0; x < ArraySize(Conditional); x++)
	{
		Pointer::WriteBytes((void*)Conditional[x].dwAddr, Conditional[x].bOldCode, Conditional[x].dwLen);
		delete[] Conditional[x].bOldCode;
	}
}

BOOL Pointer::WriteBytes(void *pAddr, void *pData, DWORD dwLen)
{
	DWORD dwOld;

	if (!VirtualProtect(pAddr, dwLen, PAGE_READWRITE, &dwOld))
		return FALSE;

	::memcpy(pAddr, pData, dwLen);
	return VirtualProtect(pAddr, dwLen, dwOld, &dwOld);
}

void Pointer::FillBytes(void *pAddr, BYTE bFill, DWORD dwLen)
{
	BYTE *bCode = new BYTE[dwLen];
	::memset(bCode, bFill, dwLen);

	Pointer::WriteBytes(pAddr, bCode, dwLen);

	delete[] bCode;
}

void Pointer::InterceptLocalCode(BYTE bInst, DWORD pAddr, DWORD pFunc, DWORD dwLen)
{
	BYTE *bCode = new BYTE[dwLen];
	::memset(bCode, 0x90, dwLen);
	DWORD dwFunc = pFunc - (pAddr + 5);

	bCode[0] = bInst;
	*(DWORD *)&bCode[1] = dwFunc;
	Pointer::WriteBytes((void*)pAddr, bCode, dwLen);

	delete[] bCode;
}

void Pointer::PatchCall(DWORD dwAddr, DWORD dwFunc, DWORD dwLen)
{
	Pointer::InterceptLocalCode(INST_CALL, dwAddr, dwFunc, dwLen);
}

void Pointer::PatchJmp(DWORD dwAddr, DWORD dwFunc, DWORD dwLen)
{
	Pointer::InterceptLocalCode(INST_JMP, dwAddr, dwFunc, dwLen);
}

void Pointer::PatchBytes(DWORD dwAddr, DWORD dwValue, DWORD dwLen)
{
	BYTE *bCode = new BYTE[dwLen];
	::memset(bCode, (BYTE)dwValue, dwLen);

	Pointer::WriteBytes((LPVOID)dwAddr, bCode, dwLen);

	delete[] bCode;
}
