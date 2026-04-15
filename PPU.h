#pragma once

#include <cstdint>

class PPU {
public:
	PPU();
	~PPU();

public:
	uint8_t cpuRead(uint16_t addr, bool bReadOnly);
	void cpuWrite(uint16_t addr, uint8_t data);

	void vramWrite(uint16_t addr, uint8_t data);
	uint8_t vramRead(uint16_t addr);

public:
	uint8_t patternTable[2][4096];
	uint8_t nameTable[4][1024];	u
	uint8_t paletteTable[32];

	uint8_t oamMemory[256];

private:
	uint8_t status = 0x00;
	uint8_t control = 0x00;
	uint8_t mask = 0x00;

	uint8_t dataBuffer = 0x00;

	uint16_t addressLatch = 0x0000;
	uint16_t address = 0x0000;
	uint8_t tIncrement = 1;
	bool bAddressLatch = false;

uint8_t oamAddress = 0x00;
};