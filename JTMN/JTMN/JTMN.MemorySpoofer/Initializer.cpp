#include <string>
#include <unordered_map>
#include <vector>

#include "Initializer.h"

Spoofer Initializer::Initialize()
{
	LPCWSTR gameWindowName = L"AssaultCube";	
	std::vector<DWORD> healthOffsets = { 0xF8 };
	std::vector<DWORD> ammoOffsets = { 0x384, 0x14, 0x0 };
	DWORD baseAddress = 0x00509B74;
	TargetAddress healthTarget(5000, baseAddress, healthOffsets);
	TargetAddress ammoTarget(20, baseAddress, ammoOffsets);
	std::unordered_map<std::string, TargetAddress> targets
	{
		{ "Health", healthTarget },
		{ "Ammo", ammoTarget }
	};

	Spoofer spoofer(gameWindowName, targets);

	return spoofer;
}
