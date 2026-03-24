#pragma once

#include <cstdint>
#include <array>
#include <memory>

#include "olc6502.h"
#include "PPU.h"
#include "Cartridge.h"

class Bus {
public:
	Bus();
	~Bus();

	olc6502 cpu;
	PPU ppu;

	std::shared_ptr<Cartridge> cart;
	std::array<uint8_t, 2048> cpuRam;

	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);

	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	void clock();

private:
	uint32_t nSystemClockCounter = 0;
};
