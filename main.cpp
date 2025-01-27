#include <iostream>
#include "Windows.h"
#include "ByPass.cpp"

int main()
{
	DWORD pid = 0;
	std::cout << "PID: ";
	std::cin >> std::dec >> pid;

	uintptr_t address = 0x0;
	std::cout << "Address: ";
	std::cin >> std::hex >> address;


	ByPass* byPass = new ByPass();

	if (byPass->Attach(pid)) 
	{
		std::cout << "Process opened" << std::endl;
	}
	else std::cout << "Error: " << std::dec << GetLastError() << std::endl;

	int choice = 0;

	std::cout << "1 - Read \n 2 - Write" << std::endl;
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		ReadMem();
	case 2:
		WriteMem();

	default:
		std::cout << "Unexpected value" << std::endl;
	}

	int intRead = 0;

	std::cout << "Size of int: " << sizeof(int) << std::endl;
	int valueToWrite = 0;
	std::cout << "Value to write: ";
	std::cin >> valueToWrite;

	

	delete byPass;
}

void ReadMem()
{
	if (byPass->Read(address, &intRead, sizeof(int), NULL))
	{
		std::cout << "Successful read" << std::endl;
		std::cout << "Address: " << "0x" << std::hex << std::uppercase << address << " Value: " << std::dec << intRead << std::endl;
	}
	else std::cout << "Error: " << std::dec << GetLastError() << std::endl;
}

void WriteMem()
{
	if (byPass->Write(address, valueToWrite, sizeof(int), NULL))
	{
		std::cout << "Successful write" << std::endl;
		std::cout << "Address: " << "0x" << std::hex << std::uppercase << address << " Value: " << std::dec << valueToWrite << std::endl;
	}
	else std::cout << "Error: " << std::dec << GetLastError() << std::endl;
}