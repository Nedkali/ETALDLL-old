// dllmain.cpp : Defines the entry point for the DLL application.
#define _CRT_SECURE_NO_WARNINGS
#include <shlwapi.h>
#include <io.h>
#include <string>

#include "Offset.h"
#include "D2Handlers.h"
#include "Main.h"
#include "D2Ptrs.h"

static HANDLE hD2Thread = INVALID_HANDLE_VALUE;

int DeleteDatFiles()
{

	struct _WIN32_FIND_DATAA FindFileData;
	char pszPath[MAX_PATH];
	char Dst[MAX_PATH];
	char Buffer[MAX_PATH];

	GetCurrentDirectoryA(MAX_PATH, Buffer);
	memset(&Dst, 0, MAX_PATH);
	strcpy_s(Dst, MAX_PATH, Buffer);
	PathAppend(Dst, "\\*.dat");
	HANDLE v0 = FindFirstFile(Dst, &FindFileData);
	if (v0 != (HANDLE)-1)
	{
		do
		{
			memset(&pszPath, 0, MAX_PATH);
			strcpy_s(pszPath, MAX_PATH, Buffer);
			PathAppend(pszPath, FindFileData.cFileName);
			DeleteFile(pszPath);
		} while (FindNextFile(v0, &FindFileData));
		FindClose(v0);
	}
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hDll, DWORD  ul_reason_for_call, LPVOID lpReserved ){

	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			HANDLE hMap = OpenFileMappingA(FILE_MAP_READ, false, "D2NT Profile");
			if (!hMap){
				return 0;
			}
			HANDLE mView = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 1010);
			if (!mView){
				CloseHandle(hMap);
				return 0;
			}

			memcpy(&Prof, mView, 1010);
			UnmapViewOfFile(mView);
			CloseHandle(hMap);

			DisableThreadLibraryCalls(hDll);
			if (lpReserved != NULL)	{
				Vars.pModule = (Module*)lpReserved;
				if (!Vars.pModule)
					return FALSE;

				strcpy_s(Vars.szScriptPath, MAX_PATH, Vars.pModule->szPath);
			}
			else{
				Vars.hModule = hDll;
				GetModuleFileName(hDll, Vars.szScriptPath, MAX_PATH);
				PathRemoveFileSpec(Vars.szScriptPath);
				strcat_s(Vars.szScriptPath, MAX_PATH, "\\");
			}

			//MessageBox(NULL, "Debug", "pausing", NULL);
			DeleteDatFiles();

			if ((hD2Thread = CreateThread(NULL, NULL, D2Thread, NULL, NULL, NULL)) == NULL)
				return FALSE;

			break;
	}
	return TRUE;
}

