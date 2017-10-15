#ifndef INJECTOR
#define INJECTOR

#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include "ProcessLocator.h"

class Injector
{
public:
	Injector(ProcessLocator locator, const std::string& dllFilePath);
	bool Inject() const;
private:
	ProcessLocator locator;
	std::string dllFilePath;
};

#endif // !INJECTOR
