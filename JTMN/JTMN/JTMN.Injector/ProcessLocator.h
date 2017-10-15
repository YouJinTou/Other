#ifndef PROCESS_LOCATOR
#define PROCESS_LOCATOR

#include <Windows.h>
#include <tlhelp32.h>
#include <string>

class ProcessLocator
{
public:
	ProcessLocator(const std::string& processName);
	DWORD TryGetProcessId() const;
private:
	std::string processName;
private:
};

#endif // !PROCESS_LOCATOR
