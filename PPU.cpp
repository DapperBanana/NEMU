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
		// OAMADDR register (W)
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		break;
	}

	return data;
}

void PPU::cpuWrite(uint16_t addr, uint8_t data) {
	switch (addr) {
	case 0x0000: // Control
		control = data;
		break;
	case 0x0001: // Mask
		mask = data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		oamAddr = data;
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		break;
	}
}

void PPU::ppuWrite(uint16_t addr, uint8_t data) {
	addr &= 0x3FFF;
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		addr &= 0x0FFF;
		if (cart->mirror == Cartridge::MIRROR::VERTICAL) {
			// Vertical Mirroring
			if (addr >= 0x0000 && addr <= 0x03FF) nameTable[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF) nameTable[1][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF) nameTable[0][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF) nameTable[1][addr & 0x03FF] = data;
		}
		else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL) {
			// Horizontal Mirroring
			if (addr >= 0x0000 && addr <= 0x03FF) nameTable[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF) nameTable[0][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF) nameTable[1][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF) nameTable[1][addr & 0x03FF] = data;
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3F1F) {
		addr &= 0x001F;
		paletteTable[addr] = data;
	}
}