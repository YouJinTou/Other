#include <Windows.h>
#include <TlHelp32.h>

#include "ProcessLocator.h"

int main()
{
	ProcessLocator locator("ac_client.exe");
	DWORD processId = locator.TryGetProcessId();


	return 0;
}