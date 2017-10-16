#include <Windows.h>

#include "Listener.h"

DWORD WINAPI Run(LPVOID lpParam)
{
	Listener listener;
	
	listener.Listen();

	return NULL;
}

BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD reason,
	LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0x100, Run, 0, 0, NULL);

		break;
	default:
		break;
	}

	return TRUE;
}