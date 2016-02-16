#include "D2Intercepts.h"
#include "OOG.h"

DWORD DClass = 0x6FF35EB8;
DWORD DLod = 0x6FF361BD;

VOID __declspec(naked) __fastcall ClassicSTUB()
{
	__asm {
		lea eax, dword ptr ss : [Vars.szClassic]
			mov dword ptr ds : [0x6FF3E928], eax
			jmp DClass;
	}

}

VOID __declspec(naked) __fastcall LodSTUB()
{
	__asm {
		lea eax, dword ptr ss : [Vars.szLod]
			mov dword ptr ds : [0x6FF3E930], eax
			jmp DLod;
	}

}