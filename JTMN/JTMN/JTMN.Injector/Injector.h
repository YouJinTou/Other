#ifndef INJECTOR
#define INJECTOR

#include <Windows.h>
#include <TlHelp32.h>

#include "ProcessLocator.h"

class Injector
{
public:
	Injector(ProcessLocator locator, const WCHAR* dllFilePath);
	bool Inject() const;
private:
	ProcessLocator locator;
	const WCHAR* dllFilePath;
};

#endif // !INJECTOR
