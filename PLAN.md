# NEMU Development Plan

## Completed
- [x] CPU (olc6502) implementation
- [x] Bus with CPU RAM read/write
- [x] PPU register interface (cpuRead/cpuWrite for $2000-$2007)
- [x] PPU internal VRAM read/write (pattern tables, nametables, palette)
- [x] PPU OAM read/write
- [x] PPU clock with scanline/cycle tracking
- [x] Bus address mirroring for CPU RAM ($0000-$1FFF) and PPU ($2000-$3FFF)
- [x] System clock with 3:1 PPU:CPU ratio
- [x] NMI generation on vblank
- [x] Cartridge loading (iNES format, mapper 000)
- [x] Cartridge wired into Bus for CPU ($8000-$FFFF) and PPU ($0000-$1FFF)
- [x] PPU dummy read

## In Progress
- [ ] PPU rendering pipeline (background tile fetch per scanline)
- [ ] Nametable mirroring modes (horizontal/vertical from cartridge header)

## Up Next
- [ ] Additional mappers (001, 002, 003)
- [ ] PPU sprite evaluation