---
title: Address increment in control register
date: 2026-03-28
tags: [ppu, nes, emulator, addressing]
type: technique
project: DapperBanana/NEMU
---

The PPU control register determines how the PPU address is incremented after each read/write to the PPU data port. It can increment by 1 or 32. Incrementing by 32 is used for reading tile data in vertical strips, while incrementing by 1 accesses sequential bytes. By encapsulating the address increment logic within the PPU control register write, the read/write cycle can be simplified.
