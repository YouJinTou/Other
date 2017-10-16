#include "Injector.h"

typedef HINSTANCE(*fpLoadLibrary)(char*);

Injector::Injector(ProcessLocator locator, const WCHAR* dllFilePath) :
	locator(locator),
	dllFilePath(dllFilePath)
{
}

bool Injector::Inject() const
{
	DWORD processId = locator.TryGetProcessId();

	if (processId == NULL)
	{
		return false;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	if (hProcess == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	const int dllPathSize = (wcslen(dllFilePath) + 1) * sizeof(WCHAR);
	LPVOID pAddress = VirtualAllocEx(hProcess, NULL, dllPathSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);	
	bool written = WriteProcessMemory(hProcess, pAddress, dllFilePath, dllPathSize, NULL);

	if (!written)
	{
		return false;
	}

	HMODULE hKernel = GetModuleHandleA("kernel32.dll");
	FARPROC funcAddress = GetProcAddress(hKernel, "LoadLibraryW");
	DWORD threadId;
	HANDLE hRemoteThread = 
		CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)funcAddress, pAddress, 0, &threadId);

	WaitForSingleObject(hRemoteThread, INFINITE);

	DWORD exitCode;

	GetExitCodeThread(hRemoteThread, &exitCode);

	CloseHandle(hProcess);
	CloseHandle(hRemoteThread);

	return exitCode != 0;
}
