#include <stdio.h>
#include <memory>
#include "vm.h"
#include "vmexecutor.h"
#include "BitManipulation.h"

namespace VmExecutor
{
	void ExecuteLoad(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg = BitManipulation::ReadSecond8(instruction);
		uint16_t number = BitManipulation::ReadLast16(instruction);
		vmInstance->registers[reg] = number;
		printf("LOAD $%d %d \r\n", reg, number);
	}

	void ExecuteAdd(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		uint8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] + vmInstance->registers[reg2];
		printf("ADD $%d $%d $%d \r\n", reg1, reg2, resultRegister);
	}

	void ExecuteSub(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		uint8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] - vmInstance->registers[reg2];
		printf("SUB $%d $%d $%d \r\n", reg1, reg2, resultRegister);
	}

	void ExecuteMul(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		uint8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] * vmInstance->registers[reg2];
		printf("MUL $%d $%d $%d \r\n", reg1, reg2, resultRegister);
	}

	void ExecuteDiv(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		uint8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] / vmInstance->registers[reg2];
		vmInstance->remainder = vmInstance->registers[reg1] % vmInstance->registers[reg2];
		printf("DIV $%d $%d $%d \r\n", reg1, reg2, resultRegister);
	}

	void ExecuteJmp(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t jmpTarget = BitManipulation::ReadLast16(instruction);
		vmInstance->pc = jmpTarget;
		printf("JMP %d\r\n", jmpTarget);
	}

	void ExecuteJmpf(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t jmpTarget = BitManipulation::ReadLast16(instruction);
		vmInstance->pc = vmInstance->pc + jmpTarget;
		printf("JMPF %d\r\n", jmpTarget);
	}

	void ExecuteJmpb(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t jmpTarget = BitManipulation::ReadLast16(instruction);
		vmInstance->pc = vmInstance->pc - jmpTarget;
		printf("JMPB %d\r\n", jmpTarget);
	}

	void ExecuteEq(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] == vmInstance->registers[reg2];
		printf("EQ $%d $%d \r\n", reg1, reg2);
	}

	void ExecuteNEQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] != vmInstance->registers[reg2];
		printf("NEQ $%d $%d \r\n", reg1, reg2);
	}

	void ExecuteGT(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] > vmInstance->registers[reg2];
		printf("GT $%d $%d \r\n", reg1, reg2);
	}

	void ExecuteLT(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] < vmInstance->registers[reg2];
		printf("GT $%d $%d \r\n", reg1, reg2);
	}

	void ExecuteGTQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] >= vmInstance->registers[reg2];
		printf("GTQ $%d $%d \r\n", reg1, reg2);
	}

	void ExecuteLTQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint8_t reg1 = BitManipulation::ReadSecond8(instruction);
		uint8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] <= vmInstance->registers[reg2];
		printf("LTQ $%d $%d \r\n", reg1, reg2);
	}

	void ExecuteJEQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t targetLocation = BitManipulation::ReadLast16(instruction);
		if (vmInstance->equal_flag)
		{
			vmInstance->pc = targetLocation - 1;
		}
		printf("JEQ %d \r\n", targetLocation);
	}

	void ExecuteJNEQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t targetLocation = BitManipulation::ReadLast16(instruction);
		if (!vmInstance->equal_flag)
		{
			vmInstance->pc = targetLocation - 1;
		}
		printf("JNEQ %d \r\n", targetLocation);
	}

	void ExecuteAloc(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t alocSize = BitManipulation::ReadLast16(instruction);
		vmInstance->heap = (uint32_t*)malloc(sizeof(uint32_t) * alocSize);
		printf("ALOC %d \r\n", alocSize);
	}
}