---
title: Understanding the PPU address latch
date: 2026-05-08
tags: [PPU, NES, addressing]
type: technique
project: DapperBanana/NEMU
---

The NES PPU uses a pair of registers as a latch to form a 15-bit address, allowing access to its memory. This is done because the NES CPU uses an 8-bit data bus, and 15 bits can't be written in a single operation. The first write latches the high byte, and the second write combines it with the low byte to form the full address. Getting the timing and order of operations correct for this latch is crucial for correct PPU behavior. Without it, the PPU wouldn't be able to access the correct memory locations for rendering graphics.
