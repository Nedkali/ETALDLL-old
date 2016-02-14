

#include <vector>

#include "D2Handlers.h"
#include "D2NetHandlers.h"

#include "Main.h"
#include "Offset.h"
#include "D2Ptrs.h"

using namespace std;



bool  SendCopyData(unsigned int  code, char* data) {

	HWND EtalhWnd = FindWindowA(NULL, "Etal Manager");
	if (!EtalhWnd)
		return false;
	if (data == NULL)
		data = "";
	data = data + char(0);
	DWORD thwnd = GetCurrentProcessId();
	COPYDATASTRUCT* aCopy = new COPYDATASTRUCT();
	aCopy->dwData = code;
	aCopy->cbData = strlen(data) + 1;
	aCopy->lpData = data;

	if (SendMessageA(EtalhWnd, WM_COPYDATA, thwnd, (LPARAM)aCopy))
		return true;
	return false;
}

void LoadMPQ(const char* mpq)
{
	D2WIN_InitMPQ("D2Win.DLL", mpq, NULL, 0, 0);
	*p_BNCLIENT_XPacKey = *p_BNCLIENT_ClassicKey = *p_BNCLIENT_KeyOwner = NULL;
	BNCLIENT_DecodeAndLoadKeys();

}

DWORD WINAPI D2Thread(LPVOID lpParam)
{
	SendCopyData(1, "Loading");
	unsigned int v = 0;
	do	{
		Sleep(500);
		if (GetModuleHandle("Bnclient.DLL") && GetModuleHandle("D2Launch.DLL") && GetModuleHandle("D2Net.DLL") && GetModuleHandle("D2Win.DLL"))
			break;
		++v;
	} while (v < 10);
		
	WideCharToMultiByte(0, 0, Prof.CdKeys, -1, Vars.szMpqfile, 128, 0, 0);

	SendCopyData(11, Vars.szMpqfile);
	DefineOffsets();
	
	if (strlen(Vars.szMpqfile) > 0){
		LoadMPQ(Vars.szMpqfile);
	}

	if (strlen(Vars.szScript) == 0){

		SendCopyData(11, "Exiting dll");
		return true;
	}



	return true;

}

