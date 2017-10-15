#ifndef TARGET_ADDRESS
#define TARGET_ADDRESS

#include <Windows.h>
#include <string>
#include <vector>

class TargetAddress
{
public:
	TargetAddress() = default;
	TargetAddress(
		const int replacementValue,
		const DWORD baseAddress,
		const std::vector<DWORD> offsets);
	void SetAddress(HANDLE hProcess);
private:
	const int replacementValue;
	const DWORD baseAddress;
	const std::vector<DWORD> offsets;
	DWORD targetAddress;
	bool addressFound = false;
private:
	DWORD GetAddress(const HANDLE hProcess);
};

#endif // !TARGET_ADDRESS
