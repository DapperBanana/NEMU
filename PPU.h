#pragma once

#include <cstdint>
#include <array>

class PPU {
public:
	PPU();
	~PPU();

public:
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
	void cpuWrite(uint16_t addr, uint8_t data);

	uint8_t ppuRead(uint16_t addr, bool bReadOnly = false);
	void ppuWrite(uint16_t addr, uint8_t data);

public:
	void clock();

private:
	// PPU nametable memory
	uint8_t nameTable[2][1024];
	// pattern table memory
	uint8_t patternTable[2][4096];
	// palette memory
	uint8_t paletteTable[32];

private:
	// internal registers
	uint8_t status = 0x00;
	uint8_t mask = 0x00;
	uint8_t control = 0x00;

	// address latch and data buffer for two-write registers
	bool bAddressLatch = false;
	uint8_t dataBuffer = 0x00;
	uint16_t vramAddr = 0x0000;

	// scanline and cycle tracking
	int16_t scanline = 0;
	int16_t cycle = 0;

public:
	bool bFrameComplete = false;
};
