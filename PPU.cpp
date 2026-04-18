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
		data = oamData;
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		data = dataBuffer;
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
		oamData = data;
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		dataBuffer = data;
		break;
	}
}

void PPU::clock() {

}
