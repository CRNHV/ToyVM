#ifndef VM_H
#define VM_H
#include <cstdint>

namespace Vm
{
	typedef struct
	{
		uint32_t registers[32];
		uint32_t* handles[32];
		uint32_t* program;
		uint32_t* heap;
		uint16_t heapSize;
		uint16_t pc;
		uint16_t remainder;
		bool equal_flag;
	} VM;

	uint32_t NextInstruction(VM* vm);
}
#endif // !VM_H
