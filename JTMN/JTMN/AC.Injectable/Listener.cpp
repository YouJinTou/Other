#include <ctime>

#include "Listener.h"

void Listener::Listen()
{
	while (true)
	{
		HandleUserCommand();

		Sleep(100);
	}
}

void Listener::HandleUserCommand()
{
	if (GetAsyncKeyState(VK_F1))
	{
		HandleAmmoCommand();
	}
}

void Listener::HandleAmmoCommand()
{
	infiniteAmmoOn = !infiniteAmmoOn;

	if (infiniteAmmoOn)
	{
		WriteToMemory(AmmoBaseAddress, AmmoTargetOpCode, AmmoTargetOpCodeSize);
	}
	else
	{
		WriteToMemory(AmmoBaseAddress, AmmoDefOpCode, AmmoDefOpCodeSize);
	}
}

void Listener::WriteToMemory(
	const DWORD address,
	const char* valueToWrite, 
	const int pageByteSize)
{
	unsigned long oldProtection;
	
	VirtualProtect((LPVOID)address, pageByteSize, PAGE_EXECUTE_READWRITE, &oldProtection);

	memcpy((LPVOID)address, valueToWrite, pageByteSize);

	VirtualProtect((LPVOID)address, pageByteSize, oldProtection, NULL);
}
