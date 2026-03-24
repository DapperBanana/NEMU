#include "Cartridge.h"

#include <fstream>

struct sHeader {
	char name[4];
	uint8_t prg_rom_chunks;
	uint8_t chr_rom_chunks;
	uint8_t mapper1;
	uint8_t mapper2;
	uint8_t prg_ram_size;
	uint8_t tv_system1;
	uint8_t tv_system2;
	char unused[5];
};

Cartridge::Cartridge(const std::string& sFileName) {
	sHeader header;

	std::ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);

	if (ifs.is_open()) {
		ifs.read((char*)&header, sizeof(sHeader));

		// Skip trainer data if present
		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

		// iNES Format Type 1 for now
		uint8_t nFileType = 1;

		if (nFileType == 1) {
			nPRGBanks = header.prg_rom_chunks;
			vPRGMemory.resize(nPRGBanks * 16384);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			nCHRBanks = header.chr_rom_chunks;
			if (nCHRBanks == 0) {
				// CHR RAM
				vCHRMemory.resize(8192);
			}
			else {
				vCHRMemory.resize(nCHRBanks * 8192);
			}
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}

		bImageValid = true;
		ifs.close();
	}
}

Cartridge::~Cartridge() {

}

bool Cartridge::ImageValid() {
	return bImageValid;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t& data) {
	// Mapper 000 only for now
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		uint32_t mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		data = vPRGMemory[mapped_addr];
		return true;
	}
	return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data) {
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		uint32_t mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		vPRGMemory[mapped_addr] = data;
		return true;
	}
	return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t& data) {
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		data = vCHRMemory[addr];
		return true;
	}
	return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		if (nCHRBanks == 0) {
			// CHR RAM writable
			vCHRMemory[addr] = data;
			return true;
		}
	}
	return false;
}
