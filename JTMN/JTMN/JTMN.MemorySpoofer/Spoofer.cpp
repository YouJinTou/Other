#include <ctime>
#include <iostream>

#include "Spoofer.h"

Spoofer::Spoofer(
	LPCWSTR gameWindowName,
	const std::unordered_map<std::string, TargetAddress>& targets) :
	gameWindowName(gameWindowName),
	targets(targets)
{
	std::cout << "[F1] -- Health" << std::endl;
	std::cout << "[F2] -- Ammo" << std::endl;
	std::cout << "[F3] -- Turn auto on/off" << std::endl;
}

bool Spoofer::Spoofing()
{
	elapsed = clock();

	if (elapsed < CooldownTicks)
	{
		return true;
	}

	elapsed = 0;
	HWND hGameWindow = FindWindow(NULL, gameWindowName);

	if (!hGameWindow)
	{
		std::cout << "Could not find game window." << std::endl;

		return false;
	}

	DWORD processId = NULL;
	GetWindowThreadProcessId(hGameWindow, &processId);

	if (processId == NULL)
	{
		std::cout << "Could not find process ID." << std::endl;

		return false;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	if (hProcess == INVALID_HANDLE_VALUE || hProcess == NULL)
	{
		std::cout << "Could not open process." << std::endl;

		return false;
	}

	HandleUserCommand(hProcess);

	return true;
}

bool Spoofer::ConditionsMet() const
{
	return false;
}

void Spoofer::HandleUserCommand(HANDLE hProcess)
{
	if (isAutomatic)
	{
		for (auto t : targets)
		{
			t.second.SetAddress(hProcess);
		}
	}

	std::string command;

	if (GetAsyncKeyState(VK_F1))
	{
		command = "Health";
	}

	if (GetAsyncKeyState(VK_F2))
	{
		command = "Ammo";
	}

	if (GetAsyncKeyState(VK_F3))
	{
		isAutomatic = !isAutomatic;
	}

	if (command != "NONE")
	{
		TargetAddress target = targets.find(command)->second;

		target.SetAddress(hProcess);
	}
}
