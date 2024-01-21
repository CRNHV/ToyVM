#include "pch.h"



namespace BitWritingTests
{
#include "../ToyVM/bitmanipulation.cpp"

	TEST(WriteFirst8, ShouldWriteCorrectly)
	{
		uint32_t originalValue = 0x00000000;
		uint8_t bitsToWrite = 0xFFFF;

		uint32_t modifiedValue = BitManipulation::WriteFirst8(originalValue, bitsToWrite);
		uint8_t writtenBits = BitManipulation::ReadFirst8(originalValue);

		ASSERT_TRUE(bitsToWrite == writtenBits);
	}
}