#include "../Includes/BitManipulation.h"

namespace BitManipulation
{
	uint16_t BitManipulation::ReadLast16(uint32_t original_value)
	{
		return (uint16_t)(original_value & 0xFFFF);
	}

	uint8_t BitManipulation::ReadFirst8(uint32_t original_value)
	{
		return (uint16_t)(original_value >> 24);
	}

	uint8_t BitManipulation::ReadSecond8(uint32_t original_value)
	{
		return (uint16_t)((original_value >> 16) & 0x00FF);
	}

	uint8_t BitManipulation::ReadThird8(uint32_t original_value)
	{
		return (uint16_t)((original_value >> 8) & 0x0000FF);
	}

	uint8_t BitManipulation::ReadFourth8(uint32_t original_value)
	{
		return (uint16_t)((original_value) & 0x000000FF);
	}

	uint32_t BitManipulation::WriteFirst8(uint32_t original_value, uint8_t value_to_write)
	{
		uint32_t cleared = original_value & 0x00ffffff;
		return cleared | value_to_write << 24;
	}

	uint32_t BitManipulation::WriteSecond8(uint32_t original_value, uint8_t value_to_write)
	{
		uint32_t cleared = original_value & 0xff00ffff;
		return cleared | value_to_write << 16;
	}

	uint32_t BitManipulation::WriteThird8(uint32_t original_value, uint8_t value_to_write)
	{
		uint32_t cleared = original_value & 0xffff00ff;
		return cleared | value_to_write << 8;
	}

	uint32_t BitManipulation::WriteLast8(uint32_t original_value, uint8_t value_to_write)
	{
		uint32_t cleared = original_value & 0xffffff00;
		return cleared | value_to_write << 0;
	}

	uint32_t BitManipulation::WriteLast16(uint32_t original_value, uint16_t value_to_write)
	{
		uint32_t cleared = original_value & 0xffff0000;
		return cleared | value_to_write << 0;
	}
}