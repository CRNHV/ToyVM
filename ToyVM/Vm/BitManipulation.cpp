#include "../Includes/BitManipulation.h"

namespace BitManipulation
{
	uint16_t BitManipulation::ReadLast16(uint32_t original_value)
	{
		uint16_t val = (uint16_t)(original_value & 0xFFFF);
		return val;
	}

	int8_t BitManipulation::ReadFirst8(uint32_t original_value)
	{
		return (int8_t)(original_value >> 24);
	}

	int8_t BitManipulation::ReadSecond8(uint32_t original_value)
	{
		return (int8_t)((original_value >> 16) & 0x00FF);
	}

	int8_t BitManipulation::ReadThird8(uint32_t original_value)
	{
		return (original_value >> 8) & 0x000000FF;
	}

	int8_t BitManipulation::ReadFourth8(uint32_t original_value)
	{
		return (int8_t)((original_value) & 0x000000FF);
	}

	uint32_t BitManipulation::WriteFirst8(uint32_t original_value, int8_t value_to_write)
	{
		uint32_t cleared = original_value & 0x00ffffff;
		return cleared | value_to_write << 24;
	}

	uint32_t BitManipulation::WriteSecond8(uint32_t original_value, int8_t value_to_write)
	{
		uint32_t cleared = original_value & 0xFF00FFFF;
		uint32_t shifted = (uint32_t)(value_to_write & 0xFF) << 16;
		return cleared | shifted;
	}

	uint32_t BitManipulation::WriteThird8(uint32_t original_value, int8_t value_to_write)
	{
		uint32_t cleared = original_value & 0xFFFF00FF;
		return cleared | ((uint32_t)(value_to_write & 0xFF) << 8);
	}

	uint32_t BitManipulation::WriteLast8(uint32_t original_value, int8_t value_to_write)
	{
		uint32_t cleared = original_value & 0xFFFFFF00;
		return cleared | (uint32_t)(value_to_write & 0xFF);
	}

	uint32_t BitManipulation::WriteLast16(uint32_t original_value, uint16_t value_to_write)
	{
		uint32_t cleared = original_value & 0xFFFF0000;
		return cleared | (value_to_write & 0xFFFF);
	}
}