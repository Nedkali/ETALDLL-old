

#include <vector>

#include "D2Handlers.h"
#include "D2NetHandlers.h"

#include "Main.h"
#include "Offset.h"
#include "D2Ptrs.h"
#include "CommandLine.h"
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
	sLine* command;
	SendCopyData(1, "Loading");	
		
	WideCharToMultiByte(0, 0, Prof.CdKeys, -1, Vars.szMpqfile, 128, 0, 0);
	
	SendCopyData(11, Vars.szMpqfile);

	ParseCommandLine(GetCommandLineA());

	command = GetCommand("-c0");

	if (command)
	{
		Vars.bUseRawCDKey = 1;
		const char *keys = (char*)command->szText;
		int len = strlen(keys);
		strncat_s(Vars.szClassic, keys, len);
	}

	command = GetCommand("-c1");

	if (command)
	{
		const char *keys = (char*)command->szText;
		int len = strlen(keys);
		strncat_s(Vars.szClassic, keys, len);
	}

	command = GetCommand("-c2");

	if (command)
	{
		const char *keys = (char*)command->szText;
		int len = strlen(keys);
		strncat_s(Vars.szClassic, keys, len);
	}

	command = GetCommand("-e0");

	if (command)
	{
		const char *keys = (char*)command->szText;
		int len = strlen(keys);
		strncat_s(Vars.szLod, keys, len);
	}

	command = GetCommand("-e1");

	if (command)
	{
		const char *keys = (char*)command->szText;
		int len = strlen(keys);
		strncat_s(Vars.szLod, keys, len);
	}

	command = GetCommand("-e2");

	if (command)
	{
		const char *keys = (char*)command->szText;
		int len = strlen(keys);
		strncat_s(Vars.szLod, keys, len);
	}

	if (Vars.bUseRawCDKey == 1)
	{
		SendCopyData(11, "Load Raw Key");
		InstallConditional();
	}


	command = GetCommand("-mpq");

	if (command)
	{
		SendCopyData(11, "Load mpq");
		LoadMPQ(command->szText);
	}

	//if (strlen(Vars.szMpqfile) > 0){
	//	SendCopyData(11, "Load mpq");
	//	//LoadMPQ(Vars.szMpqfile);
	//}

	if (strlen(Vars.szScript) == 0){

		SendCopyData(11, "No script = loader only - Exiting dll");
		return true;
	}



	return true;

}

