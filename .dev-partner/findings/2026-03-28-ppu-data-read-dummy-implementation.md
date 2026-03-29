---
title: Dummy read on PPU data port
date: 2026-03-28
tags: [ppu, nes, emulator, read]
type: pattern
project: DapperBanana/NEMU
---

The NES PPU's data port exhibits special read behavior. Specifically, after writing to PPU registers, the first read from the data port ($2007) returns stale data. Subsequent reads return the data from the PPU's internal memory as expected. This 'dummy read' is implemented to accurately emulate the PPU's behavior, which affects how games read back palette or tile data during rendering. This pattern demonstrates a deeper dive into hardware-specific quirks, moving beyond textbook memory access.
