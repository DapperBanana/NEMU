#include "PPU.h"


PPU::PPU() {
	for (auto& nt : nameTable)
		for (auto& b : nt) b = 0x00;

	for (auto& pt : patternTable)
		for (auto& b : pt) b = 0x00;

	for (auto& b : paletteTable) b = 0x00;
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
		status &= ~0x80;
		bAddressLatch = false;
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		data = dataBuffer;
		dataBuffer = ppuRead(vramAddr);

		if (vramAddr >= 0x3F00)
			data = dataBuffer;

		vramAddr += (control & 0x04) ? 32 : 1;
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
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		bAddressLatch = !bAddressLatch;
		break;
	case 0x0006: // PPU Address
		if (!bAddressLatch) {
			vramAddr = (uint16_t)((data & 0x3F) << 8) | (vramAddr & 0x00FF);
			bAddressLatch = true;
		} else {
			vramAddr = (vramAddr & 0xFF00) | data;
			bAddressLatch = false;
		}
		break;
	case 0x0007: // PPU Data
		ppuWrite(vramAddr, data);
		vramAddr += (control & 0x04) ? 32 : 1;
		break;
	}
}

uint8_t PPU::ppuRead(uint16_t addr, bool bReadOnly) {
	uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (addr >= 0x0000 && addr <= 0x1FFF) {
		data = patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF];
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		addr &= 0x0FFF;
		data = nameTable[0][addr & 0x03FF];
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		data = paletteTable[addr];
	}

	return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data) {
	addr &= 0x3FFF;

	if (addr >= 0x0000 && addr <= 0x1FFF) {
		patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		addr &= 0x0FFF;
		nameTable[0][addr & 0x03FF] = data;
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		paletteTable[addr] = data;
	}
}

void PPU::clock() {
	// set vblank flag at scanline 241, cycle 1
	if (scanline == 241 && cycle == 1) {
		status |= 0x80;
		if (control & 0x80) {
			bNmi = true;
		}
	}

	// pre-render scanline clears vblank
	if (scanline == -1 && cycle == 1) {
		status &= ~0x80;
	}

	cycle++;
	if (cycle >= 341) {
		cycle = 0;
		scanline++;
		if (scanline >= 261) {
			scanline = -1;
			bFrameComplete = true;
		}
	}
}
