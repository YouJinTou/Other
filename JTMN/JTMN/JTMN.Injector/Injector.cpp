#include "Injector.h"

Injector::Injector(ProcessLocator locator, const std::string& dllFilePath) :
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

	HINSTANCE hKernelLib = LoadLibrary("KERNEL32");
	auto funcAddress = GetProcAddress(hKernelLib, "LoadLibraryA");
	LPVOID paramAddress = VirtualAllocEx(hProcess, NULL, dllFilePath.length(), MEM_COMMIT, PAGE_READWRITE);
	bool memoryWritten = WriteProcessMemory(hProcess, paramAddress, nullptr, sizeof(int), NULL);

	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)funcAddress, paramAddress, 0, 0);

	CloseHandle(hProcess);

	return memoryWritten;
}
