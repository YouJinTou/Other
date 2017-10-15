#ifndef SPOOFER
#define SPOOFER

#include <Windows.h>
#include <string>
#include <unordered_map>

#include "TargetAddress.h"

class Spoofer
{
public:
	Spoofer(
		LPCWSTR gameWindowName,
		const std::unordered_map<std::string, TargetAddress>& targets);
	bool Spoofing();
private:
	static constexpr int CooldownTicks = 2000;
	std::string gameName;
	LPCWSTR gameWindowName;
	const std::unordered_map<std::string, TargetAddress> targets;
	unsigned long elapsed = 0;
	bool isAutomatic = false;
private:
	bool ConditionsMet() const;
	void HandleUserCommand(HANDLE hProcess);
};

#endif // !SPOOFER