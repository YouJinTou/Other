#include "ProcessLocator.h"

ProcessLocator::ProcessLocator(const std::string & processName) :
	processName(processName)
{
}

DWORD ProcessLocator::TryGetProcessId() const
{
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	PROCESSENTRY32 processEntry;

	if (!Process32First(hProcessSnapshot, &processEntry))
	{
		CloseHandle(hProcessSnapshot);

		return NULL;
	}

	do
	{
		if (processName == processEntry.szExeFile)
		{
			CloseHandle(hProcessSnapshot);

			return processEntry.th32ProcessID;
		}
	} while (Process32Next(hProcessSnapshot, &processEntry));

	CloseHandle(hProcessSnapshot);

	return NULL;
}
