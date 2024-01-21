#include <memory>
#include <windows.h>

#include "Vm.h"
#include "Opcodes.h"
#include "VmExecutor.h"
#include "BitManipulation.h"

namespace VmMain
{
	Vm::VM* VmInstance;
	size_t ProgramSize;

	bool Initialize(uint32_t* program, size_t programSize)
	{
		ProgramSize = programSize;

		VmInstance = (Vm::VM*)malloc(sizeof(Vm::VM));
		if (VmInstance == NULL)
		{
			printf("Fatal error when initializing the VM");
			return false;
		}

		VmInstance->program = (uint32_t*)malloc(programSize * sizeof(uint32_t));
		if (VmInstance->program == NULL)
		{
			printf("Fatal error when initializing the VM program");
			return false;
		}

		VmInstance->equal_flag = false;
		VmInstance->heapSize = 0;
		VmInstance->pc = 0;
		VmInstance->remainder = 0;

		ZeroMemory(VmInstance->program, programSize * sizeof(uint32_t));
		memcpy(VmInstance->program, program, programSize * sizeof(uint32_t));

		for (size_t i = 0; i < 32; i++)
		{
			VmInstance->registers[i] = 0;
		}

		for (size_t i = 0; i < programSize; i++)
		{
			VmInstance->program[i] = program[i];
		}

		return true;
	}

	void Run()
	{
		bool running = true;
		while (running)
		{
			if (VmInstance->pc > ProgramSize)
			{
				break;
			}

			uint32_t nextInstruction = Vm::NextInstruction(VmInstance);
			uint8_t opcode = BitManipulation::ReadFirst8(nextInstruction);

			switch (opcode)
			{
			case Opcodes::HLT:
				running = false;
				break;
			case Opcodes::LOAD:
				VmExecutor::ExecuteLoad(VmInstance, nextInstruction);
				break;
			case Opcodes::ADD:
				VmExecutor::ExecuteAdd(VmInstance, nextInstruction);
				break;
			case Opcodes::SUB:
				VmExecutor::ExecuteSub(VmInstance, nextInstruction);
				break;
			case Opcodes::MUL:
				VmExecutor::ExecuteMul(VmInstance, nextInstruction);
				break;
			case Opcodes::DIV:
				VmExecutor::ExecuteDiv(VmInstance, nextInstruction);
				break;
			case Opcodes::JMP:
				VmExecutor::ExecuteJmp(VmInstance, nextInstruction);
				break;
			case Opcodes::JMPF:
				VmExecutor::ExecuteJmpf(VmInstance, nextInstruction);
				break;
			case Opcodes::JMPB:
				VmExecutor::ExecuteJmpb(VmInstance, nextInstruction);
				break;
			case Opcodes::EQ:
				VmExecutor::ExecuteEq(VmInstance, nextInstruction);
				break;
			case Opcodes::NEQ:
				VmExecutor::ExecuteNEQ(VmInstance, nextInstruction);
				break;
			case Opcodes::GT:
				VmExecutor::ExecuteGT(VmInstance, nextInstruction);
				break;
			case Opcodes::LT:
				VmExecutor::ExecuteLT(VmInstance, nextInstruction);
				break;
			case Opcodes::GTQ:
				VmExecutor::ExecuteGTQ(VmInstance, nextInstruction);
				break;
			case Opcodes::LTQ:
				VmExecutor::ExecuteLTQ(VmInstance, nextInstruction);
				break;
			case Opcodes::JEQ:
				VmExecutor::ExecuteJEQ(VmInstance, nextInstruction);
				break;
			case Opcodes::JNEQ:
				VmExecutor::ExecuteJNEQ(VmInstance, nextInstruction);
				break;
			case Opcodes::ALOC:
				VmExecutor::ExecuteAloc(VmInstance, nextInstruction);
				break;
			case Opcodes::FREE:
				break;
			}

			Sleep(300);
		}
	}

	void Dispose()
	{
		free(VmInstance);
	}

	Vm::VM* GetInstance()
	{
		return VmInstance;
	}
}