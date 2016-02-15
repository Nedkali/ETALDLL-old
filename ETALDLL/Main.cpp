// dllmain.cpp : Defines the entry point for the DLL application.

#include <shlwapi.h>
#include "OOG.h"
//#include "Main.h"
#include "D2Pointers.h"
#include "Common.h"
#include "Constants.h"
#include "Input.h"
#include "D2Structs.h"




void WaitForDlls()
{
	unsigned int v = 0;
	do {
		Sleep(500);
		if (GetModuleHandle("Bnclient.DLL") && GetModuleHandle("D2Launch.DLL") && GetModuleHandle("D2Net.DLL"))
			break;
		++v;
	} while (v < 10);
}

<<<<<<< HEAD
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		//int a = sizeof(Prof);//place mouse over "sizeof" to find struct size
		HANDLE hMap = OpenFileMappingA(FILE_MAP_READ, false, "D2NT Profile");
		if (!hMap) {
			MessageBoxA(NULL, "MMf not found", "Debug", NULL);
			return 0;
		}
		HANDLE mView = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 71);
		if (!mView) {
=======
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
>>>>>>> origin/master
			CloseHandle(hMap);
			MessageBoxA(NULL, "MMf not found", "Debug", NULL);
			return 0;
		}

		memcpy(&Prof, mView, 71);
		UnmapViewOfFile(mView);
		CloseHandle(hMap);

		DisableThreadLibraryCalls(hModule);
		WaitForDlls();

<<<<<<< HEAD
		Vars.hModule = hModule;
		GetModuleFileName(hModule, Vars.szScriptPath, MAX_PATH);
		PathRemoveFileSpec(Vars.szScriptPath);
		strcat_s(Vars.szScriptPath, MAX_PATH, "\\Scripts\\");

		//CheckStruct();
		HANDLE hD2Thread;
		if ((hD2Thread = CreateThread(NULL, NULL, MainThread, NULL, NULL, NULL)) == NULL)
			//return FALSE;
=======
			//MessageBox(NULL, "Debug", "pausing", NULL);
			DeleteDatFiles();

			unsigned int v = 0;
			do {
				Sleep(100);
				if (GetModuleHandle("Bnclient.DLL") && GetModuleHandle("D2Launch.DLL") && GetModuleHandle("D2Net.DLL") && GetModuleHandle("D2Win.DLL"))
					break;
				++v;
			} while (v < 10);
			DefineOffsets();
			InstallPatches();

			if ((hD2Thread = CreateThread(NULL, NULL, D2Thread, NULL, NULL, NULL)) == NULL)
				return FALSE;

			MessageBoxA(NULL, "DLL Attached", "Debug", NULL);
>>>>>>> origin/master
			break;

	}
	return TRUE;
}

