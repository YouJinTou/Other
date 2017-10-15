#include <Windows.h>

extern int main();

DWORD WINAPI Run(LPVOID lpParam)
{

}

BOOL APIENTRY InjectableMain(
	HMODULE hModule,
	DWORD reason,
	LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0x100, &Run, 0, 0, NULL);

		break;
	default:
		break;
	}

	return true;
}