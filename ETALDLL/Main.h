#ifndef __D2BS_H__
#define __D2BS_H__

#pragma once
//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include <cstdint>

struct Profile{
	wchar_t ProfileName[32];
	wchar_t D2Folder[260];
	uint8_t WindowMode;
	uint8_t D2Sound;
	uint8_t D2Quality;
	uint8_t D2DirectText;
	uint8_t D2Minimized;
	uint8_t unused;
	wchar_t CdKeys[128];
	wchar_t CdSwap[3];
	wchar_t Account[24];
	wchar_t GameName[12];
	wchar_t GamePassword[8];
	uint8_t PlayType;
	uint8_t Realm;
	uint8_t Difficulty;
	uint8_t CharLoc;
	uint8_t RandomGameName;
	uint8_t RandomGamePassword;
	wchar_t ScriptFile[32];
}; 

#define D2NT_MGR_LOADING		1
#define D2NT_MGR_READY			2
#define D2NT_MGR_LOGIN			3
#define D2NT_MGR_CREATE_GAME	4
#define D2NT_MGR_INGAME			5
#define D2NT_MGR_RESTART		6
#define D2NT_MGR_CHICKEN		7
#define D2NT_MGR_PRINT_STATUS	8
#define D2NT_MGR_COMMON			9
#define D2NT_MGR_ITEM_LOG		10
#define D2NT_MGR_ERROR_LOG		11


struct Module
{
	union {
		HMODULE hModule;
		DWORD dwBaseAddress;
	};
	DWORD _1;
	char szPath[MAX_PATH];
};

struct Variables
{
	char	szPath[MAX_PATH];
	char	szScriptPath[MAX_PATH];
	char	szMpqfile[MAX_PATH];
	char	szScript[MAX_PATH];
	char	szDefault[_MAX_FNAME];
	char	szClassic[30];
	char	szLod[30];


	unsigned int iCharPos;

	BOOL	bLoadedWithCGuard;
	BOOL	bShutdownFromDllMain;
	BOOL	bUseRawCDKey;

	Module* pModule;
	HMODULE hModule;
};



extern Variables Vars;
extern Profile  Prof;
#endif