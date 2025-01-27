#include <iostream>
#include "Windows.h"

class ByPass
{
public:
	ByPass() {}

	bool Attach(DWORD pid)
	{
		m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		return m_hProcess != NULL ? true : false;
	}

	bool Read(uintptr_t ipBaseAddress, void* ipBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead)
	{
		return ReadProcessMemory(m_hProcess, (LPCVOID)ipBaseAddress, ipBuffer, nSize, lpNumberOfBytesRead);
	}

	bool Write(uintptr_t ipBaseAddress, int ipBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten)
	{
		return WriteProcessMemory(m_hProcess, (LPVOID)ipBaseAddress, &ipBuffer, nSize, lpNumberOfBytesWritten);
	}

	~ByPass()
	{
		if (m_hProcess != NULL)
		{
			if (CloseHandle(m_hProcess))
				std::cout << "m_hProcess closed" << std::endl;
			else
				std::cout << "Error closing m_hProcess: " << std::dec << GetLastError() << std::endl;
		}
	}

private:
	HANDLE m_hProcess = NULL;
};
