#include <memory>
#include <stdio.h>
#include <windows.h>
#include "../Includes/BitManipulation.h"
#include "../Includes/Vm.h"
#include "../Includes/VmExecutor.h"

namespace VmExecutor
{
	void VmExecutor::ExecuteLoad(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg = BitManipulation::ReadSecond8(instruction);
		int8_t number = BitManipulation::ReadThird8(instruction);
		vmInstance->registers[reg] = number;
#ifdef _DEBUG
		printf("LOAD %d %d\r\n", reg, number);
		printf("==> %d %d\r\n", vmInstance->registers[reg], number);
#endif // _DEBUG
	}

	void VmExecutor::ExecuteAddR(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		int8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] + vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("ADDR %d %d %d\r\n", reg1, reg2, resultRegister);
		printf("==> %d %d %d\r\n", vmInstance->registers[reg1], vmInstance->registers[reg2], vmInstance->registers[resultRegister]);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteAddI(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t value = BitManipulation::ReadThird8(instruction);
		int8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] + value;
#ifdef _DEBUG
		printf("ADDI %d %d %d\r\n", reg1, value, resultRegister);
		printf("==> %d %d %d\r\n", vmInstance->registers[reg1], value, vmInstance->registers[resultRegister]);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteSub(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		int8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] - reg2;
#ifdef _DEBUG
		printf("SUB $%d $%d $%d\r\n", reg1, reg2, resultRegister);
		printf("==> %d %d %d\r\n", vmInstance->registers[reg1], vmInstance->registers[reg2], vmInstance->registers[resultRegister]);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteMul(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		int8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] * vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("MUL $%d $%d $%d\r\n", reg1, reg2, resultRegister);
		printf("==> %d %d %d\r\n", vmInstance->registers[reg1], vmInstance->registers[reg2], vmInstance->registers[resultRegister]);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteDiv(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		int8_t resultRegister = BitManipulation::ReadFourth8(instruction);
		vmInstance->registers[resultRegister] = vmInstance->registers[reg1] / vmInstance->registers[reg2];
		vmInstance->remainder = vmInstance->registers[reg1] % vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("DIV $%d $%d $%d\r\n", reg1, reg2, resultRegister);
		printf("==> %d %d %d %d\r\n", vmInstance->registers[reg1], vmInstance->registers[reg2], vmInstance->registers[resultRegister], vmInstance->remainder);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteJmp(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t jmpTarget = BitManipulation::ReadLast16(instruction);
		vmInstance->pc = jmpTarget;
#ifdef _DEBUG
		printf("JMP %d\r\n", jmpTarget);
		printf("==> %d \r\n", vmInstance->pc);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteJmpf(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t jmpTarget = BitManipulation::ReadLast16(instruction);
		vmInstance->pc = vmInstance->pc + jmpTarget;
#ifdef _DEBUG
		printf("JMPF %d\r\n", jmpTarget);
		printf("==> %d\r\n", vmInstance->pc);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteJmpb(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t jmpTarget = BitManipulation::ReadLast16(instruction);
		vmInstance->pc = vmInstance->pc - jmpTarget;
#ifdef _DEBUG
		printf("JMPB %d\r\n", jmpTarget);
		printf("==> %d\r\n", vmInstance->pc);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteEq(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] == vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("EQ $%d $%d\r\n", reg1, reg2);
		printf("==> %d\r\n", vmInstance->equal_flag);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteNEQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] != vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("NEQ $%d $%d\r\n", reg1, reg2);
		printf("==> %d\r\n", vmInstance->equal_flag);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteGT(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] > vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("GT $%d $%d\r\n", reg1, reg2);
		printf("==> %d\r\n", vmInstance->equal_flag);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteLT(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] < vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("GT $%d $%d\r\n", reg1, reg2);
		printf("==> %d\r\n", vmInstance->equal_flag);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteGTQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] >= vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("GTQ $%d $%d\r\n", reg1, reg2);
		printf("==> %d\r\n", vmInstance->equal_flag);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteLTQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t reg1 = BitManipulation::ReadSecond8(instruction);
		int8_t reg2 = BitManipulation::ReadThird8(instruction);
		vmInstance->equal_flag = vmInstance->registers[reg1] <= vmInstance->registers[reg2];
#ifdef _DEBUG
		printf("LTQ $%d $%d\r\n", reg1, reg2);
		printf("==> %d\r\n", vmInstance->equal_flag);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteJEQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t targetLocation = BitManipulation::ReadLast16(instruction);
		if (vmInstance->equal_flag)
		{
			vmInstance->pc = targetLocation - 1;
		}
#ifdef _DEBUG
		printf("JEQ %d \r\n", targetLocation);
		printf("==> EQ: %d %d\r\n", vmInstance->equal_flag, vmInstance->pc);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteJNEQ(Vm::VM* vmInstance, uint32_t instruction)
	{
		uint16_t targetLocation = BitManipulation::ReadLast16(instruction);
		if (!vmInstance->equal_flag)
		{
			vmInstance->pc = targetLocation - 1;
		}
#ifdef _DEBUG
		printf("JNEQ %d\r\n", targetLocation);
		printf("==> %d\r\n", vmInstance->pc);
#endif // _DEBUG

	}

	void VmExecutor::ExecuteSet(Vm::VM* vmInstance, uint32_t instruction)
	{
		int8_t targetRegister = BitManipulation::ReadSecond8(instruction);
		int8_t valueRegister = BitManipulation::ReadThird8(instruction);

		vmInstance->registers[targetRegister] = vmInstance->registers[valueRegister];

#ifdef _DEBUG
		printf("SET %d %d\r\n", targetRegister, valueRegister);
		printf("==> %d %d\r\n", vmInstance->registers[targetRegister], vmInstance->registers[valueRegister]);
#endif // _DEBUG

	}
}