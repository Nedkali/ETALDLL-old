#pragma once
#include "D2Intercepts.h"
#include "OOG.h"
#include "Offset.h"
PatchHook Conditional[] = {
	{ Pointer::PatchJmp,	Pointer::GetDllOffset("Bnclient.dll",0x15EB3),	(DWORD)ClassicSTUB,		5},
	{ Pointer::PatchJmp,	Pointer::GetDllOffset("Bnclient.dll",0x161B8),	(DWORD)LodSTUB,			5}
};