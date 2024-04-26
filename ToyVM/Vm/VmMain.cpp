#include <memory>
#include <windows.h>

#include "../Includes/BitManipulation.h"
#include "../Includes/Opcodes.h"
#include "../Includes/Vm.h"
#include "../Includes/VmExecutor.h"
#include "../Includes/VmMain.h"

namespace VmMain
{
	Vm::VM* VmInstance;
	size_t ProgramSize;

	typedef struct
	{
		Opcodes::OpCode Opcode;
		void(*executionFunction)(Vm::VM* vmInstance, uint32_t instruction);
	} OpcodeHandler;

	OpcodeHandler opcodeHandlers[] = {
		{Opcodes::OpCode::LOAD, VmExecutor::ExecuteLoad},
		{Opcodes::OpCode::ADD, VmExecutor::ExecuteAdd},
		{Opcodes::OpCode::SUB, VmExecutor::ExecuteSub},
		{Opcodes::OpCode::MUL, VmExecutor::ExecuteMul},
		{Opcodes::OpCode::DIV, VmExecutor::ExecuteDiv},
		{Opcodes::OpCode::JMP, VmExecutor::ExecuteJmp},
		{Opcodes::OpCode::JMPF, VmExecutor::ExecuteJmpf},
		{Opcodes::OpCode::JMPB, VmExecutor::ExecuteJmpb},
		{Opcodes::OpCode::EQ, VmExecutor::ExecuteEq},
		{Opcodes::OpCode::NEQ, VmExecutor::ExecuteNEQ},
		{Opcodes::OpCode::GT, VmExecutor::ExecuteGT},
		{Opcodes::OpCode::LT, VmExecutor::ExecuteLT},
		{Opcodes::OpCode::GTQ, VmExecutor::ExecuteGTQ},
		{Opcodes::OpCode::LTQ, VmExecutor::ExecuteLTQ},
		{Opcodes::OpCode::JEQ, VmExecutor::ExecuteJEQ},
		{Opcodes::OpCode::JNEQ, VmExecutor::ExecuteJNEQ},
		{Opcodes::OpCode::SET, VmExecutor::ExecuteSet},
		{Opcodes::OpCode::ALOC, VmExecutor::ExecuteAloc},
	};

	bool VmMain::Initialize(uint32_t* program, size_t programSize)
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

	void VmMain::Run()
	{
		bool running = true;
		while (running)
		{
			if (VmInstance->pc > ProgramSize)
			{
				break;
			}

			uint32_t nextInstruction = Vm::NextInstruction(VmInstance);
			int8_t opcode = BitManipulation::ReadFirst8(nextInstruction);

			if (opcode == Opcodes::HLT)
			{
				running = false;
				break;
			}

			opcodeHandlers[opcode].executionFunction(VmInstance, nextInstruction);
		}
	}

	void VmMain::Dispose()
	{
		free(VmInstance);
	}

	Vm::VM* VmMain::GetInstance()
	{
		return VmInstance;
	}
}