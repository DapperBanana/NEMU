#pragma once
#include <cstdint>
#include "olc6502.h"
#include <array>

class Bus{
	
	public:
		Bus();
		~Bus();

	//devices on the bus
	public:
		olc6502 cpu;

		//fake RAM using the stack
		std::array<uint8_t, 64 * 1024> ram;

	//bus read/write
	public:
		void write(uint16_t addr, uint8_t data);
		uint8_t read(uint16_t addr, bool bReadOnly = false);

};

