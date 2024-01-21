#pragma once
#include <cstdint>

uint32_t WriteFirst8(uint32_t original_value, uint16_t value_to_write) {
	uint32_t cleared = original_value & 0x00ffffff;
	return cleared | value_to_write << 24;
}

uint32_t WriteSecond8(uint32_t original_value, uint16_t value_to_write) {
	uint32_t cleared = original_value & 0xff00ffff;
	return cleared | value_to_write << 16;
}

uint32_t WriteThird8(uint32_t original_value, uint16_t value_to_write) {
	uint32_t cleared = original_value & 0xffff00ff;
	return cleared | value_to_write << 8;
}

uint32_t WriteLast8(uint32_t original_value, uint16_t value_to_write) {
	uint32_t cleared = original_value & 0xffffff00;
	return cleared | value_to_write << 8;
}

uint32_t WriteLast16(uint32_t original_value, uint16_t value_to_write) {
	uint32_t cleared = original_value & 0xffff0000;
	return cleared | value_to_write << 0;
}

uint16_t ReadLast16(uint32_t original_value) {
	return (uint16_t)(original_value & 0xFFFF);
}

uint16_t ReadFirst8(uint32_t original_value) {
	return (uint16_t)(original_value >> 24);
}

uint16_t ReadSecond8(uint32_t original_value) {
	return (uint16_t)((original_value >> 16) & 0x00FF);
}