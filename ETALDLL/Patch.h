#pragma once
#include "D2Intercepts.h"
#include "OOG.h"
#include "Offset.h"
PatchHook Conditional[] = {
	{PatchJmp,	GetDllOffset("Bnclient.dll",0x15EB3),	(DWORD)ClassicSTUB,		5}, 
	{PatchJmp,	GetDllOffset("Bnclient.dll",0x161B8),	(DWORD)LodSTUB,			5} 
};