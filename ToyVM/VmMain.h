#ifndef VMMAIN_H
#define VMMAIN_H
#include "vm.h"

namespace VmMain
{
	bool Initialize(uint32_t* program, size_t programSize);
	void Run();
	void Dispose();
	Vm::VM* GetInstance();
}
#endif // !VMMAIN_H
