//////////////////////////////////////////////////////////////////////
// Pointers.cpp
//////////////////////////////////////////////////////////////////////
#define DEFINE_POINTERS
#include "D2Pointers.h"

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
