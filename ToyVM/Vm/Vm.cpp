#include "../Includes/Vm.h"

namespace Vm
{
	uint32_t Vm::NextInstruction(Vm::VM* vm)
	{
		return vm->program[vm->pc++];
	}
}