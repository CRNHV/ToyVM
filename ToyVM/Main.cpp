#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <iostream>
#include <memory>
#include <stdio.h>
#include "Includes/BitManipulation.h"
#include "Includes/OpcodeParser.h"
#include "Includes/VmMain.h"

void WriteFile(uint32_t* data, size_t size);

int fib(int n)
{
	int a = 0, b = 1, c, i;
	if (n == 0)
		return a;
	for (i = 2; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

int main()
{
	uint32_t* program = (uint32_t*)malloc(512);
	size_t programSize = Parser::ParseFile("main.toy", program);
	if (program == nullptr)
	{
		printf("Error parsing main.toy");
	}

	WriteFile(program, programSize);

	if (!VmMain::Initialize(program, programSize))
	{
		return 1;
	}
	free(program);

	std::chrono::steady_clock::time_point vmBegin = std::chrono::steady_clock::now();
	VmMain::Run();
	std::chrono::steady_clock::time_point vmEnd = std::chrono::steady_clock::now();

	std::cout << "Fib calc time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(vmEnd - vmBegin).count() << "[nanoseconds]" << std::endl;

	VmMain::Dispose();

	return 0;
}

void WriteFile(uint32_t* data, size_t size)
{
	// Open the file with "ab+" mode
	FILE* file = fopen("program.top", "ab+");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}

	// Write the array to the file
	size_t written = fwrite(data, sizeof(uint32_t), size, file);
	if (written != size)
	{
		perror("Error writing to file");
	}

	// Close the file
	fclose(file);
}