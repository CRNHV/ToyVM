#include "opcodes.h"

namespace Opcodes
{
	OpCode GetNextOpcode(VM* vm)
	{
		OpCode opCode = (OpCode)vm->program[vm->pc];
		vm->pc += 1;
		return opCode;
	}
}