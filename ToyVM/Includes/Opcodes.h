#ifndef OPCODES_H
#define OPCODES_H
namespace Opcodes
{
	typedef enum
	{
		HALT, // Halt
		LOAD, // Load
		ADDR, // Add register values
		ADDI, // Add immediate value
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
		SET, // Set register to value of other register

	} OpCode;
}
#endif // !OPCODES_H