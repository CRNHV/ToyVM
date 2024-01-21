#ifndef PARSER_H
#define PARSER_H
#include <cstdint>

namespace Parser
{
	uint32_t HandleLoad();
	uint32_t HandleAdd();
	uint32_t HandleDiv();
	uint32_t HandleSub();
	uint32_t HandleMul();
	uint32_t HandleJmp();
	uint32_t HandleJmpf();
	uint32_t HandleJmpb();
	uint32_t HandleEq();
	uint32_t HandleNeq();
	uint32_t HandleGt();
	uint32_t HandleLt();
	uint32_t HandleGtq();
	uint32_t HandleLtq();
	uint32_t HandleJeq();
	uint32_t HandleJneq();
	uint32_t HandleHalt();
	uint32_t HandleAloc();
	uint32_t ParseFile(const char* file_path, uint32_t* program);
	uint32_t ParseInstruction(const char* instruction);
}
#endif // !PARSER_H
