#ifndef VMEXECUTOR_H
#define VMEXECUTOR_H
#include <cstdint>
#include "vm.h"

namespace VmExecutor
{
	void ExecuteLoad(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteAddR(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteAddI(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteSub(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteMul(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteDiv(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteJmp(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteJmpf(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteJmpb(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteEq(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteNEQ(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteGT(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteLT(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteGTQ(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteLTQ(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteJEQ(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteJNEQ(Vm::VM* vmInstance, uint32_t instruction);
	void ExecuteSet(Vm::VM* vmInstance, uint32_t instruction);
}
#endif // !VMEXECUTOR_H
