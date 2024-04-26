#ifndef BITMANIPULATION_H
#define BITMANIPULATION_H
#include <cstdint>

namespace BitManipulation
{
	uint16_t ReadLast16(uint32_t original_value);
	int8_t ReadFirst8(uint32_t original_value);
	int8_t ReadSecond8(uint32_t original_value);
	int8_t ReadThird8(uint32_t original_value);
	int8_t ReadFourth8(uint32_t original_value);
	uint32_t WriteFirst8(uint32_t original_value, int8_t value_to_write);
	uint32_t WriteSecond8(uint32_t original_value, int8_t value_to_write);
	uint32_t WriteThird8(uint32_t original_value, int8_t value_to_write);
	uint32_t WriteLast8(uint32_t original_value, int8_t value_to_write);
	uint32_t WriteLast16(uint32_t original_value, uint16_t value_to_write);
}
#endif // !BITMANIPULATION_H
