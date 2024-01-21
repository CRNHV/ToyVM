#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <string>
#include "../Includes/OpcodeParser.h"
#include "../Includes/BitManipulation.h"
#include "../Includes/opcodes.h"

namespace Parser
{
	typedef struct
	{
		const char* instructionName;
		uint32_t(*handlerFunction)();
	} InstructionEntry;

	InstructionEntry instructionTable[] = {
		{"LOAD", HandleLoad},
		{"ADD", HandleAdd},
		{"SUB", HandleSub},
		{"MUL", HandleMul},
		{"DIV", HandleDiv},
		{"JMP", HandleJmp},
		{"JMPF", HandleJmpf},
		{"JMPB", HandleJmpb},
		{"EQ", HandleEq},
		{"NEQ", HandleNeq},
		{"GT", HandleGt},
		{"LT", HandleLt},
		{"GTQ", HandleGtq},
		{"LTQ", HandleLtq},
		{"JEQ", HandleJeq},
		{"JNEQ", HandleJneq},
		{"HALT", HandleHalt},
		{"ALOC", HandleAloc}
	};

	const char split[2] = " ";
	const int instructionTableSize = sizeof(instructionTable) / sizeof(instructionTable[0]);

	uint32_t Parser::ParseInstruction(const char* instruction)
	{
		for (int i = 0; i < instructionTableSize; i++)
		{
			if (strcmp(instructionTable[i].instructionName, instruction) == 0)
			{
				return (*instructionTable[i].handlerFunction)();
			}
		}
		printf("Unknown instruction: %s\n", instruction);
	}

	uint32_t Parser::ParseFile(const char* file_path, uint32_t* program)
	{
		FILE* file = fopen(file_path, "r");
		if (file == NULL)
		{
			perror("Error opening file");
			return 0;
		}

		memset(program, 0, 512);

		char lineBuffer[512] = { 0 };
		uint32_t programSize = 0;

		while (fgets(lineBuffer, 512, file) != NULL)
		{
			char* token;

			token = strtok(lineBuffer, split);
			uint32_t instruction = ParseInstruction(token);
			if (instruction == -1)
			{
				printf("Error parsing tokens %s \n", token);
				break;
			}

			program[programSize++] = instruction;
		}

		fclose(file);
		return programSize;
	}


	int Parser::ExtractRegister()
	{
		char* token = strtok(NULL, split);
		if (token == NULL || token[0] != '$')
		{
			printf("Unknown register value: %s\n", token);
			return -1;
		}
		return atoi(token + 1);
	}

	uint32_t Parser::EncodeInstruction(uint8_t opcode, int reg1, int reg2, int reg3, uint16_t value)
	{
		uint32_t instruction = 0;
		instruction = BitManipulation::WriteFirst8(instruction, opcode);
		if (reg1 != -1) instruction = BitManipulation::WriteSecond8(instruction, reg1);
		if (reg2 != -1) instruction = BitManipulation::WriteThird8(instruction, reg2);
		if (reg3 != -1) instruction = BitManipulation::WriteLast8(instruction, reg3);
		if (value != 0) instruction = BitManipulation::WriteLast16(instruction, value);
		return instruction;
	}

	// Refactored methods (example for HandleLoad, HandleAdd, and HandleJmp)
	uint32_t Parser::HandleLoad()
	{
		int registerNumber = ExtractRegister();
		if (registerNumber == -1) return -1;

		char* valueToken = strtok(NULL, split);
		int valueNumber = atoi(valueToken);

		return EncodeInstruction(Opcodes::LOAD, registerNumber, -1, -1, valueNumber);
	}

	uint32_t Parser::HandleAdd()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		int register3 = ExtractRegister();
		if (register3 == -1) return -1;

		return EncodeInstruction(Opcodes::ADD, register1, register2, register3, 0);
	}

	uint32_t Parser::HandleJmp()
	{
		char* jmpTargetToken = strtok(NULL, split);
		uint16_t jmpTarget = atoi(jmpTargetToken);

		return EncodeInstruction(Opcodes::JMP, -1, -1, -1, jmpTarget);
	}

	uint32_t Parser::HandleDiv()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		int register3 = ExtractRegister();
		if (register3 == -1) return -1;

		return EncodeInstruction(Opcodes::DIV, register1, register2, register3, 0);
	}

	uint32_t Parser::HandleSub()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		int register3 = ExtractRegister();
		if (register3 == -1) return -1;

		return EncodeInstruction(Opcodes::SUB, register1, register2, register3, 0);
	}

	uint32_t Parser::HandleMul()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		int register3 = ExtractRegister();
		if (register3 == -1) return -1;

		return EncodeInstruction(Opcodes::MUL, register1, register2, register3, 0);
	}

	uint32_t Parser::HandleJmpf()
	{
		char* jmpTargetToken = strtok(NULL, split);
		uint16_t jmpTarget = atoi(jmpTargetToken);

		return EncodeInstruction(Opcodes::JMPF, -1, -1, -1, jmpTarget);
	}

	uint32_t Parser::HandleJmpb()
	{
		char* jmpTargetToken = strtok(NULL, split);
		uint16_t jmpTarget = atoi(jmpTargetToken);

		return EncodeInstruction(Opcodes::JMPB, -1, -1, -1, jmpTarget);
	}

	uint32_t Parser::HandleEq()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		return EncodeInstruction(Opcodes::EQ, register1, register2, -1, 0);
	}

	uint32_t Parser::HandleNeq()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		return EncodeInstruction(Opcodes::NEQ, register1, register2, -1, 0);
	}

	uint32_t Parser::HandleGt()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		return EncodeInstruction(Opcodes::GT, register1, register2, -1, 0);
	}

	uint32_t Parser::HandleLt()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		return EncodeInstruction(Opcodes::LT, register1, register2, -1, 0);
	}

	uint32_t Parser::HandleGtq()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		return EncodeInstruction(Opcodes::GTQ, register1, register2, -1, 0);
	}

	uint32_t Parser::HandleLtq()
	{
		int register1 = ExtractRegister();
		if (register1 == -1) return -1;

		int register2 = ExtractRegister();
		if (register2 == -1) return -1;

		return EncodeInstruction(Opcodes::LTQ, register1, register2, -1, 0);
	}

	uint32_t Parser::HandleJeq()
	{
		char* jmpTargetToken = strtok(NULL, split);
		uint16_t jmpTarget = atoi(jmpTargetToken);

		return EncodeInstruction(Opcodes::JEQ, -1, -1, -1, jmpTarget);
	}

	uint32_t Parser::HandleJneq()
	{
		char* jmpTargetToken = strtok(NULL, split);
		uint16_t jmpTarget = atoi(jmpTargetToken);

		return EncodeInstruction(Opcodes::JNEQ, -1, -1, -1, jmpTarget);
	}

	uint32_t Parser::HandleHalt()
	{
		// Halt does not require any arguments
		return EncodeInstruction(Opcodes::HLT, -1, -1, -1, 0);
	}

	uint32_t Parser::HandleAloc()
	{
		char* alocSizeToken = strtok(NULL, split);
		uint16_t alocSize = atoi(alocSizeToken);

		return EncodeInstruction(Opcodes::ALOC, -1, -1, -1, alocSize);
	}
}