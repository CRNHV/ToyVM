#include "vm.h"

namespace Vm
{
	uint32_t NextInstruction(VM* vm)
	{
		return vm->program[vm->pc++];
	}
}