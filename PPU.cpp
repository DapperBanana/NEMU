#include "PPU.h"


PPU::PPU() {
	for (auto& nt : nameTable)
		for (auto& b : nt) b = 0x00;

	for (auto& pt : patternTable)
		for (auto& b : pt) b = 0x00;
	
	for (auto& b : paletteTable) b = 0x00;

	for (auto& b : oamMemory) b = 0x00;
}

PPU::~PPU() {

}

uint8_t PPU::cpuRead(uint16_t addr, bool bReadOnly) {
	uint8_t data = 0x00;

	switch (addr) {
	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		data = (status & 0xE0) | (dataBuffer & 0x1F);
		status &= ~0x80; // Clear vblank flag on read
		bAddressLatch = false;
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		data = oamMemory[oamAddress];
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		data = dataBuffer;
		dataBuffer = vramRead(address);
		address += tIncrement;
		break;
	}

	return data;
}

void PPU::cpuWrite(uint16_t addr, uint8_t data) {
	switch (addr) {
	case 0x0000: // Control
		control = data;
		tIncrement = (data & 0x04) ? 32 : 1; // Set VRAM address increment
		break;
	case 0x0001: // Mask
		mask = data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		oamAddress = data;
		break;
	case 0x0004: // OAM Data
		oamMemory[oamAddress] = data;
		oamAddress++;
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		addressLatch = (addressLatch << 8) | data;
		address = addressLatch;
		break;
	case 0x0007: // PPU Data
		vramWrite(address, data);
		address += tIncrement;
		break;
	}
}

void PPU::vramWrite(uint16_t addr, uint8_t data) {
	addr &= 0x3FFF; // Mirroring

	if (addr >= 0x0000 && addr <= 0x1FFF) {
		patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		nameTable[(addr & 0x0C00) >> 10][addr & 0x03FF] = data;
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		paletteTable[addr & 0x001F] = data;
	}
}

uint8_t PPU::vramRead(uint16_t addr) {
	addr &= 0x3FFF;

uint8_t data = 0x00;

	if (addr >= 0x0000 && addr <= 0x1FFF) {
		data = patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF];
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		data = nameTable[(addr & 0x0C00) >> 10][addr & 0x03FF];
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		data = paletteTable[addr & 0x001F];
	}

	return data;
}