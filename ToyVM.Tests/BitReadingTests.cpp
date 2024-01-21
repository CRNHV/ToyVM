#include "pch.h"

#include "../ToyVM/bitmanipulation.cpp"
#include "../ToyVM/bitmanipulation.h"

namespace BitManipulationTests
{
	TEST(ReadLast16, ShouldGetBitsCorrectly)
	{
		uint32_t input1 = 0xFFFFFFF0;
		uint16_t lowestBytes = BitManipulation::ReadLast16(input1);
		ASSERT_TRUE(lowestBytes == 0xFFF0);
	}

	TEST(ReadLast16, ShouldGetDifferentBits)
	{
		uint32_t input1 = 0xFFFFFFF0;
		uint16_t lowestBytes = BitManipulation::ReadLast16(input1);
		ASSERT_TRUE(lowestBytes != 0xFFFF);
	}

	TEST(ReadFirst8, ShouldGetBitsCorrectly)
	{
		uint32_t input1 = 0x00FFFFFF;
		uint16_t lowestBytes = BitManipulation::ReadFirst8(input1);
		ASSERT_TRUE(lowestBytes == 0x00);
	}

	TEST(ReadFirst8, ShouldGetDifferentBits)
	{
		uint32_t input1 = 0xF0FFFFFF;
		uint16_t lowestBytes = BitManipulation::ReadFirst8(input1);
		ASSERT_TRUE(lowestBytes != 0xFF);
	}

	TEST(ReadSecond8, ShouldGetBitsCorrectly)
	{
		uint32_t input1 = 0xFF00FFFF;
		uint16_t lowestBytes = BitManipulation::ReadSecond8(input1);
		ASSERT_TRUE(lowestBytes == 0x00);
	}

	TEST(ReadSecond8, ShouldGetDifferentBits)
	{
		uint32_t input1 = 0xFF00FFFF;
		uint16_t lowestBytes = BitManipulation::ReadSecond8(input1);
		ASSERT_TRUE(lowestBytes != 0xFF);
	}

	TEST(ReadThird8, ShouldGetBitsCorrectly)
	{
		uint32_t input1 = 0xFFFF00FF;
		uint16_t lowestBytes = BitManipulation::ReadThird8(input1);
		ASSERT_TRUE(lowestBytes == 0x00);
	}

	TEST(ReadThird8, ShouldGetDifferentBits)
	{
		uint32_t input1 = 0xFFFF00FF;
		uint16_t lowestBytes = BitManipulation::ReadThird8(input1);
		ASSERT_TRUE(lowestBytes != 0xFF);
	}

	TEST(ReadFourth8, ShouldGetBitsCorrectly)
	{
		uint32_t input1 = 0xFFFFFF00;
		uint16_t lowestBytes = BitManipulation::ReadFourth8(input1);
		ASSERT_TRUE(lowestBytes == 0x00);
	}

	TEST(ReadFourth8, ShouldGetDifferentBits)
	{
		uint32_t input1 = 0xFFFFFF00;
		uint16_t lowestBytes = BitManipulation::ReadFourth8(input1);
		ASSERT_TRUE(lowestBytes != 0xFF);
	}

	TEST(WriteFirst8, ShouldWriteCorrectly)
	{
		uint32_t originalValue = 0x00000000;
		uint8_t bitsToWrite = 0xFF;

		uint32_t modifiedValue = BitManipulation::WriteFirst8(originalValue, bitsToWrite);
		uint8_t writtenBits = BitManipulation::ReadFirst8(modifiedValue);

		ASSERT_TRUE(bitsToWrite == writtenBits);
	}

	TEST(WriteSecond8, ShouldWriteCorrectly)
	{
		uint32_t originalValue = 0x00000000;
		uint8_t bitsToWrite = 0xFF;

		uint32_t modifiedValue = BitManipulation::WriteSecond8(originalValue, bitsToWrite);
		uint8_t writtenBits = BitManipulation::ReadSecond8(modifiedValue);

		ASSERT_TRUE(bitsToWrite == writtenBits);
	}

	TEST(WriteThird8, ShouldWriteCorrectly)
	{
		uint32_t originalValue = 0x00000000;
		uint8_t bitsToWrite = 0xFF;

		uint32_t modifiedValue = BitManipulation::WriteThird8(originalValue, bitsToWrite);
		uint8_t writtenBits = BitManipulation::ReadThird8(modifiedValue);

		ASSERT_TRUE(bitsToWrite == writtenBits);
	}

	TEST(WriteFourth8, ShouldWriteCorrectly)
	{
		uint32_t originalValue = 0x00000000;
		uint8_t bitsToWrite = 0xFFFF;

		uint32_t modifiedValue = BitManipulation::WriteLast8(originalValue, bitsToWrite);
		uint8_t writtenBits = BitManipulation::ReadFourth8(modifiedValue);

		ASSERT_TRUE(bitsToWrite == writtenBits);
	}


	TEST(WriteLast16, ShouldWriteCorrectly)
	{
		uint32_t originalValue = 0x00000000;
		uint16_t bitsToWrite = 0xFFFF;

		uint32_t modifiedValue = BitManipulation::WriteLast16(originalValue, bitsToWrite);
		uint16_t writtenBits = BitManipulation::ReadLast16(modifiedValue);

		ASSERT_TRUE(bitsToWrite == writtenBits);
	}
}