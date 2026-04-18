#pragma once
#include <cstdint>

class PPU
{
public:
	PPU();
	~PPU();

public:
	uint8_t cpuRead(uint16_t addr, bool bReadOnly);
	void cpuWrite(uint16_t addr, uint8_t data);

	void clock();

private:

	// PPU internal memory

	uint8_t patternTable[2][4096];
	uint8_t nameTable[2][1024];
	uint8_t paletteTable[32];

	uint8_t oamMemory[256];

	// PPU registers
	uint8_t control = 0x00;
	uint8_t mask = 0x00;
	uint8_t status = 0x00;
	uint8_t oamAddr = 0x00;
	uint8_t oamData = 0x00;
	uint8_t scroll = 0x00;
	uint8_t addr = 0x00;
	uint8_t dataBuffer = 0x00;

	bool bAddressLatch = false;

	// PPU Clock
	uint16_t scanline = 0;
	uint16_t cycle = 0;


	// PPU memory map constants
	static constexpr uint16_t PATTERN_TABLE0_START = 0x0000;
	static constexpr uint16_t PATTERN_TABLE1_START = 0x1000;
	static constexpr uint16_t NAMETABLE0_START = 0x2000;
	static constexpr uint16_t NAMETABLE1_START = 0x2400;
	static constexpr uint16_t NAMETABLE2_START = 0x2800;
	static constexpr uint16_t NAMETABLE3_START = 0x2C00;
	static constexpr uint16_t PALETTE_START = 0x3F00;

};
