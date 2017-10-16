#include <Windows.h>
#include <TlHelp32.h>

#include "ProcessLocator.h"
#include "Injector.h"

int main()
{
	ProcessLocator locator("ac_client.exe");
	WCHAR dllFilePath[] = L"C:\\Users\\Dimitard\\Desktop\\AC.Injectable.dll";
	Injector injector(locator, dllFilePath);

	while (!injector.Inject())
	{

	}

	return 0;
}