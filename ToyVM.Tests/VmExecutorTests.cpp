#include "pch.h"

#include "../ToyVM/vmmain.h"
#include "../ToyVM/vmmain.cpp"
#include "../ToyVM/parser.h"
#include "../ToyVM/parser.cpp"

namespace VmExecutorTests
{
	TEST(ExecuteLoad, ShouldExecuteSuccesfully)
	{
		uint32_t instruction = Parser::ParseInstruction("LOAD $0 50");
		VmMain::Initialize(&instruction, 1);
		VmMain::Run();
		Vm::VM* vmInstance = VmMain::GetInstance();

		ASSERT_TRUE(vmInstance->registers[0] == 50);
	}
}