#include <ctime>

#include "Listener.h"

Listener::Listener() :
	healthAddress(GetAddressFromOffsets(HealthBaseAddress, HealthOffsets, HealthOffsetsCount))
{
}

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

	if (GetAsyncKeyState(VK_F2))
	{
		HandleRapidFireCommand();
	}

	if (GetAsyncKeyState(VK_F3))
	{
		HandleRecoilCommand();
	}

	if (GetAsyncKeyState(VK_F4) || infiniteHealthOn)
	{
		if (GetAsyncKeyState(VK_F4))
		{
			infiniteHealthOn = !infiniteHealthOn;
		}

		HandleHealthCommand();
	}
}

void Listener::HandleAmmoCommand()
{
	infiniteAmmoOn = !infiniteAmmoOn;

	if (infiniteAmmoOn)
	{
		WriteToMemory(AmmoBaseAddress, AmmoTargetOpCode, DefaultOpCodeSize);
	}
	else
	{
		WriteToMemory(AmmoBaseAddress, AmmoDefOpCode, DefaultOpCodeSize);
	}
}

void Listener::HandleRapidFireCommand()
{
	rapidFireOn = !rapidFireOn;

	if (rapidFireOn)
	{
		WriteToMemory(RapidFireBaseAddress, RapidFireTargetOpCode, DefaultOpCodeSize);
		WriteToMemory(AutomaticBaseAddress, AutomaticTargetOpCode, DefaultOpCodeSize);
	}
	else
	{
		WriteToMemory(RapidFireBaseAddress, RapidFireDefOpCode, DefaultOpCodeSize);
		WriteToMemory(AutomaticBaseAddress, AutomaticDefOpCode, DefaultOpCodeSize);
	}
}

void Listener::HandleRecoilCommand()
{
	antiRecoilOn = !antiRecoilOn;

	if (antiRecoilOn)
	{
		for (size_t i = 0; i < RecoilBaseAddressesCount; i++)
		{
			WriteToMemory(RecoilBaseAddresses[i], RecoilTargetOpCodes[i], RecoilTargetOpCodeSizes[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < RecoilBaseAddressesCount; i++)
		{
			WriteToMemory(RecoilBaseAddresses[i], RecoilDefOpCodes[i], RecoilDefOpCodeSizes[i]);
		}
	}
}

void Listener::HandleHealthCommand()
{
	if (infiniteHealthOn)
	{
		WriteToMemory(healthAddress, TargetHealth, DefaultOpCodeSize);
	}
	else
	{
		WriteToMemory(healthAddress, DefaultHealth, DefaultOpCodeSize);
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

DWORD Listener::GetAddressFromOffsets(
	const DWORD baseAddress,
	const DWORD offsets[],
	const int offsetsCount) const
{
	if (offsetsCount == 0)
	{
		return baseAddress;
	}

	DWORD targetAddress = *(DWORD*)(baseAddress);

	for (size_t i = 0; i < offsetsCount; i++)
	{
		targetAddress = DWORD(targetAddress + offsets[i]);
	}

	return targetAddress;
}