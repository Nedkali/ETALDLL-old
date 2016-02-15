

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

	Input* input = new Input;
	input->Initialize();

	bool starter = true;
	bool ingame = false;


	while (true)
	{
		switch (OOG::ClientState())
		{
		case ClientStateInGame:
			if (ingame)
			{
				Sleep(10);
			}
			else
			{
				Sleep(1000);
				ingame = true;
				starter = true;
				SetWindowText(fpGetHwnd(), "Etal - In Game");
			}
			break;
		case ClientStateMenu:
			if (starter)
			{
				starter = false;
				ingame = false;
				SetWindowText(fpGetHwnd(), "Etal");
				Sleep(1000);
			}
			Logincontrol();
			break;
		case ClientStateBusy:
			Sleep(1000);
			break;
		case ClientStateNull:
			Sleep(1000);

			break;
		}
		Sleep(100);
	}

	return 0;

	return true;

}

void  Logincontrol()
{

	switch (OOG::GetLocationID())
	{

	case OOG_MAIN_MENU:
	{

		if (Prof.Realm == 0)//SinglePlayer
		{
			Control* pControl = OOG::findControl(CONTROL_BUTTON, (char *)NULL, -1, 264, 324, 272, 35);
			if (pControl && pControl->wText2) {
				OOG::clickControl(pControl, 295, 315);
				Sleep(1000);
			}
			return;
		}


		Control* pControl = OOG::findControl(CONTROL_BUTTON, (char *)NULL, -1, 264, 391, 272, 25);
		if (pControl && pControl->wText2) {
			char* cstr = "";
			char* szLine = wchart_to_char(pControl->wText2);

			if (Prof.Realm == 1) { cstr = "GATEWAY: U.S. WEST"; }
			if (Prof.Realm == 2) { cstr = "GATEWAY: U.S. EAST"; }
			if (Prof.Realm == 3) { cstr = "GATEWAY: ASIA"; }
			if (Prof.Realm == 4) { cstr = "GATEWAY: EUROPE"; }

			if (strcmp(cstr, szLine) != 0) {
				if (!OOG::clickControl(pControl, 364, 375))
					return;

				Sleep(750);
				if (!OOG::clickControl(pControl, -1, 320 + ((Prof.Realm * 24) + 12))) { return; }

				//OK Button
				pControl = OOG::findControl(CONTROL_BUTTON, (char *)NULL, -1, 281, 538, 96, 32);
				if (pControl) {
					if (!OOG::clickControl(pControl, 281, 515)) { return; }
				}
				Sleep(750);
			}
			// Bnet connect
			pControl = OOG::findControl(CONTROL_BUTTON, "BATTLE.NET", -1, -1, -1, -1, -1);

			if (pControl) {
				Sleep(50);
				Input::SendMouseClick(295, 355, 0);
				Sleep(50);
			}
			while (true) {
				Sleep(250);
				if (OOG::GetLocationID() == 9) { break; }
			}

		}
	}
	break;

	case OOG_CHAR_SELECT:
		Sleep(2000);
		OOG::SelectCharacter(Prof.CharName);
		//if (!OOG::SelectCharacter(Prof.CharName)) {
		//	MessageBoxA(NULL, "Character not found", "Error", NULL);
		//}
		Sleep(750);
		break;

	case OOG_DIFFICULTY:// Single Player difficulty select
		if (Prof.Difficulty == 0)
			Input::SendMouseClick(398, 280, 0);
		if (Prof.Difficulty == 1)
			Input::SendMouseClick(398, 322, 0);
		if (Prof.Difficulty == 2)
			Input::SendMouseClick(398, 366, 0);
		Sleep(750);
		break;

	case OOG_LOGIN:
	{
		Sleep(1000);
		// enter Account name
		Control* pControl = OOG::findControl(1, (char *)NULL, -1, 322, 342, 162, 19);
		if (!pControl)
			return;

		OOG::SetControlText(pControl, Prof.Account);
		Sleep(750);

		// enter pass
		pControl = OOG::findControl(1, (char *)NULL, -1, 322, 396, 162, 19);
		if (!pControl)
			return;

		OOG::SetControlText(pControl, Prof.AccPass);
		Sleep(1200);
		// click login
		pControl = OOG::findControl(6, (char *)NULL, -1, 264, 484, 272, 35);
		if (pControl)
		{
			OOG::clickControl(pControl, 264, 470);
		}
		Sleep(500);
	}
	break;
	case	OOG_D2SPLASH://	//18 Spash
		SetWindowText(fpGetHwnd(), "Diabase Mule");
		Sleep(50);
		Input::SendMouseClick(10, 10, 0);
		Sleep(2000);
		break;
	case OOG_LOGIN_ERROR:
		//char* temp = Prof.Account;
		//
		//if (Prof.Realm == 1)
		//	strcat_s(temp, 125, ", USWest");
		//if (Prof.Realm == 2)
		//	strcat_s(temp, 125, ", USEast");
		//if (Prof.Realm == 3)
		//	strcat_s(temp, 125, ", Asia");
		//if (Prof.Realm == 4)
		//	strcat_s(temp, 125, ", Europe");
		//char temp1[125];
		//strcpy_s(temp1, temp);
		//SendCopyData(10, temp1);		
		break;
	}

	return;
}