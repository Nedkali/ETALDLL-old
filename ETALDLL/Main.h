#ifndef __DBase_H__
#define __DBase_H__

#pragma once
#include <windows.h>
#include <vector>



struct Profile {
	char Account[24];
	char AccPass[12];
	char Charloc;
	char Realm;
	char Difficulty;
	char ScriptFile[32];
};

struct Variables
{
	char	szPath[MAX_PATH];
	char	szScriptPath[MAX_PATH];
	char	szMpqfile[MAX_PATH];
	char	szClassic[30];
	char	szLod[30];
	bool	bzladder;
	unsigned int iCharPos;

<<<<<<< HEAD
=======
	BOOL	bLoadedWithCGuard;
	BOOL	bShutdownFromDllMain;
	BOOL	bUseRawCDKey;

	Module* pModule;
>>>>>>> origin/master
	HMODULE hModule;
};

extern Profile  Prof;
extern Variables Vars;

#endif