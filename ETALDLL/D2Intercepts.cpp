#include "D2Intercepts.h"
#include "OOG.h"

VOID __declspec(naked) __fastcall ClassicSTUB()
{
	__asm {
		lea eax, dword ptr ss : [Vars.szClassic]
			mov dword ptr ds : [0x6FF3E928], eax
			jmp BNCLIENT_DClass;
	}
	*p_BNCLIENT_ClassicKey = Vars.szClassic;
}

VOID _declspec(naked) _fastcall NameSTUB()
{
	_asm {
		lea eax, dword ptr ss : [Vars.szKeyOwner]
			mov dword ptr ds : [0x6FF3E934], eax		
			jmp BNCLIENT_DName;
	}
	*p_BNCLIENT_KeyOwner = Vars.szKeyOwner;
}

VOID __declspec(naked) __fastcall LodSTUB()
{
	__asm {
		lea eax, dword ptr ss : [Vars.szLod]
			mov dword ptr ds : [0x6FF3E930], eax
			jmp BNCLIENT_DLod;
	}
	*p_BNCLIENT_XPacKey = Vars.szLod;
}