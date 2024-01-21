#ifndef OPCODES_H
#define OPCODES_H
namespace Opcodes
{
	typedef enum
	{
		HLT, // Halt
		LOAD, // Load
		ADD, // Add
		SUB, // Substract
		MUL, // Multiply
		DIV, // Divide
		JMP, // Jump
		JMPF, // Jump forward by x 
		JMPB, // Jump backward by x
		EQ, // Equal
		NEQ, // Not equal
		GT, // Greater than
		LT, // Less than
		GTQ, // Greater than or equal to
		LTQ, // Less than or equal to
		JEQ, // Jump if equal
		JNEQ, // Jump if not equal
		ALOC, // Allocate memory
		FREE, // Free memory

	} OpCode;
}
#endif // !OPCODES_H