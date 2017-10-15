#include "TargetAddress.h"

TargetAddress::TargetAddress(
	const int replacementValue,
	const DWORD baseAddress, 
	const std::vector<DWORD> offsets) :
	replacementValue(replacementValue),
	baseAddress(baseAddress),
	offsets(offsets)
{
}

DWORD TargetAddress::GetAddress(const HANDLE hProcess)
{
	if (addressFound)
	{
		return targetAddress;
	}

	addressFound = true;
	targetAddress = baseAddress;
	DWORD buffer;

	ReadProcessMemory(
		hProcess, (LPCVOID)targetAddress, &buffer, sizeof(targetAddress), NULL);

	for (auto offset : offsets)
	{
		targetAddress = buffer + offset;

		ReadProcessMemory(
			hProcess, (LPCVOID)targetAddress, &buffer, sizeof(targetAddress), NULL);
	}

	return targetAddress;
}

void TargetAddress::SetAddress(HANDLE hProcess)
{
	DWORD address = GetAddress(hProcess);

	WriteProcessMemory(
		hProcess, (BYTE*)address, &replacementValue, sizeof(replacementValue), NULL);
}
