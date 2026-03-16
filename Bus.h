#pragma once

#include <cstdint>
#include <array>

#include "olc6502.h"
#include "PPU.h"

class Bus {
public:
	Bus();
	~Bus();

public:
	olc6502 cpu;
	PPU ppu;

	std::array<uint8_t, 2048> cpuRam;

public:
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);

private:
	uint32_t nSystemClockCounter = 0;
};
