#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <string>
#include "parser.h"
#include "BitManipulation.h"
#include "opcodes.h"

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

	uint32_t ParseInstruction(const char* instruction)
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

	uint32_t ParseFile(const char* file_path, uint32_t* program)
	{
		FILE* file = fopen(file_path, "r");
		if (file == NULL) {
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

	uint32_t HandleLoad()
	{
		char* registerToken = strtok(NULL, split);

		if (registerToken[0] != '$')
		{
			printf("Unknown register value: %s", registerToken);
			return -1;
		}
		char* valueToken = strtok(NULL, split);

		int registerNumber = atoi(registerToken + 1);
		int valueNumber = atoi(valueToken);

		uint32_t instruction = 0;
		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::LOAD);
		instruction = BitManipulation::WriteSecond8(instruction, registerNumber);
		instruction = BitManipulation::WriteLast16(instruction, valueNumber);
		return instruction;
	}

	uint32_t HandleAdd()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);
		char* register3Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$' || register3Token[0] != '$')
		{
			printf("Unknown register value: %s %s %s", register1Token, register2Token, register3Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);
		int register3 = atoi(register3Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::ADD);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);
		instruction = BitManipulation::WriteLast8(instruction, register3);
		return instruction;
	}

	uint32_t HandleDiv()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);
		char* register3Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$' || register3Token[0] != '$')
		{
			printf("Unknown register value: %s %s %s", register1Token, register2Token, register3Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);
		int register3 = atoi(register3Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::DIV);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);
		instruction = BitManipulation::WriteLast8(instruction, register3);
		return instruction;
	}

	uint32_t HandleSub()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);
		char* register3Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$' || register3Token[0] != '$')
		{
			printf("Unknown register value: %s %s %s", register1Token, register2Token, register3Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);
		int register3 = atoi(register3Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::SUB);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);
		instruction = BitManipulation::WriteLast8(instruction, register3);
		return instruction;
	}

	uint32_t HandleMul()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);
		char* register3Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$' || register3Token[0] != '$')
		{
			printf("Unknown register value: %s %s %s", register1Token, register2Token, register3Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);
		int register3 = atoi(register3Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::MUL);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);
		instruction = BitManipulation::WriteLast8(instruction, register3);
		return instruction;
	}

	uint32_t HandleJmp()
	{
		char* jmpTargetToken = strtok(NULL, split);

		uint32_t instruction = 0;
		uint16_t jmpTarget = atoi(jmpTargetToken);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::JMP);
		instruction = BitManipulation::WriteLast16(instruction, jmpTarget);
		return instruction;
	}

	uint32_t HandleJmpf()
	{
		char* jmpTargetToken = strtok(NULL, split);

		uint32_t instruction = 0;
		uint16_t jmpTarget = atoi(jmpTargetToken);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::JMPF);
		instruction = BitManipulation::WriteLast16(instruction, jmpTarget);
		return instruction;
	}
	uint32_t HandleJmpb()
	{
		char* jmpTargetToken = strtok(NULL, split);

		uint32_t instruction = 0;
		uint16_t jmpTarget = atoi(jmpTargetToken);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::JMPB);
		instruction = BitManipulation::WriteLast16(instruction, jmpTarget);
		return instruction;
	}

	uint32_t HandleEq()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);
		if (register1Token[0] != '$' || register2Token[0] != '$')
		{
			printf("Unknown register value: %s %s", register1Token, register2Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::EQ);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);
		return instruction;
	}

	uint32_t HandleNeq()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$')
		{
			printf("Unknown register value: %s %s", register1Token, register2Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::NEQ);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);

		return instruction;
	}

	uint32_t HandleGt()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$')
		{
			printf("Unknown register value: %s %s", register1Token, register2Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::GT);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);

		return instruction;
	}

	uint32_t HandleLt()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$')
		{
			printf("Unknown register value: %s %s", register1Token, register2Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::LT);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);

		return instruction;
	}

	uint32_t HandleGtq()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$')
		{
			printf("Unknown register value: %s %s", register1Token, register2Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::GTQ);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);

		return instruction;
	}

	uint32_t HandleLtq()
	{
		char* register1Token = strtok(NULL, split);
		char* register2Token = strtok(NULL, split);

		if (register1Token[0] != '$' || register2Token[0] != '$')
		{
			printf("Unknown register value: %s %s", register1Token, register2Token);
			return -1;
		}

		uint32_t instruction = 0;
		int register1 = atoi(register1Token + 1);
		int register2 = atoi(register2Token + 1);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::LTQ);
		instruction = BitManipulation::WriteSecond8(instruction, register1);
		instruction = BitManipulation::WriteThird8(instruction, register2);

		return instruction;
	}

	uint32_t HandleJeq()
	{
		char* jmpTargetToken = strtok(NULL, split);

		uint32_t instruction = 0;
		uint16_t jmpTarget = atoi(jmpTargetToken);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::JEQ);
		instruction = BitManipulation::WriteLast16(instruction, jmpTarget);

		return instruction;
	}

	uint32_t HandleJneq()
	{
		char* jmpTargetToken = strtok(NULL, split);

		uint32_t instruction = 0;
		uint16_t jmpTarget = atoi(jmpTargetToken);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::JNEQ);
		instruction = BitManipulation::WriteLast16(instruction, jmpTarget);

		return instruction;
	}

	uint32_t HandleHalt()
	{
		char* jmpTargetToken = strtok(NULL, split);
		return 0;
	}

	uint32_t HandleAloc()
	{
		char* alocSizeToken = strtok(NULL, split);

		uint32_t instruction = 0;
		uint16_t alocSize = atoi(alocSizeToken);

		instruction = BitManipulation::WriteFirst8(instruction, Opcodes::ALOC);
		instruction = BitManipulation::WriteLast16(instruction, alocSize);

		return instruction;
	}
}