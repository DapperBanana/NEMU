---
title: Cartridge address decoding delegates cleanly to Bus, avoiding memory duplication
date: 2026-03-23
tags: [pattern, technique]
type: technique
project: DapperBanana/NEMU
---

Wiring Cartridge into Bus so that CPU and PPU address spaces route through it keeps ROM data in one place and simplifies mapper logic. The CPU sees PRG ROM at 0x8000–0xFFFF; the PPU sees CHR ROM/RAM at 0x0000–0x1FFF via the PPU's address decoder.

This architecture scales well: mappers that do CHR banking, mirroring control, or PRG swapping can all live in Cartridge::write() without touching Bus or CPU/PPU internals. When you add mappers 1+ (MMC1, UxROM, etc.), the Bus stays unchanged—only Cartridge gains state and logic.

One edge case to watch: ensure Bus doesn't accidentally return stale data if Cartridge returns nullptr for unmapped regions. A defensive fallback (open bus value, typically 0x00 or 0xFF) prevents undefined behavior.
