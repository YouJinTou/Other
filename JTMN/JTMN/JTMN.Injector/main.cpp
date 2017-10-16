#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

#include "ProcessLocator.h"
#include "Injector.h"

int main()
{
	ProcessLocator locator("ac_client.exe");
	WCHAR dllFilePath[] = 
		L"C:\\Users\\Dimitard\\source\\repos\\Other\\JTMN\\JTMN\\Debug\\AC.Injectable.dll";
	Injector injector(locator, dllFilePath);

	while (!injector.Inject())
	{
		std::system("cls");
		std::cout << "Assault Cube hasn't been started yet..." << std::endl;
	}

	std::cout << "Injection successful." << std::endl;

	Sleep(3000);

	return 0;
}